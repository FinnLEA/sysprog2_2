#ifndef _OFFSETS_H_
#define _OFFSETS_H_

#include "includes.h"



#ifdef _M_IX86


#if NTDDI_VERSION <= NTDDI_WINXP
typedef ULONG	HANDLE_T;
typedef ULONG	PROCESS_T;
typedef ULONG	PETHREAD_T;
#else
typedef HANDLE		HANDLE_T;
typedef PEPROCESS	PROCESS_T;
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

// --------------------------- FOR WINXP


#define SYSCALL_ZwQuerySystemInformation_WINXP	0x00AD
#define SYSCALL_ZwDeviceIoControlFile_WINXP		0x0042
#define SYSCALL_ZwQueryDirectoryFile_WINXP		0x0091
#define SYSCALL_ZwEnumerateKey_WINXP			0x0047


//�������� ��������� ������� ������� � ������� ��������
#define THREAD_LIST_PROCESS_OFFSET_WINXP      0x190

// �������� �������� ������� ������� � ������� ������
#define THREAD_LIST_THREAD_OFFSET_WINXP       0x22c

// �������� ���������� ������ ������ � ������� ������
#define START_ADDRESS_THREAD_OFFSET_WINXP     0x224

#define WIN32_START_ADDESS_THREAD_OFFSET_WINXP    0x228

// �������� �������� ����������� ������ ���� ��������� � ������� ��������
#define ACTIVE_LIST_PROCESS_OFFSET_WINXP  0x88

// �������� �� _HANDLE_TABLE � ������� ��������
#define HANDLE_TABLE_OFFSET_WINXP	0x0c4

// �������� �� PID � ������� ������� �������
#define HANDLE_TABLE_PID_OFFSET_WINXP	0x08

// �������� �� ������ ������� �������� � ������� ����. �������
#define HANDLE_TABLE_PROC_OFFSET_WINXP		0x04

// �������� �� ������ �������� ����. ������� � ������� ����. �������
#define HANDLE_TABLE_LIST_OFFSET_WINXP		0x01c

// �������� �� ����� � ������� ��������
#define IMAGE_NAME_OFFSET_WINXP				0x174



// --------------------------- FOR WIN7

#define SYSCALL_ZwQuerySystemInformation_WIN7	0x0105
#define SYSCALL_ZwDeviceIoControlFile_WIN7		0x006B
#define SYSCALL_ZwQueryDirectoryFile_WIN7		0x00DF
#define SYSCALL_ZwEnumerateKey_WIN7				0x0074


//�������� ��������� ������� ������� � ������� ��������
#define THREAD_LIST_PROCESS_OFFSET_WIN7      0x188

// �������� �������� ������� ������� � ������� ������
#define THREAD_LIST_THREAD_OFFSET_WIN7       0x268

// �������� ���������� ������ ������ � ������� ������
#define START_ADDRESS_THREAD_OFFSET_WIN7     0x218

#define WIN32_START_ADDESS_THREAD_OFFSET_WIN7    0x260

// �������� �������� ����������� ������ ���� ��������� � ������� ��������
#define ACTIVE_LIST_PROCESS_OFFSET_WIN7  0x0b8

// �������� �� _HANDLE_TABLE � ������� ��������
#define HANDLE_TABLE_OFFSET_WIN7			0x0f4

// �������� �� PID � ������� ������� �������
#define HANDLE_TABLE_PID_OFFSET_WIN7	0x08

// �������� �� ������ ������� �������� � ������� ����. �������
#define HANDLE_TABLE_PROC_OFFSET_WIN7		0x04

// �������� �� ������ �������� ����. ������� � ������� ����. �������
#define HANDLE_TABLE_LIST_OFFSET_WIN7		0x010

// �������� �� ����� � ������� ��������
#define IMAGE_NAME_OFFSET_WIN7				0x16c

// --------------------------- FOR WIN8.1

