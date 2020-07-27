#include <windows.h>
#include <stdio.h>
#include <string.h>

int main()
{
	// 1
	/*char aString1[] = "Hello World!";
	char aString2[100];
	printf("aString1: [%s]\n", aString1);
	CopyMemory(aString2, aString1, strlen(aString1) + 1);
	printf("aString2: [%s]\n", aString2);*/

	// 2
	char s[1024] = "This is a test.";
	printf("%s\n", s);
	CopyMemory(s + 5, s, strlen(s));
	printf("%s\n", s);

	return 0;
}