/**
 * @file task.h
 * @brief É^ÉXÉNä«óù
 *
 * @author Kiminori Mizushino
 * @date 2007-05-05
 * @version 0.1
 */

#ifndef TASK_H
#define TASK_H

#include "icb.h"

extern volatile unsigned short g_taskid;

void ini_tsk(void);
void cre_tsk(unsigned short taskid, unsigned long pc);
void sta_tsk(unsigned short taskid);
void ext_tsk(void);
void svc_sta_tsk(void);
void svc_ext_tsk(void);

#endif
