#include <stdio.h>
#include <windows.h>

int main()
{
	DWORD drives = GetLogicalDrives();
	CHAR root[4] = "A:";

	for (int i = 0; i < 26; i++)
	{
		if (drives & (1 << i))
		{
			root[0] = i + 'A';
			printf("Driver %c: found, type %d\n", i + 'A',GetDriveTypeA(root));
		}
	}

	return 0;
}