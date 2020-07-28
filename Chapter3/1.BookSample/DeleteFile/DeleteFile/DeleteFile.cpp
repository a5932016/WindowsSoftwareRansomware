#include <windows.h>
#include <tchar.h>

int main()
{
	if (!DeleteFile(_T("C:\\TEMP\\file2.txt")))
	{
		_tprintf(_T("DeleteFile() Error: %d\n"), GetLastError());
		return false;
	}

	system("pause");
	return 0;
}
