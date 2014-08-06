#include <stdio.h>
#include <windows.h>

BOOL CALLBACK EnumAll(lpszDesktop, lParam){
    printf("[+] WinSta0\\%s\n", lpszDesktop);   
    return 1;
}

//int main(char argc, int argv[]){
    int main(){
    /*if(argc != 2){
        printf("[-] Uso: %s <IP>\n", argv[0]);
        return 0;
    }*/
    
    //Vars - stack overflow :D
    char url[55];
    char ip[] = "10.1.1.115";
    sprintf(url,"/c start iexplore.exe -k http://%s/index.htm", ip);
    
    
    //Handles
    HWINSTA hStation = OpenWindowStation((LPTSTR)"WinSta0", 0, GENERIC_ALL);
    EnumDesktops(hStation, *EnumAll, 0);
    HDESK defDesk = OpenDesktop("Default",0,0,GENERIC_ALL);
    HDESK newDesk = CreateDesktop("SDesktop",0,0,0,GENERIC_ALL,0);
    
    //Checks
    if(!(defDesk && newDesk)){
        printf("[-] ERROR\tEscritorios\t%d\n", GetLastError());
        return 0;
    }
    if(!SwitchDesktop(newDesk)){
        printf("[-] ERROR\tSwitchDesktop\t%d\n", GetLastError());
        return 0;
    }
    if(!SetThreadDesktop(newDesk)){
        printf("[-] ERROR\tSetThreadDesktop\t%d\n", GetLastError());
        return 0;
    }
    
    //Proceso
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.lpDesktop = "CSLDesktop";
    BOOL proc = CreateProcess((LPCTSTR)"c:\\windows\\system32\\cmd.exe", url, 0, 0, 0, 0, 0, 0, &si, &pi);
    if(!proc){
        printf("[-] Fallo creando el proceso en SDesktop: %d\n", GetLastError());
    }
    
    //Failsafe
    MessageBoxA(0,"SDesktop","SDesktop",MB_OK);
    Sleep(3000);
    SwitchDesktop(defDesk);
    SetThreadDesktop(defDesk);
    
    //Limpieza
    CloseHandle(defDesk);
    CloseHandle(newDesk);
    CloseHandle(hStation);
    
    //Check
    EnumDesktops(hStation, *EnumAll, 0);
    return 1;

}
