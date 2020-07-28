#include <windows.h>
#include <tchar.h>

BOOL UpdateFileAttributes(
	LPCTSTR lpFileName,
	DWORD dwFileAttributes,
	BOOL bFlag)
{
	BOOL bResult = TRUE;
	DWORD dwAttrs = GetFileAttributes(lpFileName);

	if (dwAttrs == INVALID_FILE_ATTRIBUTES)
		return false;

	if (bFlag)
	{
		if (!(dwAttrs & dwFileAttributes))
		{
			bResult = SetFileAttributes(lpFileName, dwAttrs | dwFileAttributes);
		}
	}
	else
	{
		if (dwAttrs & dwFileAttributes)
		{
			DWORD dwNewAttrs = dwAttrs & ~dwFileAttributes;
			bResult = SetFileAttributes(lpFileName, dwNewAttrs);
		}
	}

	return bResult;
}

int main()
{
	LPCTSTR lpFileName;
	DWORD dwFileAttributes;

	lpFileName = _T("C:\\TEMP\\test.txt");
	dwFileAttributes = FILE_ATTRIBUTE_READONLY;
	if (!UpdateFileAttributes(lpFileName, dwFileAttributes, FALSE))
	{
		_tprintf(TEXT("SetFileAttributes() Error: %d\n"), GetLastError());
	}

	system("pause");
	return 0;
}