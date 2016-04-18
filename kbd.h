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
	/**
	  * @brief   Get ascii code, corresponding to the pressed key, or 0 if there is no such code.
	  * @return  char - ascii code of pressed key or 0 if key has no ascii code
	  * @note    Function wait until key pressed.
	  */
	char KBD_GetDecodedChar();
	/**
	  * @brief   Get state of shift key
	  * @return  1 - shift is active (hold) or 0 - shitf if not active
	  */
	int8_t KBD_GetShiftState(void);
	/**
	  * @brief   Get state of ctrl key
	  * @return  1 - ctrl is active (hold) or 0 - ctrl if not active
	  */
	int8_t KBD_GetCtrlState(void);

#ifdef __cplusplus
}
#endif
#endif // _BT_KBD_H_
