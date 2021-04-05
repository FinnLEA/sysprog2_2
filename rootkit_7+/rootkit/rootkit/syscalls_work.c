#include "syscalls_work.h"



volatile ULONG glHookCount = 0;



//
// ������� ��� WP � �������� cr0.
// ���������� ������� ��������.
//
ULONG ClearWP(void) {
    ULONG reg = 0;

#ifdef _M_IX86
    __asm {
        mov eax, cr0
        mov[reg], eax
        and eax, 0xFFFEFFFF
        mov cr0, eax
    }
#endif

    return reg;
}


//--------------------

//
// ��������� �������� � ������� cr0.
//
void WriteCR0(ULONG reg) {
#ifdef _M_IX86
    __asm {
        mov eax, [reg]
        mov cr0, eax
    }
#else
    UNREFERENCED_PARAMETER(reg);
#endif
}


//--------------------

//
// ������� ��������� ����������.
//
void WaitVar(volatile ULONG* var) {

    KEVENT event;
    LARGE_INTEGER time;

    time.QuadPart = -10000000;

    KeInitializeEvent(&event, SynchronizationEvent, FALSE);

    while (*var) {
        KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, &time);
    }

    return;
}


//--------------------