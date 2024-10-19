/**
 * @file icb.c
 * @brief Interrupt Control Block
 */

#include "icb.h"
#include <string.h>

ICB g_icb[MAX_ICB];
unsigned char g_stack[MAX_ICB][STACK_SIZE];

unsigned short icb_temp;

/**
 * void ini_icb(unsigned short n);
 * @brief icbÇèâä˙âªÇ∑ÇÈ
 *
 * @param[in] n èâä˙âªÇ∑ÇÈicbî‘çÜ
 */
void ini_icb(unsigned short n)
{
	memset(&g_icb[n], 0, sizeof(ICB));
	g_icb[n].stack_btm = (unsigned short)(&g_stack[n][STACK_SIZE - 1]);
}

/**
 * void swp_icb(ICB *icb1, ICB *icb2);
 * @brief icbÇì¸ÇÍë÷Ç¶ÇÈ
 *
 * @param[in] *icb1 icb1
 * @param[in] *icb2 icb2
 */
void swp_icb(ICB *icb1, ICB *icb2)
{
	ICB tmp;
	memcpy(&tmp, icb1, sizeof(ICB));
	memcpy(icb1, icb2, sizeof(ICB));
	memcpy(icb2, &tmp, sizeof(ICB));
}
