#include "stdio.h"
#include "keys_table.h"

int main(int argc, char* argv[])
{
	char c = 0;

#ifndef WIN32
	system("Try to type something\n");
#endif

	while (1)
	{
		printf("%c", KBD_getDecodedChar());
	}
	return 0;
}

