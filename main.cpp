#include "stdio.h"

int main(int argc, char* argv[])
{
	char c = 0;

#ifndef WIN32
	system("rfkill unblock bluetooth\n"
		"bluetoothctl\n"
		"agent KeyboardDisplay\n"
		"default-agent\n"
		"connect CC:C5:0A:20:29:E5\n"
        "quit\n");
	system("/bin/stty raw");
#endif

	while (1)
	{
		printf("%c", getchar());
	}
	return 0;
}

