#include "stdio.h"
#include "keys_table.h"

int main(int argc, char* argv[])
{
	char c = 0;
	char* path = NULL;
	char pathBuf[128] = { 0 };

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

	while (1)
	{
		c = KBD_getDecodedChar();
		if (c != 0)
		{
			printf("%c", c);
		}
		else
		{
			printf("unknown\n");
		}
	}
	return 0;
}

