#ifndef _OFFSETS_H_
#define _OFFSETS_H_

#include "includes.h"





#if NTDDI_VERSION <= NTDDI_WINXP
typedef ULONG	HANDLE_T;
typedef ULONG	PROCESS_T;
typedef ULONG	PETHREAD_T;
#else
typedef HANDLE		HANDLE_T;
typedef PEPROCESS	PEPROCESS_T;
typedef PETHREAD	PETHREAD_T;
#endif // DEBUG

//-----------------------------------------------

typedef enum _SYSCALL_INDEXES_ {
	_ZwQuerySystemInformation_,
	_ZwDeviceIoControlFile_,
	_ZwQueryDirectoryFile_,
	_ZwEnumerateKey_,
	_LastIndex_
}SYSCALL_INDEXES;

//-----------------------------------------------

//-----------------------------------------------

#ifdef _M_IX86


// --------------------------- FOR WINXP


#define SYSCALL_ZwQuerySystemInformation_WINXP_x86	0x00AD
#define SYSCALL_ZwDeviceIoControlFile_WINXP_x86		0x0042
#define SYSCALL_ZwQueryDirectoryFile_WINXP_x86		0x0091
#define SYSCALL_ZwEnumerateKey_WINXP_x86			0x0047


//смещение заголовка очереди потоков в объекте процесса
#define THREAD_LIST_PROCESS_OFFSET_WINXP_x86      0x190

// смещение элемента очереди потоков в объекте потока
#define THREAD_LIST_THREAD_OFFSET_WINXP_x86       0x22c

// смещение стартового адреса потока в объекте потока
#define START_ADDRESS_THREAD_OFFSET_WINXP_x86     0x224

#define WIN32_START_ADDESS_THREAD_OFFSET_WINXP_x86    0x228

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET_WINXP_x86  0x88

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WINXP_x86	0x0c4

// смещение до PID в объекте таблицы хэндлов
#define HANDLE_TABLE_PID_OFFSET_WINXP_x86	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
#define HANDLE_TABLE_PROC_OFFSET_WINXP_x86		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WINXP_x86		0x01c

// смещение до имени в объекте процесса
#define IMAGE_NAME_OFFSET_WINXP_x86				0x174



// --------------------------- FOR WIN7

#define SYSCALL_ZwQuerySystemInformation_WIN7_x86	0x0105
#define SYSCALL_ZwDeviceIoControlFile_WIN7_x86		0x006B
#define SYSCALL_ZwQueryDirectoryFile_WIN7_x86		0x00DF
#define SYSCALL_ZwEnumerateKey_WIN7_x86				0x0074


//смещение заголовка очереди потоков в объекте процесса
#define THREAD_LIST_PROCESS_OFFSET_WIN7_x86      0x188

// смещение элемента очереди потоков в объекте потока
#define THREAD_LIST_THREAD_OFFSET_WIN7_x86       0x268

// смещение стартового адреса потока в объекте потока
#define START_ADDRESS_THREAD_OFFSET_WIN7_x86     0x218

#define WIN32_START_ADDESS_THREAD_OFFSET_WIN7_x86    0x260

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET_WIN7_x86  0x0b8

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WIN7_x86			0x0f4

// смещение до PID в объекте таблицы хэндлов
#define HANDLE_TABLE_PID_OFFSET_WIN7_x86	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
#define HANDLE_TABLE_PROC_OFFSET_WIN7_x86		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WIN7_x86		0x010

// смещение до имени в объекте процесса
#define IMAGE_NAME_OFFSET_WIN7_x86				0x16c

// --------------------------- FOR WIN8.1

#define SYSCALL_ZwQuerySystemInformation_WIN8_1_x86	0x0098
#define SYSCALL_ZwDeviceIoControlFile_WIN8_1_x86	0x0137
#define SYSCALL_ZwQueryDirectoryFile_WIN8_1_x86		0x00BE
#define SYSCALL_ZwEnumerateKey_WIN8_1_x86			0x012E

