#include <windows.h>
#include <tchar.h>

int main()
{
	if (!MoveFile(
		_T("C:\\TEMP\\OldFile.txt"),
		_T("C:\\TEMP\\NewFile.txt")))
	{
		_tprintf(_T("MoveFile() Error: %d\n"), GetLastError());
		return false;
	}

	system("pause");
	return 0;
}