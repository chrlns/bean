/*
 *  Bean Java VM
 *  Copyright (C) 2005-2014 Christian Lins <christian@lins.me>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _THREAD_H_
#define _THREAD_H_

#include <classloaderass.h"
#include "bvm_stack.h"
#include "bvm_io.h"

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
	((struct stackframe_t*)thread->frameStack.top->data)

typedef struct
{
    struct VMCLASS*     RunningClass;    /* Pointer to the currently running class.*/
    struct METHOD_INFO* RunningMethod;   /* Pointer to the currently run. method. */
    struct VMTHREAD*    Parent;          /* Ref. to a parent thread. Can be NULL. */
    unsigned char       Priority;        /* Priority of this thread. */
    unsigned char       PriorityCurrent; /* Current priority (timeslice) */
    unsigned char       Status;
    struct stack_t      frameStack;      /* Top of this stack contains current stackframe */
} Thread;

int  exec_thread(struct VMTHREAD*);
int  start_process(FILE*);

Thread* Thread_next(VM* vm);
void Thread_exec(Thread* thread);

#endif
