/**
 * @file semaphore.h
 * @brief �Z�}�t�H
 */

#include "semaphore.h"

extern void scheduler();

SEMAPHORE g_semaphore[MAX_SEMAPHORE];

//volatile unsigned short gg_semid;
unsigned short wup_tsk_id;
unsigned short wup_tsk_id_mask;
unsigned short semid;

/**
 * void ini_sem(void);
 * @brief �Z�}�t�H������������
 */
void ini_sem(void)
{
	unsigned short i;
	for (i = 0; i < MAX_SEMAPHORE; ++i) {
		g_semaphore[i].owner_tsk = 0;
		g_semaphore[i].wait_tsk = 0;
	}
}

/**
 * void wai_sem(unsigned short semid);
 * @brief �Z�}�t�H���l������
 *
 * @param[in] semid �Z�}�t�H�ԍ�
 */
void wai_sem(unsigned short semid)
{
//	gg_semid = semid;
	
//	_asm("\tpush.w $@", semid);
	_asm("\tint #35");
	_asm("\tnop");
}

/**
 * void sig_sem(unsigned short semid);
 * @brief �Z�}�t�H���J������
 *
 * @param[in] semid �Z�}�t�H�ԍ�
 */
void sig_sem(unsigned short semid)
{
//	_asm("\tpush.w $@", semid);
	_asm("\tint #36");
	_asm("\tnop");
}

/**
 * void pol_sem(unsigned short semid);
 * @brief �Z�}�t�H���l������
 *
 * @param[in] semid �Z�}�t�H�ԍ�
 */
void pol_sem(unsigned short semid)
{
//	_asm("	push.w $@", semid);
	_asm("	int #37");
}

/**
 * void svc_wai_sem(void);
 * @brief svc_wai_sem
 */
void svc_wai_sem(void)
{
//	_asm("	pop.w $@", semid);
	_asm("\tmov.w R1, _semid");

	if(!g_semaphore[semid].owner_tsk) {
		g_semaphore[semid].owner_tsk = (0x01 << g_taskid);
		g_semaphore[semid].wait_tsk = 0; // for safety
		g_icb[g_taskid].context.pc_flg[1] &= 0x0fff; // IPL = 0
		g_icb[g_taskid].context.pc_flg[1] |= 0x0040; // Interrupt enable
	}
	else {
		g_semaphore[semid].wait_tsk = (1 << g_taskid);
		g_icb[g_taskid].state_flag &= ~READY_FLG;
		g_icb[g_taskid].context.pc_flg[1] &= 0x0fff; // IPL = 0
		g_icb[g_taskid].context.pc_flg[1] |= 0x0040; // Interrupt enable
	}

	_asm("\tjmp _scheduler");
//	scheduler();
}

/**
 * void svc_sig_sem(void);
 * @brief svc_sig_sem
 */
void svc_sig_sem(void)
{	
//	_asm("	pop.w $@", semid);
	_asm("\tmov.w R1, _semid");
	
	if(!g_semaphore[semid].wait_tsk) {
		g_semaphore[semid].owner_tsk = 0;
		g_icb[g_taskid].context.pc_flg[1] &= 0x0fff; // IPL = 0
		g_icb[g_taskid].context.pc_flg[1] |= 0x0040; // Interrupt enable�C�܂�S�Ẵ��x�����荞�݂�����
	}
	else {
		g_semaphore[semid].owner_tsk = g_semaphore[semid].wait_tsk;
		wup_tsk_id = 0;
		wup_tsk_id_mask = 0x01;
		for(;;) {	 // ready task �����݂��邱�Ƃ��O��C�T���v���ł͍Œ�D��x�^�X�N���������[�v�ƂȂ��Ă���
			if(g_semaphore[semid].wait_tsk & wup_tsk_id_mask) break;
			wup_tsk_id_mask <<= 1;
			wup_tsk_id++;
		}
		g_semaphore[semid].wait_tsk = 0;
		g_icb[wup_tsk_id].state_flag |= READY_FLG;
		
		g_icb[g_taskid].context.pc_flg[1] &= 0x0fff; // IPL = 0
		g_icb[g_taskid].context.pc_flg[1] |= 0x0040; // Interrupt enable�C�܂�S�Ẵ��x�����荞�݂�����	
	}
	_asm("\tjmp _scheduler");
//	scheduler();	
}

/**
 * void svc_pol_sem(void);
 * @brief svc_pol_sem
 */
void svc_pol_sem(void)
{
	static unsigned short semid;
//	_asm("	pop.w $@", semid);
	_asm("\tmov.w R1, _semid");

	_asm("\tjmp _scheduler");
//	scheduler();
}

