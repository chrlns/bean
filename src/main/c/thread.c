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

#include <bvm.h>
#include <bvm_class.h>
#include <bvm_mem.h>
#include <bvm_process.h>
#include <bvm_link.h>


int init_thread(struct VMTHREAD *thread)
{
    thread->Priority = THREAD_PRIORITY_NORMAL;
    stack_init(&(thread->frameStack), 32); // FIXME What's the appropriate size?
    return true;
}

void stackframe_init(
    struct stackframe_t *frame,
    struct method_t* method,
    struct CONSTANTPOOL* constants)
{
    frame->constants = constants;
    frame->method    = method;
    frame->instPtr   = method->method_info->CodeInfo->Code;

    assert(frame->constants != NULL);
    assert(frame->instPtr != NULL);
    assert(frame->method != NULL);
}

struct VMCLASS* new_class_alloc()
{
    /* Create class struct */
    VM.LocalClassesNum++;
    VM.LocalClasses =
        (struct VMCLASS **) xam_realloc(VM.LocalClasses,
                                        sizeof(struct VMCLASS *) *
                                        VM.LocalClassesNum);
    VM.LocalClasses[VM.LocalClassesNum - 1] =
        (struct VMCLASS *) xam_alloc(sizeof(struct VMCLASS));

    return VM.LocalClasses[VM.LocalClassesNum - 1];
}

int start_process(FILE* class_file)
{
    struct method_t* mainMethod = NULL;
    struct method_t* clinitMethod = NULL;

    /* Create main thread */
    VM.ThreadNum++;
    VM.Threads =
        (struct VMTHREAD *) xam_realloc(0, sizeof(struct VMTHREAD));

    /* Initialize main thread */
    init_thread(&VM.Threads[0]);

    struct VMCLASS *new_class = new_class_alloc();

    if (load_class_file(class_file, new_class) == false) {
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
    stackframe_init(stackframe,
                    mainMethod,
                    VM.LocalClasses[VM.LocalClassesNum - 1]->ConstantPool);

    // and push it onto thread's invocation stack
    int ret = stack_push(&VM.Threads[0].frameStack, stackframe);
    assert(0 == ret); // check for unexpected stack overflow
    assert(1 == VM.Threads[0].frameStack.size);

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
#ifdef DEBUG
        printf("[DEBUG] Setting Thread %u priority to %u\n", n, VM.Threads[n].Priority);
#endif
        VM.Threads[n].PriorityCurrent = VM.Threads[n].Priority;
    }

    //... and try again
    return next_thread();
}

/* This method decides which thread is to be executed ("Green Threads") */
Thread* Thread_next(void)
{
    Thread *thread = NULL;

    while (VM.Running) {
        // Get next thread to be executed
        thread = next_thread();
        assert(thread != NULL);
    }
    
    return thread;
}

void Thread_exec(Thread* thread) {
    // Run the thread code until timeslice is over
    for (; thread->PriorityCurrent > 0; thread->PriorityCurrent >>= 1) {
        exec_thread(thread);
    }   
}
