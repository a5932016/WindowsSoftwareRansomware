#include <windows.h>
#include <tchar.h>
#include "GetFilePointerEX.h"

BOOL touch(LPCTSTR lpSource, LPCTSTR lpTarget)
{
	HANDLE hFile;
	FILETIME CreationTime, AccessTime, WriteTime;

	// GetFileTime
	// Open source file with mode 0
	hFile = CreateFile(
		lpSource,
		0,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("open file1.txt fails\n"));
		return false;
	}

	// Get file times
	GetFileTime(
		hFile,
		&CreationTime,
		&AccessTime,
		&WriteTime);

	// Close
	CloseHandle(hFile);

	// SetFileTime
	// Open target file with GENERIC_WRITE mode
	hFile = CreateFile(
		lpTarget,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		_tprintf(_T("open file2.txt fails\n"));
		return false;
	}

	// Set File Time
	SetFileTime(
		hFile,
		&CreationTime,
		&AccessTime,
		&WriteTime);

	// Close
	CloseHandle(hFile);

	return true;
}

int main()
{
	touch(
		_T("C:\\TEMP\\file1.txt"),
		_T("C:\\TEMP\\file2.txt"));

	system("pause");
	return 0;
}