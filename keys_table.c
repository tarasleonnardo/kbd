#include "stdint.h"
#include "stdio.h"
#include "keys_table.h"
#include "input-event-codes.h"

#ifndef WIN32
#include "linux/input.h"
#else
#include "input_ev_str.h"
#endif

/* Data */
static int16_t head = 0;
static int16_t tail = 0;
static char inBuf[BT_KBD_IN_BUF_SIZE] = { 0 };
static const char *keys[KEY_MAX + 1];
static FILE* fp = NULL;
static struct input_event inEvent;

/* Prototypes */
static void KBD_char2Buf(char c);

/* Public functions */
/**
  * @return int16_t - 0 if initialization was successful, -1 - if not.
  */
int16_t KBD_Init(char* path)
{
	if (path != NULL)
	{
		fp = fopen(path, "r");

		if (fp != NULL) return 0;
	}

	return -1;
}

void KBD_Close(void)
{
	fclose(fp);
}

char KBD_getc(void)
{
	char c = EOF;
	if (tail != head)
	{
		c = inBuf[tail];
		tail = (tail + 1) & BT_KBD_BUF_MASK;
	}
	else
	{
		return EOF;
	}
	return c;
}

int KBD_gets(char* str, int maxSize)
{
	int cnt = 0;

	while (cnt < maxSize)
	{
		if ((EOF != (str[cnt] = KBD_getc())) ||
			(str[cnt] == '\n') ||
			(str[cnt] == '\0'))
		{
			str[cnt] = '\0';
			return;
		}
	}

	str[maxSize - 1] = '\0';
}

static void KBD_char2Buf(char c)
{
	inBuf[head] = c;
	head = (head + 1) & BT_KBD_BUF_MASK;
	if (head == tail)
	{
		tail = (tail + 1) & BT_KBD_BUF_MASK;
	}
}

static void KBD_str2Buf(char* str)
{
	while (*str != '\0')
	{
		char2Buf(*str++);
	}
}



char KBD_getDecodedChar()
{
	if (fp == NULL) return EOF;

	if (1 != fread(&inEvent, sizeof(inEvent), 1, fp))
		return NULL;
	
	if ((inEvent.type == EV_KEY) &&
		((inEvent.value == 0x01) || (inEvent.value == 0x02)))
	{
		if ((inEvent.code <= KEY_MAX) &&
			(keys[inEvent.code] != NULL))
			return keys[inEvent.code][0];

		return EOF;
	}
}

