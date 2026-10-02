// Small launcher UI: pick a target .exe to trace and where to write the
// trace file, start/stop capture, and kick off replay -- so using
// gl_capture doesn't require manually copying the hook DLL and setting
// environment variables by hand. Built on wxWidgets; the actual
// injection/process-launch logic below is plain Win32 (CreateProcess,
// VirtualAllocEx, ...) since wx has no equivalent for that.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "shell32.lib")

#include <wx/wx.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/radiobox.h>

#include <string>
#include <vector>

namespace {

struct LaunchOptions {
    std::string executable;
    std::string arguments;
    std::string runDirectory;
    std::string outputTrace;
    bool named = false;
};

LaunchOptions g_launchOptions;

void ReadLaunchOptions() {
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv) return;

    for (int i = 1; i < argc; ++i) {
        const std::wstring option(argv[i]);
        auto value = [&](std::string& destination) {
            if (i + 1 < argc) {
                destination = wxString(argv[++i]).ToStdString();
                g_launchOptions.named = true;
            }
        };
        auto arguments = [&]() {
            if (i + 1 >= argc) return;
            g_launchOptions.arguments = wxString(argv[++i]).ToStdString();
            while (i + 1 < argc) {
                const std::wstring next(argv[i + 1]);
                if (next == L"-e" || next == L"--executable" ||
                    next == L"-i" || next == L"--arguments" ||
                    next == L"-d" || next == L"--directory" ||
                    next == L"-o" || next == L"--output") {
                    break;
                }
                g_launchOptions.arguments += " " + wxString(argv[++i]).ToStdString();
            }
            g_launchOptions.named = true;
        };
        if (option == L"-e" || option == L"--executable") {
            value(g_launchOptions.executable);
        } else if (option == L"-i" || option == L"--arguments") {
            arguments();
        } else if (option == L"-d" || option == L"--directory") {
            value(g_launchOptions.runDirectory);
        } else if (option == L"-o" || option == L"--output") {
            value(g_launchOptions.outputTrace);
        } else if (!g_launchOptions.named && g_launchOptions.executable.empty()) {
            g_launchOptions.executable = wxString(argv[i]).ToStdString();
        } else if (!g_launchOptions.named && g_launchOptions.outputTrace.empty()) {
            g_launchOptions.outputTrace = wxString(argv[i]).ToStdString();
        }
    }
    LocalFree(argv);
}

std::string ExeDir() {
    char path[MAX_PATH];
    GetModuleFileNameA(nullptr, path, MAX_PATH);
    std::string s(path);
    size_t pos = s.find_last_of('\\');
    return pos == std::string::npos ? "" : s.substr(0, pos);
}

std::string DirOf(const std::string& fullPath) {
    size_t pos = fullPath.find_last_of('\\');
    return pos == std::string::npos ? "" : fullPath.substr(0, pos);
}

bool FileExists(const std::string& path) {
    return GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}

