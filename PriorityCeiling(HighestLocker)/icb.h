/**
 * @file icb.h
 * @brief Interrupt Control Block
 *
 * @author Kiminori Mizushino
 * @date 2007-05-05
 * @version 0.1
 */

#ifndef ICB_H
#define ICB_H

//#define USE_TASKVIEWER

#define MAX_ICB 8
#define MAX_ISRCNT 32
#define STACK_SIZE 0x100

#define ENABLE_FLG	0x80
#define READY_FLG	0x40
#define WAIT_FLG	0x20
#define SEM_WAI_FLG	0x01

typedef struct _CONTEXT {
	unsigned short r0, r1, r2, r3;
	unsigned short a0, a1, fb, usp;
	unsigned short pc_flg[2];
} CONTEXT;

typedef struct _ICB {
	CONTEXT context;
	unsigned short state_flag, isr_cnt;
	unsigned long isr_entry;
	unsigned short stack_btm, wait_cnt;
} ICB;



extern ICB g_icb[MAX_ICB];
extern unsigned char g_stack[MAX_ICB][STACK_SIZE];
extern unsigned short g_priority[MAX_ICB];

void ini_icb(unsigned short n);
void swp_icb(ICB *icb1, ICB *icb2);

#define save_context() \
	_asm("\tmov.w _g_taskid, A0"); \
	_asm("\tshl.w #05h, A0"); /* ICB siza 32 bytes */ \
	_asm("\tpop.w _g_icb+00h[A0]"); /* r0 */ \
	_asm("\tpop.w _g_icb+02h[A0]"); /* r1 */ \
	_asm("\tpop.w _g_icb+04h[A0]"); /* r2 */ \
	_asm("\tpop.w _g_icb+06h[A0]"); /* r3 */ \
	_asm("\tpop.w _g_icb+08h[A0]"); /* a0 */ \
	_asm("\tpop.w _g_icb+0Ah[A0]"); /* a1 */ \
	_asm("\tpop.w _g_icb+0Ch[A0]"); /* fb */ \
	_asm("\tpop.w _g_icb+10h[A0]"); /* pc+flg[0] */ \
	_asm("\tpop.w _g_icb+12h[A0]"); /* pc;flg[1] */ \
	_asm("\tstc sp, _g_icb+0Eh[A0]"); /* sp */

extern unsigned short icb_temp;
#define load_context(n) \
	icb_temp = g_icb[n].context.r0; \
	_asm("mov.w _icb_temp, r0"); \
	icb_temp = g_icb[n].context.r1; \
	_asm("\tmov.w _icb_temp, r1"); \
	icb_temp = g_icb[n].context.r2; \
	_asm("\tmov.w _icb_temp, r2"); \
	icb_temp = g_icb[n].context.r3; \
	_asm("\tmov.w _icb_temp, r3"); \
	icb_temp = g_icb[n].context.a0; \
	_asm("\tmov.w _icb_temp, a0"); \
	icb_temp = g_icb[n].context.a0; \
	_asm("\tmov.w _icb_temp, a1"); \
	icb_temp = g_icb[n].context.fb; \
	_asm("\tldc _icb_temp, fb"); \
	icb_temp = g_icb[n].context.usp; \
	_asm("\tldc _icb_temp, sp"); \
	icb_temp = g_icb[n].context.pc_flg[1]; \
	_asm("\tpush.w _icb_temp"); \
	icb_temp = g_icb[n].context.pc_flg[0]; \
	_asm("\tpush.w _icb_temp");

#endif
