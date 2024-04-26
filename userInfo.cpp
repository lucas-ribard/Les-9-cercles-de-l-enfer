#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <lm.h> // Inclure lm.h pour utiliser NetUserGetLocalGroups

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "netapi32.lib") // Lier netapi32.lib




bool IsWindows10OrGreater() {
    OSVERSIONINFOEX osvi;
    DWORDLONG dwlConditionMask = 0;
    int op = VER_GREATER_EQUAL;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    osvi.dwMajorVersion = 10;
    osvi.dwMinorVersion = 0;

    VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, op);
    VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, op);

    return VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask) != FALSE;
}

void ListProcesses() {
    // Cr�er un snapshot des processus en cours d'ex�cution
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Erreur lors de la cr�ation du snapshot des processus.\n";
        return;
    }

    // Initialiser la structure PROCESSENTRY32
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // R�cup�rer les informations sur le premier processus
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        std::cerr << "Erreur lors de la r�cup�ration des informations sur le premier processus.\n";
        return;
    }

    // Afficher la liste des processus
    std::cout << "Liste des processus en cours d'ex�cution :\n";
    do {
        std::wcout << "Nom : " << pe32.szExeFile << ", PID : " << pe32.th32ProcessID << std::endl;
    } while (Process32Next(hProcessSnap, &pe32));

    // Fermer le handle du snapshot
    CloseHandle(hProcessSnap);
}

int main() {
    // R�cup�rer le nom de l'ordinateur
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    if (!GetComputerNameA(computerName, &size)) {
        std::cerr << "Erreur lors de la r�cup�ration du nom de l'ordinateur.\n";
        return 1;
    }
    std::cout << "Nom de l'ordinateur : " << computerName << std::endl;

    // R�cup�rer le nombre de processeurs
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    std::cout << "Nombre de processeurs : " << systemInfo.dwNumberOfProcessors << std::endl;

    // R�cup�rer la m�moire restante
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);
    std::cout << "M�moire restante : " << memoryStatus.ullAvailPhys << " octets\n";

    // Afficher des informations sur le syst�me d'exploitation
    std::cout << "Syst�me d'exploitation : ";
    if (IsWindows10OrGreater()) {
        std::cout << "Windows 10 ou version ult�rieure\n";
    }
    else {
        std::cout << "Une version ant�rieure de Windows\n";
    }

    // R�cup�rer le nom d'utilisateur Windows
    char username[UNLEN + 1];
    size = UNLEN + 1;
    if (!GetUserNameA(username, &size)) {
        std::cerr << "Erreur lors de la r�cup�ration du nom d'utilisateur.\n";
        return 1;
    }
    std::cout << "Nom d'utilisateur : " << username << std::endl;

    // R�cup�rer les groupes d'appartenance de l'utilisateur Windows
    wchar_t usernameW[UNLEN + 1];
    size = UNLEN + 1;
    if (!MultiByteToWideChar(CP_ACP, 0, username, -1, usernameW, UNLEN + 1)) {
        std::cerr << "Erreur lors de la conversion du nom d'utilisateur.\n";
        return 1;
    }

    LOCALGROUP_USERS_INFO_0* groups;
    DWORD entriesRead, totalEntries;
    DWORD result = NetUserGetLocalGroups(nullptr, usernameW, 0, LG_INCLUDE_INDIRECT, (LPBYTE*)&groups, MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries);
    if (result == NERR_Success) {
        std::cout << "Groupes d'appartenance :\n";
        for (DWORD i = 0; i < entriesRead; ++i) {
            std::wcout << groups[i].lgrui0_name << std::endl;
        }
        NetApiBufferFree(groups);
    }
    else {
        std::cerr << "Erreur lors de la r�cup�ration des groupes d'appartenance.\n";
    }

    // Afficher la liste des processus en cours d'ex�cution
    ListProcesses();

    return 0;
}
