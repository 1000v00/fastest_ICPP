/**
 * @file task.c
 * @brief タスク管理
 */

#include "task.h"

volatile unsigned short g_taskid;
//volatile unsigned short gg_task;
extern void scheduler();

/**
 * void ini_tsk(void);
 * @brief タスクを初期化する
 */
void ini_tsk(void)
{
	unsigned short i;
	for (i = 0; i < MAX_ICB; ++i) ini_icb(i);

	g_taskid = MAX_ICB - 1;
	g_icb[g_taskid].state_flag = ENABLE_FLG | READY_FLG;
	g_icb[g_taskid].isr_cnt = 1;
}

/**
 * void cre_tsk(unsigned short taskid, unsigned long isr_entry);
 * @brief タスクを生成する
 *
 * @param[in] taskid 初期化するタスク番号
 * @param[in] isr_entry タスクのエントリポイント
 */
void cre_tsk(unsigned short taskid, unsigned long isr_entry)
{
	ini_icb(taskid);
	g_icb[taskid].state_flag = ENABLE_FLG;
	g_icb[taskid].isr_entry = isr_entry;
	g_icb[taskid].context.pc_flg[0] = isr_entry & 0xFFFF;
//	g_icb[taskid].context.pc_flg[1] = ((isr_entry >> 8) & 0x0F00) | 0xC0; // U and I bits set
	g_icb[taskid].context.pc_flg[1] = ((isr_entry >> 8) & 0x0F00) | 0x40; // IPL = 0, I = 1
}

/**
 * void sta_tsk(unsigned short taskid);
 * @brief タスクを開始させる
 *
 * @param[in] taskid 開始させるタスク番号
 */
void sta_tsk(unsigned short taskid) // Interrupt enable
 {
//	_asm("\tpush.w R1");
	_asm("\tint #32");
	_asm("\tnop");
}

/**
 * void ext_tsk(void);
 * @brief タスクを終了させる
 */
void ext_tsk(void)
{
	g_icb[g_taskid].state_flag &= ~READY_FLG;
	
	_asm("\tint #33");
	_asm("\tnop");
}

/**
 * void svc_sta_tsk(void);
 * @brief svc_sta_tsk
 */
 
unsigned short taskid;
void svc_sta_tsk(void) // Interrupt disable
{
//	_asm("\tpop.w _taskid");
	_asm("\tmov.w R1, _taskid");

	g_icb[taskid].state_flag |= READY_FLG;
//	g_icb[taskid].context.fb = g_icb[7].context.fb; // ???
	g_icb[taskid].context.fb = g_icb[taskid].stack_btm - 0x20; // temporary
	g_icb[taskid].context.usp = g_icb[taskid].stack_btm;
	g_icb[taskid].context.pc_flg[1] &= 0x0f00; // IPL = 0
	g_icb[taskid].context.pc_flg[1] |= 0x0040; // Interrupt enable	
//	++g_icb[taskid].isr_cnt;  // no need

	_asm("\tjmp _scheduler");
//	scheduler();
}

/**
 * void svc_ext_tsk(void);
 * @brief svc_ext_tsk
 */
void svc_ext_tsk(void)
{
//	--g_icb[g_taskid].isr_cnt;
//	if (g_icb[g_taskid].isr_cnt == 0) g_icb[g_taskid].state_flag ^= READY_FLG;

	g_icb[g_taskid].context.pc_flg[0] = g_icb[g_taskid].isr_entry & 0xFFFF;
	g_icb[g_taskid].context.pc_flg[1] = ((g_icb[g_taskid].isr_entry >> 8) & 0x0F00) | 0x40;

	_asm("\tjmp _scheduler");
//	scheduler();
}
