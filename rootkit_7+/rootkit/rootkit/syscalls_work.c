#include "syscalls_work.h"



volatile ULONG glHookCount = 0;



//
// Очищает бит WP в регистре cr0.
// Возвращает прежнее значение.
//
ULONG ClearWP(void) {

    ULONG reg;

    __asm {
        mov eax, cr0
        mov[reg], eax
        and eax, 0xFFFEFFFF
        mov cr0, eax
    }

    return reg;
}


//--------------------

//
// Загружает значение в регистр cr0.
//
void WriteCR0(ULONG reg) {

    __asm {
        mov eax, [reg]
        mov cr0, eax
    }

}


//--------------------

//
// Ожидает обнуления переменной.
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