// Injects gl_capture_hook.dll into `process` (created with CREATE_SUSPENDED)
// via the classic remote-thread technique: write the DLL's path into the
// target's address space, then have a remote thread call LoadLibraryA on
// it. LoadLibraryA's address is valid across processes on the same
// Windows install since kernel32.dll loads at the same base address in
// every process of a given bitness. Returns once the remote LoadLibraryA
// call (and therefore the hook DLL's DllMain, which does the import-table
// patching) has completed.
bool InjectHookDll(HANDLE process, std::string& error) {
    std::string dllPath = ExeDir() + "\\gl_capture_hook.dll";
    if (!FileExists(dllPath)) {
        error = "gl_capture_hook.dll not found next to this launcher (" + dllPath + "). Build the gl_capture_hook target first.";
        return false;
    }

    size_t pathBytes = dllPath.size() + 1;
    LPVOID remoteMem = VirtualAllocEx(process, nullptr, pathBytes, MEM_COMMIT, PAGE_READWRITE);
    if (!remoteMem) {
        error = "VirtualAllocEx in target process failed (error " + std::to_string(GetLastError()) + ").";
        return false;
    }
    if (!WriteProcessMemory(process, remoteMem, dllPath.c_str(), pathBytes, nullptr)) {
        error = "WriteProcessMemory into target process failed (error " + std::to_string(GetLastError()) + ").";
        VirtualFreeEx(process, remoteMem, 0, MEM_RELEASE);
        return false;
    }

    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
    auto pLoadLibraryA = reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(kernel32, "LoadLibraryA"));
    HANDLE remoteThread = CreateRemoteThread(process, nullptr, 0, pLoadLibraryA, remoteMem, 0, nullptr);
    if (!remoteThread) {
        error = "CreateRemoteThread failed (error " + std::to_string(GetLastError()) + ").";
        VirtualFreeEx(process, remoteMem, 0, MEM_RELEASE);
        return false;
    }

    WaitForSingleObject(remoteThread, INFINITE);
    // Thread exit codes are DWORD (32-bit), so this is LoadLibraryA's real
    // HMODULE return value truncated to its low 32 bits -- not usable as a
    // pointer, but "zero vs. non-zero" (failure vs. success) still holds:
    // a genuine module base address landing on exactly zero there isn't
    // realistically going to happen.
    DWORD loadedModule = 0;
    GetExitCodeThread(remoteThread, &loadedModule);
    CloseHandle(remoteThread);
    VirtualFreeEx(process, remoteMem, 0, MEM_RELEASE);

    if (loadedModule == 0) {
        error = "the target process failed to load gl_capture_hook.dll (LoadLibraryA returned NULL).";
        return false;
    }
    return true;
}

class LauncherFrame : public wxFrame {
public:
    LauncherFrame();

private:
    void OnTargetBrowse(wxCommandEvent&);
    void OnRunDirBrowse(wxCommandEvent&);
    void OnTraceBrowse(wxCommandEvent&);
    void OnReplayBrowse(wxCommandEvent&);
    void OnStart(wxCommandEvent&);
    void OnStop(wxCommandEvent&);
    void OnReplay(wxCommandEvent&);
    void OnCaptureFrame(wxCommandEvent&);
    void OnPollTimer(wxTimerEvent&);
    void OnClose(wxCloseEvent&);

    void AppendStatus(const wxString& line);
    void SetCapturing(bool capturing);
    void StartCapture();
    void FinishCapture(bool killed);
    void StartReplay();

    wxTextCtrl* m_targetEdit = nullptr;
    wxTextCtrl* m_runDirEdit = nullptr;
    wxTextCtrl* m_argsEdit = nullptr;
    wxTextCtrl* m_traceEdit = nullptr;
    wxButton* m_startBtn = nullptr;
    wxButton* m_stopBtn = nullptr;
    wxButton* m_captureFrameBtn = nullptr;
    wxRadioBox* m_captureModeRadio = nullptr;
    wxTextCtrl* m_statusText = nullptr;
    wxTextCtrl* m_replayEdit = nullptr;
    wxButton* m_replayBtn = nullptr;

    wxTimer m_pollTimer; // no owner: events are dispatched through the Bind() on this object itself
    PROCESS_INFORMATION m_childProc{};
    bool m_capturing = false;
    HANDLE m_captureFrameEvent = nullptr;
};

