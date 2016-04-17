#ifndef _KEYS_TABLE_H_
#define _KEYS_TABLE_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define BT_KBD_IN_BUF_SIZE	16 // Must be power of 2
#define BT_KBD_BUF_MASK		(BT_KBD_IN_BUF_SIZE - 1)

	char KBD_getc(void);
	int KBD_gets(char* str, int maxSize);
	int16_t KBD_Init(char* path);
	void KBD_Close();
	char KBD_getDecodedChar();

#ifdef __cplusplus
}
#endif
#endif _KEYS_TABLE_H_
