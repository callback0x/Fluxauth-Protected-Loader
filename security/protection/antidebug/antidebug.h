#include <string>
#include "../../security/encryption/base64.h"
#include "../../security/encryption/encrypt.h"
#include <Windows.h>
#include "../../security/encryption/lazy.h"
#include <Psapi.h>
#include <vector>
#include <cwchar>
#include <tchar.h>
#include <Shlwapi.h>
#include <TlHelp32.h>

using namespace base64;

__forceinline BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    DWORD pid = GetCurrentProcessId();



    std::string title = windowTitle;
    std::string searchString = skCrypt("Brocess Racker").decrypt();
    std::string searchString2 = skCrypt("reversehacker").decrypt();
    std::string searchString3 = skCrypt("FileGrab").decrypt();
    std::string searchString4 = skCrypt("[Elevated]").decrypt();
    std::string searchString6 = skCrypt("dexzunpacker").decrypt();
    std::string searchString8 = skCrypt("x64dbg").decrypt();
    std::string searchString10 = skCrypt("Detect It Easy").decrypt();
    std::string searchString9 = skCrypt("ntdll.dll").decrypt();
    std::string searchString7 = skCrypt("1337").decrypt();
    std::string searchString11 = skCrypt("dbg").decrypt();
    std::string searchString12 = skCrypt("debugger").decrypt();
    std::string searchString13 = skCrypt("filewatcher").decrypt();
    std::string searchString14 = skCrypt("hacker").decrypt();
    std::string searchString15 = skCrypt("Beamer x64").decrypt();

    if (title.find(searchString) != std::string::npos ||
        title.find(searchString2) != std::string::npos ||
        title.find(searchString6) != std::string::npos ||
        title.find(searchString8) != std::string::npos ||
        title.find(searchString7) != std::string::npos ||
        title.find(searchString11) != std::string::npos ||
        title.find(searchString12) != std::string::npos ||
        title.find(searchString9) != std::string::npos ||
        title.find(searchString10) != std::string::npos ||
        title.find(searchString14) != std::string::npos ||
        title.find(searchString12) != std::string::npos ||
        title.find(searchString15) != std::string::npos ||
        title.find(searchString4) != std::string::npos) {


        DWORD processId;
        GetWindowThreadProcessId(hwnd, &processId);

        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);

        if (hProcess != NULL) {
            TerminateProcess(hProcess, 0);

            CloseHandle(hProcess);
        }

        (exit)(0);
    }

    return TRUE;
}

bool TerminateProcessUD(DWORD processID)
{
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
    if (hProcess == NULL)
    {

        return false;
    }

    if (TerminateProcess(hProcess, 0))
    {
        CloseHandle(hProcess);
        return true;
    }
    else
    {
        CloseHandle(hProcess);
        return false;
    }
}