////смещение заголовка очереди потоков в объекте процесса
//#define THREAD_LIST_PROCESS_OFFSET_WIN7      0x188
//
//// смещение элемента очереди потоков в объекте потока
//#define THREAD_LIST_THREAD_OFFSET_WIN7       0x268
//
//// смещение стартового адреса потока в объекте потока
//#define START_ADDRESS_THREAD_OFFSET_WIN7     0x218
//
//#define WIN32_START_ADDESS_THREAD_OFFSET_WIN7    0x260

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET_WIN8_x86		0x0b8

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WIN8_x86			0x150

// смещение до PID в объекте таблицы хэндлов
//#define HANDLE_TABLE_PID_OFFSET_WIN7_x86	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
//#define HANDLE_TABLE_PROC_OFFSET_WIN7_x86		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WIN8_x86		0x010

// смещение до имени в объекте процесса
//#define IMAGE_NAME_OFFSET_WIN8_x86				0x16c


// --------------------------- FOR WIN10_1903

#define SYSCALL_ZwQuerySystemInformation_WIN10_1903_x86	0x009D
#define SYSCALL_ZwDeviceIoControlFile_WIN10_1903_x86	0x0145	
#define SYSCALL_ZwQueryDirectoryFile_WIN10_1903_x86		0x00C5
#define SYSCALL_ZwEnumerateKey_WIN10_1903_x86			0x013C



// --------------------------- 

#define WINXP		WINXP_x86
#define WIN7		WIN7_x86
#define WIN8_1		WIN8_1_x86
#define WIN10_1903	WIN10_1903_x86


//-----------------------------------------------

#else
// for x64

// --------------------------- FOR WINXP

#define SYSCALL_ZwQuerySystemInformation_WINXP_x64	0x00AD
#define SYSCALL_ZwDeviceIoControlFile_WINXP_x64		0x0042
#define SYSCALL_ZwQueryDirectoryFile_WINXP_x64		0x0091
#define SYSCALL_ZwEnumerateKey_WINXP_x64			0x0047

//смещение заголовка очереди потоков в объекте процесса
#define THREAD_LIST_PROCESS_OFFSET_WINXP_x64      0x190

// смещение элемента очереди потоков в объекте потока
#define THREAD_LIST_THREAD_OFFSET_WINXP_x64       0x22c

// смещение стартового адреса потока в объекте потока
#define START_ADDRESS_THREAD_OFFSET_WINXP_x64     0x224

#define WIN32_START_ADDESS_THREAD_OFFSET_WINXP_x64    0x228

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET_WINXP_x64  0x88

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WINXP_x64	0x0c4

// смещение до PID в объекте таблицы хэндлов
#define HANDLE_TABLE_PID_OFFSET_WINXP_x64	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
#define HANDLE_TABLE_PROC_OFFSET_WINXP_x64		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WINXP_x64		0x01c

// смещение до имени в объекте процесса
#define IMAGE_NAME_OFFSET_WINXP_x64				0x174



// --------------------------- FOR WIN7

#define SYSCALL_ZwQuerySystemInformation_WIN7_x64	0x0105
#define SYSCALL_ZwDeviceIoControlFile_WIN7_x64		0x006B
#define SYSCALL_ZwQueryDirectoryFile_WIN7_x64		0x00DF
#define SYSCALL_ZwEnumerateKey_WIN7_x64				0x0074


//смещение заголовка очереди потоков в объекте процесса
#define THREAD_LIST_PROCESS_OFFSET_WIN7_x64      0x188

// смещение элемента очереди потоков в объекте потока
#define THREAD_LIST_THREAD_OFFSET_WIN7_x64       0x268

// смещение стартового адреса потока в объекте потока
#define START_ADDRESS_THREAD_OFFSET_WIN7_x64     0x218

#define WIN32_START_ADDESS_THREAD_OFFSET_WIN7_x64    0x260

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET_WIN7_x64  0x0b8

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WIN7_x64			0x0f4