static const char *keys[KEY_MAX + 1] = {
	[KEY_RESERVED] = NULL, [KEY_ESC] = "\e",
	[KEY_1] = "1", [KEY_2] = "2",
	[KEY_3] = "3", [KEY_4] = "4",
	[KEY_5] = "5", [KEY_6] = "6",
	[KEY_7] = "7", [KEY_8] = "8",
	[KEY_9] = "9", [KEY_0] = "0",
	[KEY_MINUS] = "-", [KEY_EQUAL] = "=",
	[KEY_BACKSPACE] = "\b", [KEY_TAB] = "\t",
	[KEY_Q] = "Q", [KEY_W] = "W",
	[KEY_E] = "E", [KEY_R] = "R",
	[KEY_T] = "T", [KEY_Y] = "Y",
	[KEY_U] = "U", [KEY_I] = "I",
	[KEY_O] = "O", [KEY_P] = "P",
	[KEY_LEFTBRACE] = "(", [KEY_RIGHTBRACE] = ")",
	[KEY_ENTER] = "\r\n", [KEY_LEFTCTRL] = NULL,
	[KEY_A] = "A", [KEY_S] = "S",
	[KEY_D] = "D", [KEY_F] = "F",
	[KEY_G] = "G", [KEY_H] = "H",
	[KEY_J] = "J", [KEY_K] = "K",
	[KEY_L] = "L", [KEY_SEMICOLON] = ";",
	[KEY_APOSTROPHE] = "'", [KEY_GRAVE] = "`",
	[KEY_LEFTSHIFT] = NULL, [KEY_BACKSLASH] = "\\",
	[KEY_Z] = "Z", [KEY_X] = "X",
	[KEY_C] = "C", [KEY_V] = "V",
	[KEY_B] = "B", [KEY_N] = "N",
	[KEY_M] = "M", [KEY_COMMA] = ",",
	[KEY_DOT] = ".", [KEY_SLASH] = "/",
	[KEY_RIGHTSHIFT] = NULL, [KEY_KPASTERISK] = "*",
	[KEY_LEFTALT] = NULL, [KEY_SPACE] = " ",
	[KEY_CAPSLOCK] = NULL, [KEY_F1] = NULL,
	[KEY_F2] = NULL, [KEY_F3] = NULL,
	[KEY_F4] = NULL, [KEY_F5] = NULL,
	[KEY_F6] = NULL, [KEY_F7] = NULL,
	[KEY_F8] = NULL, [KEY_F9] = NULL,
	[KEY_F10] = NULL, [KEY_NUMLOCK] = NULL,
	[KEY_SCROLLLOCK] = NULL, [KEY_KP7] = "7",
	[KEY_KP8] = "8", [KEY_KP9] = "9",
	[KEY_KPMINUS] = "-", [KEY_KP4] = "4",
	[KEY_KP5] = "5", [KEY_KP6] = "6",
	[KEY_KPPLUS] = "+", [KEY_KP1] = "1",
	[KEY_KP2] = "", [KEY_KP3] = "3",
	[KEY_KP0] = "0", [KEY_KPDOT] = ".",
	[KEY_ZENKAKUHANKAKU] = NULL, [KEY_102ND] = NULL,
	[KEY_F11] = NULL, [KEY_F12] = NULL,
	[KEY_RO] = NULL, [KEY_KATAKANA] = NULL,
	[KEY_HIRAGANA] = NULL, [KEY_HENKAN] = NULL,
	[KEY_KATAKANAHIRAGANA] = NULL, [KEY_MUHENKAN] = NULL,
	[KEY_KPJPCOMMA] = ",", [KEY_KPENTER] = "\r\n",
	[KEY_RIGHTCTRL] = NULL, [KEY_KPSLASH] = "/",
	[KEY_SYSRQ] = NULL, [KEY_RIGHTALT] = NULL,
	[KEY_LINEFEED] = "\n", [KEY_HOME] = "\r",
	[KEY_UP] = NULL, [KEY_PAGEUP] = NULL,
	[KEY_LEFT] = NULL, [KEY_RIGHT] = NULL,
	[KEY_END] = NULL, [KEY_DOWN] = NULL,
	[KEY_PAGEDOWN] = NULL, [KEY_INSERT] = NULL,
	[KEY_DELETE] = NULL, [KEY_MACRO] = NULL,
	[KEY_MUTE] = NULL, [KEY_VOLUMEDOWN] = NULL,
	[KEY_VOLUMEUP] = NULL, [KEY_POWER] = NULL,
	[KEY_KPEQUAL] = "=", [KEY_KPPLUSMINUS] = NULL,
	[KEY_PAUSE] = NULL, [KEY_KPCOMMA] = ",",
	[KEY_HANGUEL] = NULL, [KEY_HANJA] = NULL,
	[KEY_YEN] = NULL, [KEY_LEFTMETA] = NULL,
	[KEY_RIGHTMETA] = NULL, [KEY_COMPOSE] = NULL,
	[KEY_STOP] = NULL, [KEY_AGAIN] = NULL,
	[KEY_PROPS] = NULL, [KEY_UNDO] = NULL,
	[KEY_FRONT] = NULL, [KEY_COPY] = NULL,
	[KEY_OPEN] = NULL, [KEY_PASTE] = NULL,
	[KEY_FIND] = NULL, [KEY_CUT] = NULL,
	[KEY_HELP] = NULL, [KEY_MENU] = NULL,
	[KEY_CALC] = NULL, [KEY_SETUP] = NULL,
	[KEY_SLEEP] = NULL, [KEY_WAKEUP] = NULL,
	[KEY_FILE] = NULL, [KEY_SENDFILE] = NULL,
	[KEY_DELETEFILE] = NULL, [KEY_XFER] = NULL,
	[KEY_PROG1] = NULL, [KEY_PROG2] = NULL,
	[KEY_WWW] = NULL, [KEY_MSDOS] = NULL,
	[KEY_COFFEE] = NULL, [KEY_DIRECTION] = NULL,
	[KEY_CYCLEWINDOWS] = NULL, [KEY_MAIL] = NULL,
	[KEY_BOOKMARKS] = NULL, [KEY_COMPUTER] = NULL,
	[KEY_BACK] = NULL, [KEY_FORWARD] = NULL,
	[KEY_CLOSECD] = NULL, [KEY_EJECTCD] = NULL,
	[KEY_EJECTCLOSECD] = NULL, [KEY_NEXTSONG] = NULL,
	[KEY_F13] = NULL,
	[KEY_F14] = NULL, [KEY_F15] = NULL,
	[KEY_F16] = NULL, [KEY_F17] = NULL,
	[KEY_F18] = NULL, [KEY_F19] = NULL,
	[KEY_F20] = NULL, [KEY_F21] = NULL,
	[KEY_F22] = NULL, [KEY_F23] = NULL,
	[KEY_F24] = NULL, [KEY_CANCEL] = NULL,
	[BTN_0] = "0", [BTN_1] = "1",
	[BTN_2] = "2", [BTN_3] = "3",
	[BTN_4] = "4", [BTN_5] = "5",
	[BTN_6] = "6", [BTN_7] = "7",
	[BTN_8] = "8", [BTN_9] = "9",
	[BTN_LEFT] = NULL, [BTN_RIGHT] = NULL,
	[BTN_MIDDLE] = NULL, [BTN_SIDE] = NULL,
	[BTN_EXTRA] = NULL, [BTN_FORWARD] = NULL,
	[BTN_BACK] = NULL, [BTN_TASK] = NULL,
	[BTN_TRIGGER] = NULL, [BTN_THUMB] = NULL,
};