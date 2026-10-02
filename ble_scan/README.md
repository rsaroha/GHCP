# ble_scan

A small Windows desktop application for discovering nearby Bluetooth Low Energy devices.

## Run

```powershell
cd D:\programming\git_rsaroha\GHCP\ble_scan
python -m pip install -r requirements.txt
python ble_scan.py
```

The app uses Tkinter for the UI and `bleak` for Bluetooth Low Energy discovery. Bluetooth must be enabled in Windows, and Windows may require location/Bluetooth permissions for discovery.