// смещение до PID в объекте таблицы хэндлов
#define HANDLE_TABLE_PID_OFFSET_WIN7_x64	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
#define HANDLE_TABLE_PROC_OFFSET_WIN7_x64		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WIN7_x64		0x010

// смещение до имени в объекте процесса
#define IMAGE_NAME_OFFSET_WIN7_x64				0x16c

// --------------------------- FOR WIN8.1

#define SYSCALL_ZwQuerySystemInformation_WIN8_1_x64	0x0098
#define SYSCALL_ZwDeviceIoControlFile_WIN8_1_x64	0x0137
#define SYSCALL_ZwQueryDirectoryFile_WIN8_1_x64		0x00BE
#define SYSCALL_ZwEnumerateKey_WIN8_1_x64			0x012E

////смещение заголовка очереди потоков в объекте процесса
//#define THREAD_LIST_PROCESS_OFFSET_WIN7      0x188
//
//// смещение элемента очереди потоков в объекте потока
//#define THREAD_LIST_THREAD_OFFSET_WIN7       0x268
//
//// смещение стартового адреса потока в объекте потока
//#define START_ADDRESS_THREAD_OFFSET_WIN7     0x218
//
//#define WIN32_START_ADDESS_THREAD_OFFSET_WIN7    0x260

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET_WIN8_x64		0x0b8

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WIN8_x64			0x150

// смещение до PID в объекте таблицы хэндлов
//#define HANDLE_TABLE_PID_OFFSET_WIN7_x64	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
//#define HANDLE_TABLE_PROC_OFFSET_WIN7_x64		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WIN8_x64		0x010

// смещение до имени в объекте процесса
//#define IMAGE_NAME_OFFSET_WIN8_x64				0x16c


// --------------------------- FOR WIN10_1903

#define SYSCALL_ZwQuerySystemInformation_WIN10_1903_x64	0x009D
#define SYSCALL_ZwDeviceIoControlFile_WIN10_1903_x64	0x0145	
#define SYSCALL_ZwQueryDirectoryFile_WIN10_1903_x64		0x00C5
#define SYSCALL_ZwEnumerateKey_WIN10_1903_x64			0x013C

// --------------------------- FOR WIN10_20H2x64

#define SYSCALL_ZwQuerySystemInformation_WIN10_20H2_x64	0x0036
#define SYSCALL_ZwDeviceIoControlFile_WIN10_20H2_x64	0x0007	
#define SYSCALL_ZwQueryDirectoryFile_WIN10_20H2_x64		0x0035
#define SYSCALL_ZwEnumerateKey_WIN10_20H2_x64			0x0032

// --------------------------- 

//смещение заголовка очереди потоков в объекте процесса
#define THREAD_LIST_PROCESS_OFFSET_WIN10_20H2_x64      0x188

// смещение элемента очереди потоков в объекте потока
#define THREAD_LIST_THREAD_OFFSET_WIN10_20H2_x64       0x268

// смещение стартового адреса потока в объекте потока
#define START_ADDRESS_THREAD_OFFSET_WIN10_20H2_x64     0x218

#define WIN32_START_ADDESS_THREAD_OFFSET_WIN10_20H2_x64    0x260

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET_WIN10_20H2_x64  0x0b8

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WIN10_20H2_x64			0x0f4

// смещение до PID в объекте таблицы хэндлов
#define HANDLE_TABLE_PID_OFFSET_WIN10_20H2_x64	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
#define HANDLE_TABLE_PROC_OFFSET_WIN10_20H2_x64		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WIN10_20H2_x64		0x010

// смещение до имени в объекте процесса
#define IMAGE_NAME_OFFSET_WIN10_20H2_x64				0x16c

// --------------------------- 

#define WINXP_x64
#define WIN7_x64
#define WIN8_1_x64
#define WIN10_1903_x64
#define WIN10_20H2_x64

#define WINXP		WINXP_x64
#define WIN7		WIN7_x64
#define WIN8_1		WIN8_1_x64
#define WIN10_1903	WIN10_1903_x64

