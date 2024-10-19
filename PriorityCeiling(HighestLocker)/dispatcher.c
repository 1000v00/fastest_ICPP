/**
 * @file dispatcher.c
 * @brief �f�B�X�p�b�`��
 */

#include "dispatcher.h"

/**
 * void scheduler(void);
 * @brief ���荞�݃X�P�W���[��
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
 * @brief �f�B�X�p�b�`��
 */
void dispatcher(void)
{
	unsigned short i;
	unsigned short dispatch_task_index;

	dispatch_task_index = MAX_ICB-1; //�Œ�D��x�^�X�N��main�����蓖�ĂĂ��邽��
	for(i=0; i<MAX_ICB; ++i)
	{
		if(g_icb[i].state_flag & READY_FLG)
		{
			if(g_priority[i] <= g_priority[dispatch_task_index]) dispatch_task_index = i;
		}
	}

	if (dispatch_task_index >= MAX_ICB) { // No ready ISR
		_asm("\tnop"); // ERROR! I lowest task must FOREVER 
	}
	else {
		g_taskid = dispatch_task_index;
		load_context(g_taskid);
		_asm("reit");
		_asm("\tnop");
	}
}
