#include <stdio.h>
#include <Windows.h>

int main(int argc, char* argv[])
{
    char bars[] = "|/-\\";
    int i = 0;
    while (1)
    {
        printf("%c\b", bars[i]);
        i = (i + 1) % 4;
        Sleep(100);
    }

    return 0;
}