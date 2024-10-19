/**
 * @file icb.c
 * @brief Interrupt Control Block
 */

#include "icb.h"
#include <string.h>

ICB g_icb[MAX_ICB];
unsigned char g_stack[MAX_ICB][STACK_SIZE];
unsigned short g_priority[MAX_ICB];

unsigned short icb_temp;

/**
 * void ini_icb(unsigned short n);
 * @brief icb������������
 *
 * @param[in] n ����������ICB�ԍ�
 */
void ini_icb(unsigned short n)
{
	memset(&g_icb[n], 0, sizeof(ICB));
	g_icb[n].stack_btm = (unsigned short)(&g_stack[n][STACK_SIZE - 1]);
	g_priority[n] = n;
}

/**
 * void swp_icb(ICB *icb1, ICB *icb2);
 * @brief ICB�����ւ���
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
