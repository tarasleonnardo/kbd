#include "keys_table.h"
#include "stdio.h"

#ifdef WIN32
#include "input-event-codes.h"
#include "input_ev_str.h"
#else
#include "input-event-codes.h"
#endif

#define EVENTS_NUM	100
#ifdef WIN32
char filename[] = "eventtest";

void writeFile(char* path)
{
	FILE* fp = fopen(path, "w");
	int cnt = 0;
	input_event ie;

	if (fp == NULL) return;

	while (cnt < EVENTS_NUM)
	{
		ie.type = 1;
		ie.value = ((cnt % 5) == 0) ? 1 : 2;
		ie.code = cnt;

		fwrite(&ie, sizeof(ie), 1, fp);
		cnt++;
	}
	fclose(fp);
	printf("File created\n");
}
#endif

int main(int argc, char* argv[])
{
	int cnt = 0;
	char cp = 0;
	char* fn = NULL;

	if (argc > 1 && argv[1] != NULL)
	{
		fn = argv[1];
	}
	else
	{
#ifdef WIN32
		fn = filename;
		printf("Creating sample file\n");
		writeFile(fn);
#else
		printf("No filename found\n");
		getchar();
		return 0;
#endif
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
	while (cnt < EVENTS_NUM)
	{
		if(NULL != (cp = KBD_getDecodedChar()))
			putchar(cp);
		cnt++;
	}
	printf("\n");
	printf("Finished. Press Enter key to exit.\n");
	getchar();
	return 0;
}

