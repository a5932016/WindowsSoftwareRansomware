#include <windows.h>

BOOL GetFilePointEx(
	HANDLE hFile,
	PLARGE_INTEGER lpNewFilePointer)
{
	LARGE_INTEGER liDistanceToMove = { 0 };
	return SetFilePointerEx(
		hFile,
		liDistanceToMove,
		lpNewFilePointer,
		FILE_CURRENT);
}