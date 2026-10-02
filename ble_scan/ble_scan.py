from __future__ import annotations

import asyncio
import threading
import tkinter as tk
from dataclasses import dataclass
from tkinter import messagebox, ttk
from typing import Callable


@dataclass(frozen=True)
class DeviceInfo:
    name: str
    address: str
    rssi: str


class BleScanner:
    def __init__(self, on_device: Callable[[DeviceInfo], None], on_complete: Callable[[str | None], None]):
        self._on_device = on_device
        self._on_complete = on_complete
        self._stop = threading.Event()
        self._thread: threading.Thread | None = None

    @property
    def running(self) -> bool:
        return self._thread is not None and self._thread.is_alive()

    def start(self, duration: float = 8.0) -> None:
        if self.running:
            return
        self._stop.clear()
        self._thread = threading.Thread(target=self._run, args=(duration,), daemon=True)
        self._thread.start()

    def stop(self) -> None:
        self._stop.set()

    def _run(self, duration: float) -> None:
        try:
            from bleak import BleakScanner
        except ImportError:
            self._on_complete("The 'bleak' package is not installed. Run: python -m pip install -r requirements.txt")
            return

        try:
            asyncio.run(self._scan(BleakScanner, duration))
        except Exception as exc:  # surface backend errors to the UI instead of failing silently
            self._on_complete(f"Bluetooth scan failed: {exc}")

    async def _scan(self, scanner_type, duration: float) -> None:
        def detection_callback(device, advertisement_data) -> None:
            if self._stop.is_set():
                return
            name = device.name or advertisement_data.local_name or "Unknown device"
            rssi = getattr(advertisement_data, "rssi", None)
            if rssi is None:
                rssi = getattr(device, "rssi", None)
            self._on_device(DeviceInfo(name, device.address, f"{rssi} dBm" if rssi is not None else "N/A"))

        scanner = scanner_type(detection_callback=detection_callback)
        await scanner.start()
        try:
            for _ in range(int(duration * 10)):
                if self._stop.is_set():
                    break
                await asyncio.sleep(0.1)
        finally:
            await scanner.stop()
        self._on_complete(None)


class BleScanApp(tk.Tk):
    def __init__(self) -> None:
        super().__init__()
        self.title("BLE Scan")
        self.geometry("760x460")
        self.minsize(600, 360)
        self._devices: dict[str, DeviceInfo] = {}
        self._scanner = BleScanner(self._queue_device, self._queue_complete)
        self._events: list[tuple[str, object]] = []
        self._events_lock = threading.Lock()
        self._build_ui()
        self.after(100, self._process_events)
        self.protocol("WM_DELETE_WINDOW", self._close)

    def _build_ui(self) -> None:
        container = ttk.Frame(self, padding=16)
        container.pack(fill=tk.BOTH, expand=True)
        ttk.Label(container, text="Bluetooth Low Energy scanner", font=("Segoe UI", 16, "bold")).pack(anchor=tk.W)
        ttk.Label(container, text="Find nearby BLE devices and view their signal strength.").pack(anchor=tk.W, pady=(4, 16))

        controls = ttk.Frame(container)
        controls.pack(fill=tk.X, pady=(0, 10))
        self._scan_button = ttk.Button(controls, text="Start scan", command=self._start_scan)
        self._scan_button.pack(side=tk.LEFT)
        self._stop_button = ttk.Button(controls, text="Stop", command=self._stop_scan, state=tk.DISABLED)
        self._stop_button.pack(side=tk.LEFT, padx=(8, 0))
        self._status = ttk.Label(controls, text="Ready")
        self._status.pack(side=tk.RIGHT)

        columns = ("name", "address", "rssi")
        self._table = ttk.Treeview(container, columns=columns, show="headings", selectmode="browse")
        self._table.heading("name", text="Name")
        self._table.heading("address", text="Address")
        self._table.heading("rssi", text="Signal")
        self._table.column("name", width=250, anchor=tk.W)
        self._table.column("address", width=220, anchor=tk.W)
        self._table.column("rssi", width=100, anchor=tk.CENTER)
        self._table.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scrollbar = ttk.Scrollbar(container, orient=tk.VERTICAL, command=self._table.yview)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self._table.configure(yscrollcommand=scrollbar.set)

    def _start_scan(self) -> None:
        if self._scanner.running:
            return
        for item in self._table.get_children():
            self._table.delete(item)
        self._devices.clear()
        self._scan_button.configure(state=tk.DISABLED)
        self._stop_button.configure(state=tk.NORMAL)
        self._status.configure(text="Scanning...")
        self._scanner.start()

    def _stop_scan(self) -> None:
        self._scanner.stop()
        self._status.configure(text="Stopping...")
        self._stop_button.configure(state=tk.DISABLED)

    def _queue_device(self, device: DeviceInfo) -> None:
        with self._events_lock:
            self._events.append(("device", device))

    def _queue_complete(self, error: str | None) -> None:
        with self._events_lock:
            self._events.append(("complete", error))

    def _process_events(self) -> None:
        with self._events_lock:
            events, self._events = self._events, []
        for event, value in events:
            if event == "device":
                self._show_device(value)
            else:
                self._scan_finished(value)
        self.after(100, self._process_events)

    def _show_device(self, device: DeviceInfo) -> None:
        existing = self._devices.get(device.address)
        self._devices[device.address] = device
        if existing is None:
            self._table.insert("", tk.END, iid=device.address, values=(device.name, device.address, device.rssi))
        else:
            self._table.item(device.address, values=(device.name, device.address, device.rssi))
        self._status.configure(text=f"{len(self._devices)} device(s) found")

    def _scan_finished(self, error: str | None) -> None:
        self._scan_button.configure(state=tk.NORMAL)
        self._stop_button.configure(state=tk.DISABLED)
        if error:
            self._status.configure(text="Scan unavailable")
            messagebox.showerror("BLE scan", error, parent=self)
        else:
            self._status.configure(text=f"Scan complete - {len(self._devices)} device(s) found")

    def _close(self) -> None:
        self._scanner.stop()
        self.destroy()


if __name__ == "__main__":
    BleScanApp().mainloop()