#define x64
#define ARCH	x64



#endif // M_X86
	
//-----------------------------------------------

#endif

// ---------------------------


// --------------------------- 

ULONG glThreadListProcessOffset;
ULONG glThreadListThreadOffset;
ULONG glStartAddressThreadOffsett;
ULONG glWin32StartAddressThreadOffset;
ULONG glActiveListProcessOffset;
ULONG glHandleTableOffset;
ULONG glHandleTablePidOffset;
ULONG glHandleTableProcOffset;
ULONG glHandleTableListOffset;
ULONG glImageNameOffset;
USHORT glSysCallNumbers[_LastIndex_];

// ---------------------------

// возвращает указатель на заголовок очереди потоков
#define GET_HEAD_THREAD_LIST(process) (LIST_ENTRY*)((SIZE_T) process + glThreadListProcessOffset)

// возвращает указатель на элемент списка процессов объекта процесса
#define GET_ENTRY_PROCESS_LIST(process) (LIST_ENTRY*)((SIZE_T) process + glActiveListProcessOffset)

// возвращает указатель на поток, по соответствующему элементу списка
#define GET_THREAD_BY_LIST_ENTRY(entry) ((SIZE_T) entry - glThreadListThreadOffset)

// возвращает указатель на процесс, по соответствующему элементу списка
#define GET_PROCESS_BY_LIST_ENTRY(entry) ((SIZE_T) entry - glActiveListProcessOffset)

// возвращает стартовый адрес потока
#define GET_START_ADDRESS_THREAD(thread) *( (PSIZE_T)((SIZE_T) thread + glStartAddressThreadOffsett) )

#define GET_WIN32_START_ADDRESS_THREAD(thread) *( (PSIZE_T)((SIZE_T) thread + glWin32StartAddressThreadOffset) )

// Возвращает addr HANDLE_TABLE объекта процесса
#define GET_HANDLE_TABLE(process)	(PSIZE_T)((SIZE_T)process + glHandleTableOffset)

#define GET_HANDLE_TABLE_LIST_ENTRY(handleTable)	(PLIST_ENTRY)((SIZE_T)handleTable + glHandleTableListOffset)

// ---------------------------

#define WINXP_BUILD_NUMBER	2600
#define WIN7_BUILD_NUMBER	7601
#define WIN8_BUILD_NUMBER	9200
#define WIN10_20H2_BUILD_NUMBER	19041


#define INIT_VARIABLES(version)	 \
	glActiveListProcessOffset		= ACTIVE_LIST_PROCESS_OFFSET_##version; \
	glThreadListProcessOffset		= THREAD_LIST_PROCESS_OFFSET_##version; \
	glStartAddressThreadOffsett		= START_ADDRESS_THREAD_OFFSET_##version; \
	glThreadListThreadOffset		= THREAD_LIST_THREAD_OFFSET_##version; \
	glWin32StartAddressThreadOffset = WIN32_START_ADDESS_THREAD_OFFSET_##version; \
	glHandleTableOffset				= HANDLE_TABLE_OFFSET_##version; \
	glHandleTableListOffset			= HANDLE_TABLE_LIST_OFFSET_##version; \
	glHandleTablePidOffset			= HANDLE_TABLE_PID_OFFSET_##version; \
	glHandleTableProcOffset			= HANDLE_TABLE_PROC_OFFSET_##version; \
	glImageNameOffset				= IMAGE_NAME_OFFSET_##version; \
	glSysCallNumbers[_ZwQuerySystemInformation_]	= SYSCALL_ZwQuerySystemInformation_##version; \
	glSysCallNumbers[_ZwDeviceIoControlFile_]		= SYSCALL_ZwDeviceIoControlFile_##version; \
	glSysCallNumbers[_ZwQueryDirectoryFile_]		= SYSCALL_ZwQueryDirectoryFile_##version; \
	glSysCallNumbers[_ZwEnumerateKey_]				= SYSCALL_ZwEnumerateKey_##version; 
