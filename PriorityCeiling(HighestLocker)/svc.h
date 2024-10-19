/**
 * @file svc.h
 * @brief svc’è‹``
 *
 * @author Kiminori Mizushino
 * @date 2007-05-05
 * @version 0.1
 */

#ifndef SVC_H
#define SVC_H

#include "icb.h"
#include "task.h"

void svc_handler(void);
#pragma INTERRUPT svc_handler

void svc_wai_sem(void);
void svc_pol_sem(void);
void svc_sig_sem(void);
void svc_cre_tsk(void);
void svc_sta_tsk(void);
void svc_ext_tsk(void);
//void svc_wai_tsk(void);


typedef void(*svc_func)(void);
const svc_func svc_jump_table[] = {
	svc_sta_tsk, svc_ext_tsk, 0,
	svc_wai_sem, svc_sig_sem, svc_pol_sem
}; // 0:OLD svc_wai_tsk

#endif
