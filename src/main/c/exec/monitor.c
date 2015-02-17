/*
 *  Bean Java VM
 *  Copyright (C) 2005-2015 Christian Lins <christian@lins.me>
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

#include <debug.h>
#include <vm.h>

/* Enter monitor for object */
void do_MONITORENTER(Thread *thread)
{
    dbgmsg("MONITORENTER");

    struct MONITOR *monitor;
    struct MONITOR *monitorTmp;
    Varframe *obj = (Varframe *)
        malloc(sizeof(Varframe));

    /* Get object reference from operand stack */
    Stack_pop(&(current_frame(thread)->operandStack), (void **) obj);

    /* Check if object reference is NULL */
    if (obj->data.ptr == NULL) {
        /* Throw a NullPointerException */
        return;
    } else {
        /* Check if there is a already existing monitor */
        /* monitor is != NULL at this point */
        monitor = VM.Monitors;  /* List head */
        while (monitor != NULL) {
            /* Does the monitor hold a lock on our object? */
            if (monitor->ObjectRef == obj->data.ptr) {  /* is pointer correct here? */
                if (monitor->ThreadRef == thread) {     /* There is already a monitor of this thread...
                                                           and we add a new one... */
                    monitorTmp = monitor->Next; /* Store reference to next element */
                    monitor->Next = (struct MONITOR *)
                        malloc(sizeof(struct MONITOR));
                    monitor = monitor->Next;

                    /* Edit the new monitor */
                    monitor->Next = monitorTmp;
                    monitor->ThreadRef = thread;
                    monitor->ObjectRef = obj->data.ptr; /* is pointer correct here? */

                    current_frame(thread)->instPtr++;
                } else {        /* Object is locked by another thread...
                                   We sleep down the thread and try it again later.
                                   Note that we do NOT increase the instruction pointer by now! */
                    thread->PriorityCurrent = 0x00;
                }
                break;          /* exit while(monitor != NULL) loop */
            }
            /* Proceed with next element */
            monitor = monitor->Next;
        }                       /* end while(monitor != NULL) */

        /* There were no monitors found, if:
           - VM.Monitors is NULL
           - List loop runs to its end */
        if (monitor == NULL) {
            /* No monitor for the object was found, so we create one... */
            monitor = (struct MONITOR *) malloc(sizeof(struct MONITOR));
            monitor->Next = NULL;
            monitor->ThreadRef = thread;
            monitor->ObjectRef = obj->data.ptr; /* is pointer correct here? */

            if (VM.Monitors == NULL) {
                VM.Monitors = monitor;
            } else {
                VM.Monitors->Next = monitor;
            }
        }
    }
}

/* Exit monitor for object */
void do_MONITOREXIT(Thread *thread)
{
    struct MONITOR *monitor;
    struct MONITOR *monitorTmp;
    Varframe *obj = (Varframe *)
        malloc(sizeof(Varframe));

    dbgmsg("MONITOREXIT");

    /* Get object reference from operand stack */
    Stack_pop(&(current_frame(thread)->operandStack), (void **) obj);

    /* Check if object reference is NULL */
    if (obj->data.ptr == NULL) {        /* is pointer correct here? */
        /* Throw a NullPointerException */
        return;
    }

    monitor = VM.Monitors;
    monitorTmp = NULL;
    while (monitor != NULL) {
        if (monitor->ObjectRef == obj->data.ptr) {      /* is pointer correct here? */
            if (monitor->ThreadRef == thread) {
                if (monitorTmp == NULL) {
                    VM.Monitors = monitor->Next;
                } else {
                    monitorTmp->Next = monitor->Next;
                }
                free(monitor);

                current_frame(thread)->instPtr++;
                return;
            } else {            /* Throw a IllegalMonitorStateException */
                dbgmsg("IllegalMonitorStateException\n");
                return;
            }
        }
        monitorTmp = monitor;
        monitor = monitor->Next;
    }

    /* No associated monitor was found, but we go on as normal... */
}
