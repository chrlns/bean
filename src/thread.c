/*
 *  Bean Java VM
 *  Copyright (C) 2005-2023 Christian Lins <christian@lins.me>
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
#include <linker.h>
#include <stack.h>
#include <stackframe.h>
#include <thread.h>
#include <thread_fn.h>
#include <vm.h>

extern VM* vm;

int init_thread(Thread *thread)
{
    thread->Priority   = THREAD_PRIORITY_NORMAL;
    thread->frameStack = Stack_new(64); // FIXME What's the appropriate size?
    return true;
}

void Stackframe_init(
    Stackframe *frame,
    Method* method,
    struct CONSTANTPOOL* constants)
{
    frame->constants = constants;
    frame->method    = method;
    frame->instPtr   = method->CodeInfo->Code;
    frame->localVars = (Varframe*)malloc(sizeof(Varframe) * method->localVarsLen);
    frame->localVarsLen = method->localVarsLen;
	frame->operandStack.limit = 0; // Max. size of the operand stack
	frame->operandStack.size = 0;  
	frame->operandStack.top = NULL;  

    assert(frame->constants != NULL);
    assert(frame->instPtr != NULL);
    assert(frame->method != NULL);
}

void* Stackframe_dispose(Stackframe* frame) {
    free(frame->localVars);
    free(frame);
    return NULL;
}

Stackframe* Stackframe_create_init_push(Thread* thread, Class* class, Method* method) {
    // Create stackframe for main method
    Stackframe *stackframe = malloc(sizeof(Stackframe));
    Stackframe_init(stackframe, method, class->ConstantPool);

    // and push it onto thread's invocation stack
    int ret = Stack_push(thread->frameStack, stackframe);
    assert(0 == ret); // check for unexpected stack overflow
    return stackframe;
}

int start_process(Class* new_class)
{
    Method* mainMethod = NULL;
    Method* clinitMethod = NULL;

    /* Create main thread */
    vm->ThreadNum++;
    vm->Threads = (Thread *)realloc(0, sizeof(Thread));

    /* Initialize main thread */
    init_thread(&vm->Threads[0]);

    /* Search for main method */
    mainMethod = find_method_name(new_class, "main");
    if (mainMethod == NULL) {
        dbgmsg("No main method found!");
        return false;
    }
    
    Stackframe_create_init_push(&(vm->Threads[0]), new_class, mainMethod);

    /* Search for class constructor */
    clinitMethod = find_method_name(new_class, "<clinit>");
    if (clinitMethod == NULL) {
        dbgmsg("No class constructor found. Continue with main.");
    } else {
        // Invoke class constructor using special INVOKE instruction
        dbgmsg("Invoke <clinit>");
        Stackframe_create_init_push(&(vm->Threads[0]), new_class, clinitMethod);
    }

    return true;
}

/* Look at the thread priorities and select the next ready thread */
Thread* Thread_next_ready(void)
{
    // Search for threads with unused timeslices
    for (int n = 0; n < vm->ThreadNum; n++) {
        if (vm->Threads[n].PriorityCurrent != 0) {
            return &vm->Threads[n];
        }
    }

    // Reset all priorities...
    for (int n = 0; n < vm->ThreadNum; n++) {
#ifdef DEBUG
        printf("[DEBUG] Setting Thread %u priority to %u\n", n, vm->Threads[n].Priority);
#endif
        vm->Threads[n].PriorityCurrent = vm->Threads[n].Priority;
    }

    //... and try again
    return Thread_next_ready();
}

void Thread_exec(Thread* thread, bool Xexecstep) {
    // Run the thread code until timeslice is over
    for (; thread->PriorityCurrent > 0; thread->PriorityCurrent >>= 1) {
        if (!vm->alive) {
            dbgmsg("Thread_exec returned.");
            return;
        }
        exec_thread(thread);

        if (Xexecstep) {
            dbgmsg("Press any key to continue execution...\n");
            getchar();
        }
    }   
}
