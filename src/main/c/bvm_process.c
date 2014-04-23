/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>
#include <xam_class.h>
#include <xam_mem.h>
#include <xam_process.h>
#include <xam_link.h>

/* Prototypes */
int LoadJavaClass(IOIdentifier, struct VMCLASS *);

int init_thread(struct VMTHREAD *thread)
{
    thread->Priority = THREAD_PRIORITY_NORMAL;
    return true;
}

int start_process(IOIdentifier processFileID)
{
    struct METHOD *mainMethod = NULL;
    struct METHOD *clinitMethod = NULL;

    /* Create main thread */
    VM.ThreadNum++;
    VM.Threads =
        (struct VMTHREAD *) xam_realloc(0, sizeof(struct VMTHREAD));

    /* Initialize main thread */
    init_thread(&VM.Threads[0]);

    /* Create class struct */
    VM.LocalClassesNum++;
    VM.LocalClasses =
        (struct VMCLASS **) xam_realloc(VM.LocalClasses,
                                        sizeof(struct VMCLASS *) *
                                        VM.LocalClassesNum);
    VM.LocalClasses[VM.LocalClassesNum - 1] =
        (struct VMCLASS *) xam_alloc(sizeof(struct VMCLASS));

    if (LoadJavaClass
        (processFileID,
         VM.LocalClasses[VM.LocalClassesNum - 1]) == false) {
        return false;
    }

    /* Search for class constructor */
    clinitMethod =
        find_method_name(VM.LocalClasses[VM.LocalClassesNum - 1],
                         "<clinit>");
    if (clinitMethod == NULL) {
        dbgmsg("No class constructor found!\n");
    } else {
        // Invoke class constructor using special INVOKE instruction
        // TODO:
        return false;
    }

    /* Search for main method */
    mainMethod =
        find_method_name(VM.LocalClasses[VM.LocalClassesNum - 1], "main");
    if (mainMethod == NULL) {
        dbgmsg("No main method found!\n");
        return RaiseException(ExceptionNoSuchMethod, "StartProcess",
                              __FILE__, __LINE__);
    }
    // Create stackframe for main method
    struct stackframe_t *stackframe =
        xam_alloc(sizeof(struct stackframe_t));
    stackframe_init(stackframe, mainMethod);

    // and push it onto thread's invokation stack
    stack_push(&VM.Threads[0].frameStack, stackframe);

    return true;
}

struct VMTHREAD *next_thread(void)
{
    // Search for threads with unused timeslices
    for (int n = 0; n < VM.ThreadNum; n++) {
        if (VM.Threads[n].PriorityCurrent != 0) {
            return &VM.Threads[n];
        }
    }

    // Reset all priorities...
    for (int n = 0; n < VM.ThreadNum; n++) {
        VM.Threads[n].PriorityCurrent = VM.Threads[n].Priority;
    }

    //... and try again
    return next_thread();
}

/* This method decides which thread is to be executed ("Green Threads") */
void exec_process(void)
{
    struct VMTHREAD *thread = NULL;

    while (VM.Running) {
        // Get next thread to be executed
        thread = next_thread();

        // Run the thread code until timeslice is over
        for (; thread->PriorityCurrent > 0; thread->PriorityCurrent >>= 1) {
            exec_thread(thread);
        }
    }
}
