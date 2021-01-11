/****************************************************************************

    ������ init.c

    ������� ������� ������� ���������� � ���� ��������� � �������.

    ������ ���� �������������               13.05.2009

****************************************************************************/

#include <ntddk.h>

//*************************************************************
// ���������

// �������� ����� �������� � ������� ��������
#define IMAGE_NAME_PROCESS_OFFSET   0x174

// �������� �������������� �������� � ������� ��������
#define PID_PROCESS_OFFSET          0x84

// �������� �������� ����������� ������ ���� ��������� � ������� ��������
#define ACTIVE_LIST_PROCESS_OFFSET  0x88

// �������� ��������� �� ��� �������� �� ��������� �� �������
#define GET_NAME_PROCESS(process) ((char*)process+IMAGE_NAME_PROCESS_OFFSET)

// �������� ��������� �� ��������� ������� � ������
#define GET_NEXT_PROCESS(process) ( ( (ULONG) ((LIST_ENTRY*)((ULONG)process + ACTIVE_LIST_PROCESS_OFFSET))->Flink ) - ACTIVE_LIST_PROCESS_OFFSET )


//*************************************************************
// ��������������� ���������� �������

NTSTATUS DriverEntry (IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath);
VOID DriverUnload (IN PDRIVER_OBJECT DriverObject);

void InfoProcess(ULONG process);
void ShowAllProcess(ULONG start_process);

//*************************************************************
// �������� �������

// ������� ������������� ��������
NTSTATUS DriverEntry (IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath){

#if DBG
    DbgPrint("Load driver %wZ\n",&DriverObject->DriverName);
#endif

    DriverObject->DriverUnload = DriverUnload;

    // ������� ���������� � ���������
    ShowAllProcess((ULONG)PsGetCurrentProcess());

    return STATUS_SUCCESS;
}

//----------------------------------------

// ������� �������� ��������
VOID DriverUnload (IN PDRIVER_OBJECT DriverObject){

#if DBG
    DbgPrint("Driver unload\n");
#endif

    return;
}

//----------------------------------------

//
// ������� ����������� ���������� � �������� process
//
void InfoProcess(ULONG process){

char name[20];
ULONG pid;

    // ��� ��������
    RtlCopyMemory(name,GET_NAME_PROCESS(process),16);
    name[16] = 0;

    // ������������� ��������
    pid = *( (ULONG*) (process + PID_PROCESS_OFFSET) );

    // ������� ����������
    DbgPrint("Process %p:\n",process);
    DbgPrint("%d   %s\n\n",pid,name);

    return;
}

//----------------------------------------

//
// ���������� ���������� � ���� ��������� � �������.
// ������� ���������� ������ ���������, ������� � start_process
//
void ShowAllProcess(ULONG start_process){

ULONG current;

    current = start_process;

    // ������� ������, ���� �� ������� � ������
    do{
        // ������� ���������� ��� ���������� ��������
        InfoProcess(current);

        // �������� ��������� �� ��������� �������
        current = (ULONG) GET_NEXT_PROCESS(current);
        }
    while(current != start_process);

    return;
}

//----------------------------------------

//----------------------------------------