LauncherFrame::LauncherFrame()
    : wxFrame(nullptr, wxID_ANY, "gl_capture launcher", wxDefaultPosition, wxSize(650, 460)) {
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* root = new wxBoxSizer(wxVERTICAL);

    wxButton* targetBrowseBtn = nullptr;
    wxButton* runDirBrowseBtn = nullptr;
    wxButton* traceBrowseBtn = nullptr;
    wxButton* replayBrowseBtn = nullptr;

    auto addRow = [&](const wxString& label, wxTextCtrl** editOut, const wxString& browseLabel,
                       wxButton** browseBtnOut, long editStyle = 0) {
        wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* lbl = new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(120, -1));
        wxTextCtrl* edit = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, editStyle);
        wxButton* browseBtn = new wxButton(panel, wxID_ANY, browseLabel, wxDefaultPosition, wxSize(80, -1));
        row->Add(lbl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
        row->Add(edit, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
        row->Add(browseBtn, 0, wxALIGN_CENTER_VERTICAL);
        *editOut = edit;
        *browseBtnOut = browseBtn;
        return row;
    };

    // Like addRow, but with no browse button -- for fields (just the
    // arguments string, so far) that have nothing sensible to browse for.
    auto addPlainRow = [&](const wxString& label, wxTextCtrl** editOut) {
        wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* lbl = new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(120, -1));
        wxTextCtrl* edit = new wxTextCtrl(panel, wxID_ANY, "");
        row->Add(lbl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
        row->Add(edit, 1, wxALIGN_CENTER_VERTICAL);
        *editOut = edit;
        return row;
    };

    root->Add(addRow("Target executable:", &m_targetEdit, "Browse...", &targetBrowseBtn),
              0, wxEXPAND | wxALL, 12);
    root->Add(addRow("Run directory:", &m_runDirEdit, "Browse...", &runDirBrowseBtn),
              0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 12);
    m_runDirEdit->SetHint("(defaults to the target's own directory)");
    root->Add(addPlainRow("Arguments:", &m_argsEdit),
              0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 12);
    root->Add(addRow("Trace file:", &m_traceEdit, "Browse...", &traceBrowseBtn),
              0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 12);
    targetBrowseBtn->Bind(wxEVT_BUTTON, &LauncherFrame::OnTargetBrowse, this);
    runDirBrowseBtn->Bind(wxEVT_BUTTON, &LauncherFrame::OnRunDirBrowse, this);
    traceBrowseBtn->Bind(wxEVT_BUTTON, &LauncherFrame::OnTraceBrowse, this);

    wxString modeChoices[] = {"Trace all calls", "Capture one frame on demand"};
    m_captureModeRadio = new wxRadioBox(panel, wxID_ANY, "Capture mode", wxDefaultPosition,
                                        wxDefaultSize, 2, modeChoices, 1, wxRA_SPECIFY_ROWS);
    root->Add(m_captureModeRadio, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 12);

    wxBoxSizer* btnRow = new wxBoxSizer(wxHORIZONTAL);
    m_startBtn = new wxButton(panel, wxID_ANY, "Start Capture");
    m_captureFrameBtn = new wxButton(panel, wxID_ANY, "Capture Frame");
    m_stopBtn = new wxButton(panel, wxID_ANY, "Stop");
    m_captureFrameBtn->Enable(false);
    m_stopBtn->Enable(false);
    btnRow->Add(m_startBtn, 0, wxRIGHT, 8);
    btnRow->Add(m_captureFrameBtn, 0, wxRIGHT, 8);
    btnRow->Add(m_stopBtn, 0);
    root->Add(btnRow, 0, wxLEFT | wxRIGHT | wxBOTTOM, 12);
    m_startBtn->Bind(wxEVT_BUTTON, &LauncherFrame::OnStart, this);
    m_captureFrameBtn->Bind(wxEVT_BUTTON, &LauncherFrame::OnCaptureFrame, this);
    m_stopBtn->Bind(wxEVT_BUTTON, &LauncherFrame::OnStop, this);

    root->Add(new wxStaticText(panel, wxID_ANY, "Status:"), 0, wxLEFT | wxRIGHT, 12);
    m_statusText = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                                   wxTE_MULTILINE | wxTE_READONLY);
    root->Add(m_statusText, 1, wxEXPAND | wxALL, 12);

    root->Add(addRow("Replay trace:", &m_replayEdit, "Browse...", &replayBrowseBtn),
              0, wxEXPAND | wxLEFT | wxRIGHT, 12);
    replayBrowseBtn->Bind(wxEVT_BUTTON, &LauncherFrame::OnReplayBrowse, this);
    m_replayBtn = new wxButton(panel, wxID_ANY, "Replay");
    // Tack the Replay button onto the end of the row we just added.
    static_cast<wxBoxSizer*>(root->GetItem(root->GetItemCount() - 1)->GetSizer())
        ->Add(m_replayBtn, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 8);
    root->AddSpacer(12);
    m_replayBtn->Bind(wxEVT_BUTTON, &LauncherFrame::OnReplay, this);

    panel->SetSizer(root);

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(panel, 1, wxEXPAND);
    SetSizer(frameSizer);
    SetMinSize(wxSize(500, 350));

    m_pollTimer.Bind(wxEVT_TIMER, &LauncherFrame::OnPollTimer, this);
    Bind(wxEVT_CLOSE_WINDOW, &LauncherFrame::OnClose, this);

    // Optional CLI args:
    //   gl_capture_ui.exe -e <executable> -i "<arguments>" -d <directory> -o <trace>
    // The older positional form remains supported:
    //   gl_capture_ui.exe <executable> [trace-file]
    std::string initialTarget = g_launchOptions.executable;
    std::string initialTrace = g_launchOptions.outputTrace;
    std::string initialArgs = g_launchOptions.arguments;
    std::string initialRunDir = g_launchOptions.runDirectory;
    // With no target given on the command line, default to the triangle
    // app path used for local capture workflows.
    if (initialTarget.empty()) {
        std::string defaultTarget = "D:\\programming\\git_rsaroha\\GHCP\\vk_ogl_triangle\\build\\Debug\\triangle.exe";
        if (FileExists(defaultTarget)) initialTarget = defaultTarget;
    }
    if (initialTrace.empty()) {
        initialTrace = "D:\\programming\\git_rsaroha\\GHCP\\vk_ogl_triangle\\build\\Debug\\gl_capture.trace";
    }
    if (!initialTarget.empty()) {
        m_targetEdit->SetValue(initialTarget);
    }
    if (!initialArgs.empty()) m_argsEdit->SetValue(initialArgs);
    if (!initialRunDir.empty()) m_runDirEdit->SetValue(initialRunDir);
    if (!initialTrace.empty()) m_traceEdit->SetValue(initialTrace);
}

