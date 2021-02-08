#ifndef _OFFSETS_H_
#define _OFFSETS_H_

#include "includes.h"

// --------------------------- FOR WINXP

#if NTDDI_VERSION <= NTDDI_WINXP
typedef ULONG	HANDLE_T;
typedef ULONG	PROCESS_T;
typedef ULONG	PETHREAD_T;
#else
typedef HANDLE		HANDLE_T;
typedef PEPROCESS	PROCESS_T;
typedef PETHREAD	PETHREAD_T;
#endif // DEBUG


//смещение заголовка очереди потоков в объекте процесса
#define THREAD_LIST_PROCESS_OFFSET_WINXP      0x190

// смещение элемента очереди потоков в объекте потока
#define THREAD_LIST_THREAD_OFFSET_WINXP       0x22c

// смещение стартового адреса потока в объекте потока
#define START_ADDRESS_THREAD_OFFSET_WINXP     0x224

#define WIN32_START_ADDESS_THREAD_OFFSET_WINXP    0x228

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET_WINXP  0x88

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WINXP	0x0c4

// смещение до PID в объекте таблицы хэндлов
#define HANDLE_TABLE_PID_OFFSET_WINXP	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
#define HANDLE_TABLE_PROC_OFFSET_WINXP		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WINXP		0x01c

// смещение до имени в объекте процесса
#define IMAGE_NAME_OFFSET_WINXP				0x174

// --------------------------- FOR WIN7

//смещение заголовка очереди потоков в объекте процесса
#define THREAD_LIST_PROCESS_OFFSET_WIN7      0x188

// смещение элемента очереди потоков в объекте потока
#define THREAD_LIST_THREAD_OFFSET_WIN7       0x268

// смещение стартового адреса потока в объекте потока
#define START_ADDRESS_THREAD_OFFSET_WIN7     0x218

#define WIN32_START_ADDESS_THREAD_OFFSET_WIN7    0x260

// смещение элемента двусвязного списка всех процессов в объекте процесса
#define ACTIVE_LIST_PROCESS_OFFSET_WIN7  0x0b8

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WIN7			0x0f4

// смещение до PID в объекте таблицы хэндлов
#define HANDLE_TABLE_PID_OFFSET_WIN7	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
#define HANDLE_TABLE_PROC_OFFSET_WIN7		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WIN7		0x010

// смещение до имени в объекте процесса
#define IMAGE_NAME_OFFSET_WIN7				0x16c

// --------------------------- FOR WIN8

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
#define ACTIVE_LIST_PROCESS_OFFSET_WIN8		0x0b8

// смещение до _HANDLE_TABLE в объекте процесса
#define HANDLE_TABLE_OFFSET_WIN8			0x150

// смещение до PID в объекте таблицы хэндлов
//#define HANDLE_TABLE_PID_OFFSET_WIN7	0x08

// смещение до адреса объекта процесса в объекте табл. хэндлов
//#define HANDLE_TABLE_PROC_OFFSET_WIN7		0x04

// смещение до списка объектов табл. хэндлов в объекте табл. хэндлов
#define HANDLE_TABLE_LIST_OFFSET_WIN8		0x010

// смещение до имени в объекте процесса
//#define IMAGE_NAME_OFFSET_WIN8				0x16c

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

// ---------------------------

// возвращает указатель на заголовок очереди потоков
#define GET_HEAD_THREAD_LIST(process) (LIST_ENTRY*)((ULONG) process + glThreadListProcessOffset)

// возвращает указатель на элемент списка процессов объекта процесса
#define GET_ENTRY_PROCESS_LIST(process) (LIST_ENTRY*)((ULONG) process + glActiveListProcessOffset)

// возвращает указатель на поток, по соответствующему элементу списка
#define GET_THREAD_BY_LIST_ENTRY(entry) ((ULONG) entry - glThreadListThreadOffset)

// возвращает указатель на процесс, по соответствующему элементу списка
#define GET_PROCESS_BY_LIST_ENTRY(entry) ((ULONG) entry - glActiveListProcessOffset)

// возвращает стартовый адрес потока
#define GET_START_ADDRESS_THREAD(thread) *( (PULONG)((ULONG) thread + glStartAddressThreadOffsett) )

#define GET_WIN32_START_ADDRESS_THREAD(thread) *( (PULONG)((ULONG) thread + glWin32StartAddressThreadOffset) )

// Возвращает addr HANDLE_TABLE объекта процесса
#define GET_HANDLE_TABLE(process)	(ULONG*)((ULONG)process + glHandleTableOffset)

#define GET_HANDLE_TABLE_LIST_ENTRY(handleTable)	(PLIST_ENTRY)((ULONG)handleTable + glHandleTableListOffset)

//*************************************************************

// ---------------------------
#define WINXP_BUILD_NUMBER	2600
#define WIN7_BUILD_NUMBER	7601
#define WIN8_BUILD_NUMBER	9200

//#define WINXP
//#define WIN7

#define INIT_OFFSETS_WINXP()	 \
	glActiveListProcessOffset		= ACTIVE_LIST_PROCESS_OFFSET_WINXP; \
	glThreadListProcessOffset		= THREAD_LIST_PROCESS_OFFSET_WINXP; \
	glStartAddressThreadOffsett		= START_ADDRESS_THREAD_OFFSET_WINXP; \
	glThreadListThreadOffset		= THREAD_LIST_THREAD_OFFSET_WINXP; \
	glWin32StartAddressThreadOffset = WIN32_START_ADDESS_THREAD_OFFSET_WINXP; \
	glHandleTableOffset				= HANDLE_TABLE_OFFSET_WINXP; \
	glHandleTableListOffset			= HANDLE_TABLE_LIST_OFFSET_WINXP; \
	glHandleTablePidOffset			= HANDLE_TABLE_PID_OFFSET_WINXP; \
	glHandleTableProcOffset			= HANDLE_TABLE_PROC_OFFSET_WINXP; \
	glImageNameOffset				= IMAGE_NAME_OFFSET_WINXP;

#define INIT_OFFSETS_WIN7()		\
	glActiveListProcessOffset		= ACTIVE_LIST_PROCESS_OFFSET_WIN7; \
	glThreadListProcessOffset		= THREAD_LIST_PROCESS_OFFSET_WIN7; \
	glStartAddressThreadOffsett		= START_ADDRESS_THREAD_OFFSET_WIN7; \
	glThreadListThreadOffset		= THREAD_LIST_THREAD_OFFSET_WIN7; \
	glWin32StartAddressThreadOffset = WIN32_START_ADDESS_THREAD_OFFSET_WIN7; \
	glHandleTableOffset				= HANDLE_TABLE_OFFSET_WIN7; \
	glHandleTableListOffset			= HANDLE_TABLE_LIST_OFFSET_WIN7; \
	glHandleTablePidOffset			= HANDLE_TABLE_PID_OFFSET_WIN7; \
	glHandleTableProcOffset			= HANDLE_TABLE_PROC_OFFSET_WIN7; \
	glImageNameOffset				= IMAGE_NAME_OFFSET_WIN7;

#define INIT_OFFSETS_WIN8()		\
	glHandleTableOffset				= HANDLE_TABLE_OFFSET_WIN8; \
	glHandleTableListOffset			= HANDLE_TABLE_LIST_OFFSET_WIN8; \
	glActiveListProcessOffset		= ACTIVE_LIST_PROCESS_OFFSET_WIN8

// ---------------------------


#endif