#ifndef _SYSCALLS_WORK_H_
#define _SYSCALLS_WORK_H_

#include "includes.h"


//-----------------------------------------------

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation = 0,
    SystemPerformanceInformation = 2,
    SystemTimeOfDayInformation = 3,
    SystemProcessInformation = 5,
    SystemProcessorPerformanceInformation = 8,
    SystemInterruptInformation = 23,
    SystemExceptionInformation = 33,
    SystemRegistryQuotaInformation = 37,
    SystemLookasideInformation = 45,
    SystemModuleInformation = 11
} SYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_THREADS {

    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER CreateTime;
    ULONG WaitTime;
    PVOID StartAddress;
    CLIENT_ID ClientId;
    KPRIORITY Priority;
    KPRIORITY BasePriority;
    ULONG ContextSwitchCount;
    //THREAD_STATE State;
    UCHAR State;
    KWAIT_REASON WaitReason;
    //ULONG unknown;
} SYSTEM_THREADS;

typedef struct _SYSTEM_PROCESS {
    ULONG NextEntryDelta;
    ULONG ThreadCount;
    ULONG Reserved1[6];
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ProcessName;
    KPRIORITY BasePriority;
    HANDLE ProcessId;
    ULONG InheritedFromProcessId;
    ULONG HandleCount;
    ULONG Reserved2[2];
    ULONG PrivatePageCount;
    VM_COUNTERS VmCounters;
    IO_COUNTERS IoCounters;
    SYSTEM_THREADS Threads[1];
} SYSTEM_PROCESS;

//-----------------------------------------------

//-----------------------------------------------

// таблица системных вызовов
typedef struct _KSERVICE_TABLE_DESCRIPTOR {
    PULONG_PTR Base;        // массив адресов системных вызовов(сервисов)
    PULONG Count;           // массив счётчиков вызовов сервисов
    ULONG Limit;            // количество вызовов в таблице
    PUCHAR Number;          // массив количества параметров вызовов(в байтах)
} KSERVICE_TABLE_DESCRIPTOR, * PKSERVICE_TABLE_DESCRIPTOR;


extern PKSERVICE_TABLE_DESCRIPTOR KeServiceDescriptorTable;
extern volatile ULONG glHookCount;


//-----------------------------------------------

ULONG ClearWP(void);
void WriteCR0(ULONG reg);
void WaitVar(volatile ULONG* var);


//-----------------------------------------------

#endif