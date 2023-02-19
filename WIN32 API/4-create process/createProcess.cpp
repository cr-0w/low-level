#include <stdio.h>
#include <windows.h>

STARTUPINFO startInfo = { };

//HANDLE hThread;
//HANDLE hProcess;
//DWORD dwThreadID;
//DWORD dwProcessID;

PROCESS_INFORMATION procInfo = { 
    //hProcess,
    //hThread,
    //dwProcessID,
    //dwThreadID
};

int main() {

    printf("\n[+] spawning process: notepad.exe");

    if (!CreateProcessW(
        L"C:\\Windows\\System32\\notepad.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &startInfo,
        &procInfo
    )) {

        printf("\n[!] process couldn't be created. you're on your own. good luck.");
        exit(1);
    }

    printf("\n[+] process spawned!");
    printf("\n[+] process ID: %ld", procInfo.dwProcessId);
    printf("\n[+] thread ID: %ld\n", procInfo.dwThreadId);
    
    CloseHandle(procInfo.hProcess);
}
