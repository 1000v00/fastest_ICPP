/**
 * @file dispatcher.c
 * @brief ディスパッチャー
 */

#include "dispatcher.h"

/**
 * void scheduler(void);
 * @brief 割り込みスケジューラー
 */
void scheduler(void)
{
#if 0
	if (g_icb[g_taskid].isr_cnt < 1 || g_icb[g_taskid].isr_cnt > MAX_ISRCNT) {
		/* error */
	}
#endif	
	dispatcher();
}

/**
 * void dispatcher(void);
 * @brief ディスパッチャー
 */
void dispatcher(void)
{
	unsigned short i;

	for (i = 0; i < MAX_ICB; ++i) {
		if (g_icb[i].state_flag & READY_FLG) break;
	}

	if (i >= MAX_ICB) { // No ready ISR
		_asm("\tnop"); // ERROR！ lowest task must FOREVER 
	}
	else {
		g_taskid = i;
		load_context(g_taskid);
		_asm("reit");
		_asm("\tnop");
	}
}
