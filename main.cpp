#include "keys_table.h"
#include "stdio.h"

#include "input-event-codes.h"

#define EVENTS_NUM	100

int main(int argc, char* argv[])
{
	int cnt = 0;
	char cp = 0;
	char* fn = NULL;

	printf("Type and press enter\n");

	while (1)
	{
		cp = getchar();
		putchar(cp);
	}

	if (argc > 1 && argv[1] != NULL)
	{
		fn = argv[1];
	}
	else
	{
		printf("No filename found\n");
		getchar();
		return 0;
	}

	printf("Init Kbd\n");

	if (0 == KBD_Init(fn))
	{
		printf("Ok\n");
	}
	else
	{
		printf("Init failed\n");
		getchar();
		return 0;
	}

	printf("ASCII decoding\n");

	cnt = 0;
	while (1)
	{
		cp = getchar();
			putchar(cp);
	}
	printf("\n");
	printf("Finished. Press Enter key to exit.\n");
	getchar();
	return 0;
}

