#include <stdio.h>
#include <windows.h>

int main()
{
	char aString[] = "Hello World!";
	char* pString;
	int slen = strlen(aString);

	printf("aString: [%s]\n", aString);
	pString = (char*)HeapAlloc(GetProcessHeap(), 0, slen + 1);

	if (pString == NULL)
	{
		printf("HeapAlloc() error\n");
		return 1;
	}

	strcpy_s(pString, slen + 1, aString);
	printf("pString: [%s]\n", pString);
	HeapFree(GetProcessHeap(), 0, pString);

	return 0;
}