#define SYSCALL_ZwQuerySystemInformation_WIN8_1	0x0098
#define SYSCALL_ZwDeviceIoControlFile_WIN8_1	0x0137
#define SYSCALL_ZwQueryDirectoryFile_WIN8_1		0x00BE
#define SYSCALL_ZwEnumerateKey_WIN8_1			0x012E

////�������� ��������� ������� ������� � ������� ��������
//#define THREAD_LIST_PROCESS_OFFSET_WIN7      0x188
//
//// �������� �������� ������� ������� � ������� ������
//#define THREAD_LIST_THREAD_OFFSET_WIN7       0x268
//
//// �������� ���������� ������ ������ � ������� ������
//#define START_ADDRESS_THREAD_OFFSET_WIN7     0x218
//
//#define WIN32_START_ADDESS_THREAD_OFFSET_WIN7    0x260

// �������� �������� ����������� ������ ���� ��������� � ������� ��������
#define ACTIVE_LIST_PROCESS_OFFSET_WIN8		0x0b8

// �������� �� _HANDLE_TABLE � ������� ��������
#define HANDLE_TABLE_OFFSET_WIN8			0x150

// �������� �� PID � ������� ������� �������
//#define HANDLE_TABLE_PID_OFFSET_WIN7	0x08

// �������� �� ������ ������� �������� � ������� ����. �������
//#define HANDLE_TABLE_PROC_OFFSET_WIN7		0x04

// �������� �� ������ �������� ����. ������� � ������� ����. �������
#define HANDLE_TABLE_LIST_OFFSET_WIN8		0x010

// �������� �� ����� � ������� ��������
//#define IMAGE_NAME_OFFSET_WIN8				0x16c


// --------------------------- FOR WIN10_1903

#define SYSCALL_ZwQuerySystemInformation_WIN10_1903	0x009D
#define SYSCALL_ZwDeviceIoControlFile_WIN10_1903	0x0145	
#define SYSCALL_ZwQueryDirectoryFile_WIN10_1903		0x00C5
#define SYSCALL_ZwEnumerateKey_WIN10_1903			0x013C

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

// ���������� ��������� �� ��������� ������� �������
#define GET_HEAD_THREAD_LIST(process) (LIST_ENTRY*)((ULONG) process + glThreadListProcessOffset)

// ���������� ��������� �� ������� ������ ��������� ������� ��������
#define GET_ENTRY_PROCESS_LIST(process) (LIST_ENTRY*)((ULONG) process + glActiveListProcessOffset)

// ���������� ��������� �� �����, �� ���������������� �������� ������
#define GET_THREAD_BY_LIST_ENTRY(entry) ((ULONG) entry - glThreadListThreadOffset)

// ���������� ��������� �� �������, �� ���������������� �������� ������
#define GET_PROCESS_BY_LIST_ENTRY(entry) ((ULONG) entry - glActiveListProcessOffset)

// ���������� ��������� ����� ������
#define GET_START_ADDRESS_THREAD(thread) *( (PULONG)((ULONG) thread + glStartAddressThreadOffsett) )

#define GET_WIN32_START_ADDRESS_THREAD(thread) *( (PULONG)((ULONG) thread + glWin32StartAddressThreadOffset) )

// ���������� addr HANDLE_TABLE ������� ��������
#define GET_HANDLE_TABLE(process)	(ULONG*)((ULONG)process + glHandleTableOffset)

#define GET_HANDLE_TABLE_LIST_ENTRY(handleTable)	(PLIST_ENTRY)((ULONG)handleTable + glHandleTableListOffset)


//-----------------------------------------------

// ---------------------------
#define WINXP_BUILD_NUMBER	2600
#define WIN7_BUILD_NUMBER	7601
#define WIN8_BUILD_NUMBER	9200

#define WINXP
#define WIN7
#define WIN8_1
#define WIN10_1903


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
	


//-----------------------------------------------

#else
// for x64
#endif // M_X86
	
//-----------------------------------------------

#endif