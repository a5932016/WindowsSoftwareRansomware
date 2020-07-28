#include <windows.h>
#include <tchar.h>

int main()
{
	if (!CopyFile(
		_T("C:\\TEMP\\SourceFile.txt"),
		_T("C:\\TEMP\\TargetFile.txt"),
		false))
	{
		_tprintf(_T("CopyFile() Error: %d\n"), GetLastError());
	}

	system("pause");
	return 0;
}