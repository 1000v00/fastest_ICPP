/**
 * @file svc.c
 * @brief svc定義`
 */

#include "svc.h"

/**
 * void svc_handler(void);
 * @brief int命令のハンドラ
 */
 
extern volatile unsigned short gg_svc; 
unsigned char int_ope_num;

void svc_handler(void)
{ // PUSHM R0,R1,R2,R3,A0,A1,FB	
	save_context(); // STACK -> ICB
#pragma ASM // int命令のオペコードから、割り込み番号を取得する
.glb _int_ope
	mov.w _g_icb+12h[A0], A1 ; pc_flg[1]
	and.w #0F00H, A1
	shl.w #-8, A1
	mov.w _g_icb+10h[A0], A0 ; pc_flg[0]
	sub.w #1, A0 ; calc int operetion src address
	sbb.w #0, A1
	lde.b [A1A0], _int_ope_num
	and.b #3Fh, _int_ope_num
#pragma ENDASM
	svc_jump_table[int_ope_num - 32]();
} // POPM R0,R1,R2,R3,A0,A1,FB 
