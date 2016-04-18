#ifndef _BT_KBD_H_
#define _BT_KBD_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define BT_KBD_IN_BUF_SIZE	16 // Must be power of 2
#define BT_KBD_BUF_MASK		(BT_KBD_IN_BUF_SIZE - 1)

	int16_t KBD_Init(char* path);
	void KBD_Close();
	char KBD_GetDecodedChar();
	int8_t KBD_GetShiftState(void);
	int8_t KBD_GetCtrlState(void);

#ifdef __cplusplus
}
#endif
#endif // _BT_KBD_H_
