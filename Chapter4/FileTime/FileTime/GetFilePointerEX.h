#pragma once
#include <windows.h>

BOOL GetFilePointEx(
	HANDLE hFile,
	PLARGE_INTEGER lpNewFilePointer);