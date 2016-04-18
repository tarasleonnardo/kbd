#include "stdio.h"
#include "keys_table.h"

int main(int argc, char* argv[])
{
	char c = 0;

	while (1)
	{
		printf("%c", KBD_getDecodedChar());
	}
	return 0;
}

