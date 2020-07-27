#include <stdio.h>
#include <windows.h>

#define WIDTH 72

int main()
{
	char bars[] = "|/-\\";

	while (1)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			printf("%c\b", bars[i % 4]);
			Sleep(50);
			printf(" ");
		}

		for (int i = WIDTH; i > 0; i--)
		{
			printf("%c\b", bars[i % 4]);
			Sleep(50);
			printf(" \b\b");
		}
	}

	return 0;
}