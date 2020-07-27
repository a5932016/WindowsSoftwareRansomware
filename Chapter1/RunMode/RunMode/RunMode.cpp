#include <stdio.h>

int main()
{
#ifdef  _DEBUG
	printf("Debug Mode\n");
#else //  _DEBUG
	printf("Release Mode\n");
#endif
}