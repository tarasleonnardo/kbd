#include "stdio.h"

int main(int argc, char* argv[])
{
	char c = 0;

	if (argc > 1 && argv[1] != NULL)
	{
		printf("Input redirection from: %s\n", argv[1]);
	}

	while (1)
	{
		if (EOF != (c = getchar()))
			putchar(c);
		else
			printf("EOF\n");
	}
	return 0;
}

