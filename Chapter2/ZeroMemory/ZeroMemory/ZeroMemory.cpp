﻿#include <windows.h>
#include <stdio.h>

int main()
{
	char aString[] = "Hello, World!";
	printf("[%s]\n", aString);
	ZeroMemory(&aString, strlen(aString));
	printf("[%s]\n", aString);

	return 0;
}