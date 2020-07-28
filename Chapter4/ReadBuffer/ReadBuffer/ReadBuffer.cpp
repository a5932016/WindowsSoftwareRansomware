#include <windows.h>
#include <tchar.h>
#include "common.h"

#define HEXDUMP_BUFSIZE 1024

ULONG hexdump(PUCHAR data, ULONG size)
{
	ULONG nResult = 0;
	for (ULONG i = 0; i < size; i += 16) {
		nResult += DEBUG("%08X |", i);
		for (ULONG j = 0; j < 16; j++) {
			if (i + j < size) {
				nResult += DEBUG(" %02X", data[i + j]);
			}
			else {
				nResult += DEBUG("   ");
			}
			if ((j + 1) % 8 == 0) {
				nResult += DEBUG(" ");
			}
		}
		nResult += DEBUG("|");
		for (ULONG j = 0; j < 16; j++) {
			if (i + j < size) {
				UCHAR k = data[i + j];
				UCHAR c = k < 32 || k > 127 ? '.' : k;
				nResult += DEBUG("%c", c);
			}
			else {
				nResult += DEBUG(" ");
			}
		}
		nResult += DEBUG("\n");
	}
	return nResult;
}

BOOL ReadFile_DEBUG(
	HANDLE       hFile,
	LPVOID       lpBuffer,
	DWORD        nNumberOfBytesToRead,
	LPDWORD      lpNumberOfBytesRead,
	LPOVERLAPPED lpOverlapped
)
{
	BOOL retval = ReadFile(
		hFile,
		lpBuffer,
		nNumberOfBytesToRead,
		lpNumberOfBytesRead,
		lpOverlapped
	);
	DEBUG("Read %d\n", nNumberOfBytesToRead);
	hexdump((PUCHAR)lpBuffer, nNumberOfBytesToRead);
	return retval;
}

BOOL WriteFile_DEBUG(
	HANDLE       hFile,
	LPCVOID      lpBuffer,
	DWORD        nNumberOfBytesToWrite,
	LPDWORD      lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped
)
{
	DEBUG("Write %d\n", nNumberOfBytesToWrite);
	hexdump((PUCHAR)lpBuffer, nNumberOfBytesToWrite);
	return WriteFile(
		hFile,
		lpBuffer,
		nNumberOfBytesToWrite,
		lpNumberOfBytesWritten,
		lpOverlapped
	);
}

BOOL ReadBuffer(
	LPCTSTR lpFileName,
	LARGE_INTEGER liDistanceToMove,
	DWORD dwMoveMethod,
	PUCHAR pbBuffer,
	ULONG cbBuffer,
	PULONG pcbResult)
{
	HANDLE hFile;
	LARGE_INTEGER liNewFilePointer;
	BOOL bResult = FALSE;

	hFile = CreateFile(
		lpFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DEBUG("open %s fails: %d\n",
			lpFileName,
			GetLastError());
		return FALSE;
	}

	if (!SetFilePointerEx(
		hFile,
		liDistanceToMove,
		&liNewFilePointer,
		dwMoveMethod))
	{
		DEBUG("set pointer %s fails: %d\n",
			lpFileName, 
			GetLastError());
		goto Error_Exit;
	}

	bResult = ReadFile_DEBUG(
		hFile,
		pbBuffer,
		cbBuffer,
		pcbResult,
		0);
	if (!bResult)
	{
		DEBUG("Read %s error: %d\n",
			lpFileName, GetLastError());
	}

	bResult = TRUE;
Error_Exit:
	CloseHandle(hFile);
	return bResult;
}

BOOL WriteBuffer(
	LPCTSTR lpFileName,
	LARGE_INTEGER liDistanceToMove,
	DWORD dwMoveMethod,
	PUCHAR pbBuffer,
	ULONG cbBuffer,
	PULONG pcbResult)
{
	HANDLE hFile;
	LARGE_INTEGER liNewFilePointer;
	BOOL bResult = FALSE;

	if ((hFile = CreateFile(
		lpFileName,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	)) == INVALID_HANDLE_VALUE) {
		DEBUG("Open file %s error\n",
			lpFileName);
		return FALSE;
	}

	if (!SetFilePointerEx(
		hFile,
		liDistanceToMove,
		&liNewFilePointer,
		dwMoveMethod)) {
		DEBUG("set pointer %s fails: %d\n",
			lpFileName, GetLastError());
		goto Error_Exit;
	}

	if (!(bResult = WriteFile_DEBUG(
		hFile,
		pbBuffer,
		cbBuffer,
		pcbResult,
		0
	))) {
		DEBUG("Write %s error\n",
			lpFileName);
	}
	bResult = TRUE;
Error_Exit:
	CloseHandle(hFile);
	return bResult;
}

INT _tmain(INT argc, LPCTSTR argv[])
{
	if (argc > 2) {
		if (!_tcsicmp(argv[1], _T("hexdump"))) {
			UCHAR abBuffer[HEXDUMP_BUFSIZE];
			ULONG cbBuffer;
			ReadBuffer(argv[2], { 0 }, 0, abBuffer, sizeof(abBuffer), &cbBuffer);
			cbBuffer = hexdump(abBuffer, cbBuffer);
			WriteBuffer(_T("C:\\TEMP\\test2.txt"), { 0 }, 0, abBuffer, sizeof(abBuffer), &cbBuffer);
			return TRUE;
		}
	}
	else {
		DEBUG("Usage: %s hexdump FILENAME\n", argv[0]);
	}

	system("pause");
	return 0;
}