/****************************************************************************

    Модуль init.c

****************************************************************************/

#include <ntddk.h>
#include "process.h"

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
			INIT_VARIABLES(WINXP);
			//INIT_OFFSETS_WINXP();
			break;
		case WIN7_BUILD_NUMBER:
			DbgPrint("Win7\n");
			INIT_VARIABLES(WIN7);
			break;
		case WIN8_BUILD_NUMBER:
			DbgPrint("Win8\n");
			//INIT_VARIABLES(WIN8_1);
			break;
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

	KeServiceDescriptorTable->Base[glSysCallNumbers[_ZwQuerySystemInformation_]] = (ULONG)HookZwQuerySystemInformation;
	
	
	WriteCR0(reg);

}

VOID RemoveAllHook(VOID) {
	
	ULONG reg;

	reg = ClearWP();

	// BASE TASK 0
	KeServiceDescriptorTable->Base[glSysCallNumbers[_ZwQuerySystemInformation_]] = (ULONG)glRealNtQuerySystemInformation;
	

	WriteCR0(reg);

	WaitVar(&glHookCount);
}




//-----------------------------------------------

