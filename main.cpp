#include "stdio.h"
#include "kbd.h"

int main(int argc, char* argv[])
{
	char c = 0;
	char* path = NULL;
	char pathBuf[128] = { 0 };
	int cnt = 0;

	do
	{
		if (argc > 0 && argv[1] != NULL)
		{
			path = argv[1];
			printf("path = %s\n", path);
		}
		else
		{
			printf("Enter kbd event file path\n");
			path = gets(pathBuf);
		}

		if (0 == KBD_Init(path))
		{
			printf("File \"%s\" opened\n", path);
			break;
		}
		else
		{
			printf("Could not open file \"%s\", enter other path\n", path);
			argv[1] = NULL;
		}
	} while (1);
	/*******************/
	while (1)
	{
		c = KBD_GetDecodedChar();
		if (c == EOF)
		{
			printf("End of file\n");
			getchar();
			return 0;
		}
		else if (c != 0)
		{
			printf("Shift is %d, Ctrl is %d\n", KBD_GetShiftState(), KBD_GetCtrlState());
			printf("%c\n", c);
			cnt = 0;
		}
	}
	/*******************/
	return 0;
}