void LauncherFrame::AppendStatus(const wxString& line) {
    m_statusText->AppendText(line + "\n");
}

void LauncherFrame::SetCapturing(bool capturing) {
    m_capturing = capturing;
    m_startBtn->Enable(!capturing);
    m_stopBtn->Enable(capturing);
    m_captureFrameBtn->Enable(capturing && m_captureModeRadio->GetSelection() == 1 && m_captureFrameEvent != nullptr);
    m_targetEdit->Enable(!capturing);
    m_runDirEdit->Enable(!capturing);
    m_argsEdit->Enable(!capturing);
    m_traceEdit->Enable(!capturing);
    m_captureModeRadio->Enable(!capturing);
}

void LauncherFrame::OnTargetBrowse(wxCommandEvent&) {
    wxFileDialog dlg(this, "Choose target executable", "", "",
                      "Executables (*.exe)|*.exe|All files (*.*)|*.*",
                      wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() != wxID_OK) return;
    std::string p = dlg.GetPath().ToStdString();
    m_targetEdit->SetValue(p);
    if (m_traceEdit->GetValue().IsEmpty()) {
        m_traceEdit->SetValue(DirOf(p) + "\\gl_capture.trace");
    }
}

void LauncherFrame::OnRunDirBrowse(wxCommandEvent&) {
    wxDirDialog dlg(this, "Choose the directory to run the target in", m_runDirEdit->GetValue());
    if (dlg.ShowModal() != wxID_OK) return;
    m_runDirEdit->SetValue(dlg.GetPath());
}

void LauncherFrame::OnTraceBrowse(wxCommandEvent&) {
    wxFileDialog dlg(this, "Choose trace file location", "", m_traceEdit->GetValue(),
                      "Trace files (*.trace)|*.trace|All files (*.*)|*.*",
                      wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() != wxID_OK) return;
    m_traceEdit->SetValue(dlg.GetPath());
}

void LauncherFrame::OnReplayBrowse(wxCommandEvent&) {
    wxFileDialog dlg(this, "Choose trace file to replay", "", "",
                      "Trace files (*.trace)|*.trace|All files (*.*)|*.*",
                      wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() != wxID_OK) return;
    m_replayEdit->SetValue(dlg.GetPath());
}

void LauncherFrame::OnStart(wxCommandEvent&) { StartCapture(); }

void LauncherFrame::OnStop(wxCommandEvent&) {
    AppendStatus("Stopping capture...");
    FinishCapture(true);
}

void LauncherFrame::OnReplay(wxCommandEvent&) { StartReplay(); }

