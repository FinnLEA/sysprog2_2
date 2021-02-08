#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "includes.h"


//-----------------------------------------------

#define TARGET_NAME "System"
#define TARGET_PID	4


LIST_ENTRY *PsActiveProcessHead;
PLIST_ENTRY PsActiveHandleTableHead;


ULONG glTotalProcess;
ULONG glTotalThread;
SIZE_T glTargetProcess;
SIZE_T glTargetHandleTable;

extern ULONG glThreadListProcessOffset;
extern ULONG glThreadListThreadOffset;
extern ULONG glStartAddressThreadOffsett;
extern ULONG glWin32StartAddressThreadOffset;
extern ULONG glActiveListProcessOffset;
extern ULONG glHandleTableOffset;
extern ULONG glHandleTablePidOffset;
extern ULONG glHandleTableProcOffset;
extern ULONG glHandleTableListOffset;
extern ULONG glImageNameOffset;

//-----------------------------------------------

//-----------------------------------------------

void DeleteFromProcessListByName(PCHAR TargetImageName);
void DeleteFromProcessListByPid(ULONG TargetPid);
void DeleteFromProcessList(PLIST_ENTRY targetListEntry, ULONG targetProcess);
void DeleteFromHandleTable(SIZE_T AddrHandleTable);
void InsertProcessEntry();
void InsertHandleTableEntry();

void DeleteEntryFromList(PLIST_ENTRY TargetEntry);
void InsertEntryInList(PLIST_ENTRY prevTargetEntry, PLIST_ENTRY TargetEntry);


void InfoThread(ULONG process);
void ShowAllThreadProcess(ULONG start_process);
void InfoProcess(ULONG process);
void ShowAllProcess(void);

//extern NTSTATUS PsLookupProcessByProcessId (HANDLE ProcessId, PEPROCESS *Process);
extern char* PsGetProcessImageFileName(ULONG process);
//extern ULONG PsGetProcessId(ULONG process);
extern ULONG PsGetThreadProcess(ULONG thread);
//extern ULONG PsGetThreadId(ULONG thread);
//extern ULONG PsGetThreadProcessId(ULONG thread);

//-----------------------------------------------

//-----------------------------------------------

#endif