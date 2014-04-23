/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_PROCESS_H_
#define _XAM_PROCESS_H_

#include "xam_class.h"
#include "xam_stack.h"
#include "xam_io.h"

#define PROCESS_STATUS_FREE     0
#define PROCESS_STATUS_SLEEPING 1
#define PROCESS_STATUS_WAITING  2
#define PROCESS_STATUS_BLOCKED  3
#define PROCESS_STATUS_RUNNING  4

#define THREAD_PRIORITY_HIGHEST     255
#define THREAD_PRIORITY_ABOVENORMAL 200
#define THREAD_PRIORITY_NORMAL      128
#define THREAD_PRIORITY_BELOWNORMAL 60
#define THREAD_PRIORITY_IDLE        0

#define current_frame(thread) \
	((struct stackframe_t*)thread->frameStack.top)

struct VMTHREAD
{
	struct VMCLASS*     RunningClass;    /* Pointer to the currently running class.*/
	struct METHOD_INFO* RunningMethod;   /* Pointer to the currently run. method. */
	struct VMTHREAD*    Parent;          /* Ref. to a parent thread. Can be NULL. */
	unsigned char       Priority;        /* Priority of this thread. */
	unsigned char       PriorityCurrent; /* Current priority (timeslice) */
	unsigned char       Status;
	struct stack_t      frameStack;      /* Top of this stack contains current stackframe */
};

void exec_process(void);
int  exec_thread(struct VMTHREAD*);
int  start_process(IOIdentifier);

#endif