__forceinline auto IsVaildSigniture(const char* section_name, bool fix = false) -> bool
{

    const auto map_file = [](HMODULE hmodule) -> std::tuple<std::uintptr_t, HANDLE>
        {
            char filename[MAX_PATH];
            DWORD size = MAX_PATH;
            QueryFullProcessImageNameA(GetCurrentProcess(), 0, filename, &size);

            const auto file_handle = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
            if (!file_handle || file_handle == INVALID_HANDLE_VALUE)
            {
                return { 0ull, nullptr };
            }

            const auto file_mapping = CreateFileMapping(file_handle, 0, PAGE_READONLY, 0, 0, 0);
            if (!file_mapping)
            {
                CloseHandle(file_handle);
                return { 0ull, nullptr };
            }

            return { reinterpret_cast<std::uintptr_t>(MapViewOfFile(file_mapping, FILE_MAP_READ, 0, 0, 0)), file_handle };
        };

    const auto hmodule = GetModuleHandle(0);
    if (!hmodule) return true;

    const auto base_0 = reinterpret_cast<std::uintptr_t>(hmodule);
    if (!base_0) return true;

    const auto dos_0 = reinterpret_cast<IMAGE_DOS_HEADER*>(base_0);
    if (dos_0->e_magic != IMAGE_DOS_SIGNATURE) return true;

    const auto nt_0 = reinterpret_cast<IMAGE_NT_HEADERS*>(base_0 + dos_0->e_lfanew);
    if (nt_0->Signature != IMAGE_NT_SIGNATURE) return true;

    auto section_0 = IMAGE_FIRST_SECTION(nt_0);

    const auto [base_1, file_handle] = map_file(hmodule);
    if (!base_1 || !file_handle || file_handle == INVALID_HANDLE_VALUE) return true;

    const auto dos_1 = reinterpret_cast<IMAGE_DOS_HEADER*>(base_1);
    if (dos_1->e_magic != IMAGE_DOS_SIGNATURE)
    {
        UnmapViewOfFile(reinterpret_cast<void*>(base_1));
        CloseHandle(file_handle);
        return true;
    }

    const auto nt_1 = reinterpret_cast<IMAGE_NT_HEADERS*>(base_1 + dos_1->e_lfanew);
    if (nt_1->Signature != IMAGE_NT_SIGNATURE ||
        nt_1->FileHeader.TimeDateStamp != nt_0->FileHeader.TimeDateStamp ||
        nt_1->FileHeader.NumberOfSections != nt_0->FileHeader.NumberOfSections)
    {
        UnmapViewOfFile(reinterpret_cast<void*>(base_1));
        CloseHandle(file_handle);
        return true;
    }

    auto section_1 = IMAGE_FIRST_SECTION(nt_1);

    bool patched = false;
    for (auto i = 0; i < nt_1->FileHeader.NumberOfSections; ++i, ++section_0, ++section_1)
    {
        if (strcmp(reinterpret_cast<char*>(section_0->Name), section_name) ||
            !(section_0->Characteristics & IMAGE_SCN_MEM_EXECUTE)) continue;

        for (auto i = 0u; i < section_0->SizeOfRawData; ++i)
        {
            const auto old_value = *reinterpret_cast<BYTE*>(base_1 + section_1->PointerToRawData + i);

            if (*reinterpret_cast<BYTE*>(base_0 + section_0->VirtualAddress + i) == old_value)
            {
                continue;
            }

            if (fix)
            {
                DWORD new_protect{ PAGE_EXECUTE_READWRITE }, old_protect;
                VirtualProtect((void*)(base_0 + section_0->VirtualAddress + i), sizeof(BYTE), new_protect, &old_protect);
                *reinterpret_cast<BYTE*>(base_0 + section_0->VirtualAddress + i) = old_value;
                VirtualProtect((void*)(base_0 + section_0->VirtualAddress + i), sizeof(BYTE), old_protect, &new_protect);
            }

            patched = true;
        }

        break;
    }

    UnmapViewOfFile(reinterpret_cast<void*>(base_1));
    CloseHandle(file_handle);

    return patched;
}

int contextthread()
{
    int found = false;
    CONTEXT ctx = { 0 };
    void* h_thread = LI_FN(GetCurrentThread).safe()();

    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    if (LI_FN(GetThreadContext).safe()(h_thread, &ctx))
    {
        if ((ctx.Dr0 != 0x00) || (ctx.Dr1 != 0x00) || (ctx.Dr2 != 0x00) || (ctx.Dr3 != 0x00) || (ctx.Dr6 != 0x00) || (ctx.Dr7 != 0x00))
        {
            found = true;
        }

        if (found == true) {
            (exit)(0);
        }
    }

    return found;
}



bool CheckCloseHandleDebugger()
{
    HANDLE handle = GetCurrentProcess();
    bool isDebugging = false;
    if (!CloseHandle(handle))
    {
        isDebugging = true;
    }
    return isDebugging;
}


__forceinline bool anti_assembly()
{
    __try
    {
        LI_FN(DebugBreak).get()();
    }
    __except (EXCEPTION_BREAKPOINT)
    {
        return false;
    }

    return true;
}
__forceinline void Raise_Check()
{
    __try
    {
        RaiseException(DBG_CONTROL_C, 0, 0, NULL);
    }
    __except (DBG_CONTROL_C == GetExceptionCode()
        ? EXCEPTION_EXECUTE_HANDLER
        : EXCEPTION_CONTINUE_SEARCH)
    {
    }
}

__forceinline void SecureExit(bool debugger)
{
    if (debugger)
    {
        *((unsigned int*)0) = 0x1565;
        __fastfail(0);
        *((unsigned int*)0) = 0x1565;
    }
    else
    {
        *((unsigned int*)0) = 0x1565;
        __fastfail(0);
        *((unsigned int*)0) = 0x1565;
    }
}