void LauncherFrame::OnCaptureFrame(wxCommandEvent&) {
    if (!m_capturing) {
        AppendStatus("Start capture first.");
        return;
    }
    if (!m_captureFrameEvent) {
        AppendStatus("Capture mode is not 'one frame on demand'.");
        return;
    }
    if (!SetEvent(m_captureFrameEvent)) {
        AppendStatus(wxString::Format("Error: failed to arm next-frame capture (error %lu).", GetLastError()));
        return;
    }
    AppendStatus("CaptureFrame armed: next frame will be traced.");
}

void LauncherFrame::OnPollTimer(wxTimerEvent&) {
    if (!m_childProc.hProcess) return;
    DWORD code = 0;
    if (GetExitCodeProcess(m_childProc.hProcess, &code) && code != STILL_ACTIVE) {
        if (code == 0) {
            AppendStatus("Target process exited normally.");
        } else {
            // Nonzero could be a deliberate exit code or a crash; either
            // way it's worth flagging rather than reporting it the same
            // neutral way as a clean exit.
            AppendStatus(wxString::Format("Error: target process exited with code %lu (may have crashed).", code));
        }
        FinishCapture(false);
    }
}

void LauncherFrame::OnClose(wxCloseEvent& event) {
    if (m_capturing) FinishCapture(true);
    Destroy();
}

void LauncherFrame::StartCapture() {
    std::string targetExe = m_targetEdit->GetValue().ToStdString();
    std::string tracePath = m_traceEdit->GetValue().ToStdString();
    if (targetExe.empty() || !FileExists(targetExe)) {
        AppendStatus("Pick a valid target executable first.");
        return;
    }
    if (tracePath.empty()) {
        AppendStatus("Pick a trace file location first.");
        return;
    }

    // An explicit run directory lets the target find files it expects
    // relative to some other working directory (its data folder, a mod
    // directory, ...) instead of always running from wherever the exe
    // itself lives.
    std::string runDir = m_runDirEdit->GetValue().ToStdString();
    if (runDir.empty()) runDir = DirOf(targetExe);
    if (GetFileAttributesA(runDir.c_str()) == INVALID_FILE_ATTRIBUTES) {
        AppendStatus("Run directory does not exist: " + runDir);
        return;
    }
    std::string args = m_argsEdit->GetValue().ToStdString();
    bool oneFrameMode = m_captureModeRadio->GetSelection() == 1;

    SetEnvironmentVariableA("GLCAP_TRACE_PATH", tracePath.c_str());
    SetEnvironmentVariableA("GLCAP_CAPTURE_MODE", oneFrameMode ? "oneframe" : "all");
    if (m_captureFrameEvent) {
        CloseHandle(m_captureFrameEvent);
        m_captureFrameEvent = nullptr;
    }
    SetEnvironmentVariableA("GLCAP_CAPTURE_EVENT", nullptr);
    if (oneFrameMode) {
        std::string eventName = "Local\\GLCAP_CAPTURE_FRAME_" +
                                std::to_string(GetCurrentProcessId()) + "_" +
                                std::to_string(static_cast<unsigned long long>(GetTickCount64()));
        m_captureFrameEvent = CreateEventA(nullptr, FALSE, FALSE, eventName.c_str());
        if (!m_captureFrameEvent) {
            AppendStatus(wxString::Format("Error: failed to create capture event (error %lu).", GetLastError()));
            return;
        }
        SetEnvironmentVariableA("GLCAP_CAPTURE_EVENT", eventName.c_str());
    }

    // Launched suspended so the hook DLL's import-table patching (done in
    // its DllMain, run synchronously by the injection below) completes
    // before the target's own code -- and therefore its first GL/WGL
    // call -- ever runs.
    STARTUPINFOA si{};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{};
    std::string cmdLine = "\"" + targetExe + "\"";
    if (!args.empty()) cmdLine += " " + args;
    std::vector<char> cmdBuf(cmdLine.begin(), cmdLine.end());
    cmdBuf.push_back('\0');

    BOOL ok = CreateProcessA(targetExe.c_str(), cmdBuf.data(), nullptr, nullptr, FALSE, CREATE_SUSPENDED,
                              nullptr, runDir.c_str(), &si, &pi);
    if (!ok) {
        AppendStatus(wxString::Format("Error: failed to launch target (error %lu).", GetLastError()));
        if (m_captureFrameEvent) {
            CloseHandle(m_captureFrameEvent);
            m_captureFrameEvent = nullptr;
        }
        return;
    }

    std::string error;
    if (!InjectHookDll(pi.hProcess, error)) {
        AppendStatus("Error: " + error);
        TerminateProcess(pi.hProcess, 1);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        if (m_captureFrameEvent) {
            CloseHandle(m_captureFrameEvent);
            m_captureFrameEvent = nullptr;
        }
        return;
    }
    if (ResumeThread(pi.hThread) == static_cast<DWORD>(-1)) {
        // Left suspended otherwise -- without this check the UI would
        // report "Capturing" on a target that can never actually run.
        AppendStatus(wxString::Format("Error: failed to resume target's main thread (error %lu).", GetLastError()));
        TerminateProcess(pi.hProcess, 1);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        if (m_captureFrameEvent) {
            CloseHandle(m_captureFrameEvent);
            m_captureFrameEvent = nullptr;
        }
        return;
    }

    m_childProc = pi;
    SetCapturing(true);
    if (oneFrameMode) {
        AppendStatus(wxString::Format("Running PID %lu (on-demand frame capture) -> %s", pi.dwProcessId, tracePath.c_str()));
    } else {
        AppendStatus(wxString::Format("Capturing PID %lu -> %s", pi.dwProcessId, tracePath.c_str()));
    }
    m_pollTimer.Start(500);
}

