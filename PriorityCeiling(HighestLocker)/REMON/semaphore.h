/**
 * @file semaphore.h
 * @brief セマフォ
 *
 * @author Kiminori Mizushino
 * @date 2007-05-05
 * @version 0.1
 */

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "icb.h"
#include "task.h"

#define MAX_SEMAPHORE 4

typedef struct _SEMAPHORE {
	unsigned short owner_tsk, wait_tsk;
} SEMAPHORE;

extern SEMAPHORE g_semaphore[MAX_SEMAPHORE];

void ini_sem(void);
void wai_sem(unsigned short sem);
void sig_sem(unsigned short sem);
void pol_sem(unsigned short sem);
void svc_wai_sem(void);
void svc_sig_sem(void);
void svc_pol_sem(void);

#endif
