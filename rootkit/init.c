/****************************************************************************

    Модуль init.c

    Драйвер выводит краткую информацию о всех процессах в системе.

    Маткин Илья Александрович               13.05.2009

****************************************************************************/

#include <ntddk.h>

//*************************************************************
// константы

// смещение имени процесса в объекте процесса
#define IMAGE_NAME_PROCESS_OFFSET   0x174

// смещение идентификатора процесса в объекте процесса
#define PID_PROCESS_OFFSET          0x84

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET  0x88

// получает указатель на имя процесса по указателю на процесс
#define GET_NAME_PROCESS(process) ((char*)process+IMAGE_NAME_PROCESS_OFFSET)

// получает указатель на следующий процесс в списке
#define GET_NEXT_PROCESS(process) ( ( (ULONG) ((LIST_ENTRY*)((ULONG)process + ACTIVE_LIST_PROCESS_OFFSET))->Flink ) - ACTIVE_LIST_PROCESS_OFFSET )


//*************************************************************
// предварительное объявление функций

NTSTATUS DriverEntry (IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath);
VOID DriverUnload (IN PDRIVER_OBJECT DriverObject);

void InfoProcess(ULONG process);
void ShowAllProcess(ULONG start_process);

//*************************************************************
// описание функций

// функция инициализации драйвера
NTSTATUS DriverEntry (IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath){

#if DBG
    DbgPrint("Load driver %wZ\n",&DriverObject->DriverName);
#endif

    DriverObject->DriverUnload = DriverUnload;

    // выводим информацию о процессах
    ShowAllProcess((ULONG)PsGetCurrentProcess());

    return STATUS_SUCCESS;
}

//----------------------------------------

// функция выгрузки драйвера
VOID DriverUnload (IN PDRIVER_OBJECT DriverObject){

#if DBG
    DbgPrint("Driver unload\n");
#endif

    return;
}

//----------------------------------------

//
// Выводит минимальную информацию о процессе process
//
void InfoProcess(ULONG process){

char name[20];
ULONG pid;

    // имя процесса
    RtlCopyMemory(name,GET_NAME_PROCESS(process),16);
    name[16] = 0;

    // идентификатор процесса
    pid = *( (ULONG*) (process + PID_PROCESS_OFFSET) );

    // выводим информацию
    DbgPrint("Process %p:\n",process);
    DbgPrint("%d   %s\n\n",pid,name);

    return;
}

//----------------------------------------

//
// Отображает информацию о всех процессах в системе.
// Обходит двусвязный список процессов, начиная с start_process
//
void ShowAllProcess(ULONG start_process){

ULONG current;

    current = start_process;

    // обходим список, пока не вернёмся к началу
    do{
        // выводим информацию для очередного процесса
        InfoProcess(current);

        // получаем указатель на следующий процесс
        current = (ULONG) GET_NEXT_PROCESS(current);
        }
    while(current != start_process);

    return;
}

//----------------------------------------

//----------------------------------------