void LauncherFrame::FinishCapture(bool killed) {
    m_pollTimer.Stop();
    if (m_childProc.hProcess) {
        if (killed) TerminateProcess(m_childProc.hProcess, 1);
        CloseHandle(m_childProc.hProcess);
        CloseHandle(m_childProc.hThread);
        m_childProc = {};
    }
    if (m_captureFrameEvent) {
        CloseHandle(m_captureFrameEvent);
        m_captureFrameEvent = nullptr;
    }
    SetCapturing(false);

    std::string tracePath = m_traceEdit->GetValue().ToStdString();
    WIN32_FILE_ATTRIBUTE_DATA attr{};
    if (GetFileAttributesExA(tracePath.c_str(), GetFileExInfoStandard, &attr)) {
        ULONGLONG size = (static_cast<ULONGLONG>(attr.nFileSizeHigh) << 32) | attr.nFileSizeLow;
        AppendStatus(wxString::Format("Capture finished: %llu bytes written to %s", size, tracePath.c_str()));
        m_replayEdit->SetValue(tracePath);
    } else {
        AppendStatus("Error: capture finished, but no trace file was found at " + tracePath);
    }
}

void LauncherFrame::StartReplay() {
    std::string tracePath = m_replayEdit->GetValue().ToStdString();
    if (tracePath.empty() || !FileExists(tracePath)) {
        AppendStatus("Pick a valid trace file to replay first.");
        return;
    }
    std::string replayExe = ExeDir() + "\\gl_replay.exe";
    if (!FileExists(replayExe)) {
        AppendStatus("Error: gl_replay.exe not found next to this launcher.");
        return;
    }

    std::string cmdLine = "\"" + replayExe + "\" \"" + tracePath + "\"";
    std::vector<char> cmdBuf(cmdLine.begin(), cmdLine.end());
    cmdBuf.push_back('\0');

    STARTUPINFOA si{};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{};
    std::string exeDir = ExeDir();
    if (!CreateProcessA(replayExe.c_str(), cmdBuf.data(), nullptr, nullptr, FALSE, 0,
                         nullptr, exeDir.c_str(), &si, &pi)) {
        AppendStatus(wxString::Format("Error: failed to launch gl_replay.exe (error %lu).", GetLastError()));
        return;
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    AppendStatus("Replaying " + tracePath);
}

class LauncherApp : public wxApp {
public:
    bool OnCmdLineParsed(wxCmdLineParser&) override {
        return true;
    }

    bool OnCmdLineError(wxCmdLineParser&) override {
        // ReadLaunchOptions() parses the original Windows command line.
        // wxWidgets' built-in parser rejects switches it does not know.
        return true;
    }

    bool OnInit() override {
        ReadLaunchOptions();
        if (!wxApp::OnInit()) return false;
        LauncherFrame* frame = new LauncherFrame();
        frame->Show();
        return true;
    }
};

} // namespace

wxIMPLEMENT_APP(LauncherApp);
