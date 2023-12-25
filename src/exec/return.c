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

extern VM* vm;

void check_end_of_exec(Thread* thread) {
    if (thread->frameStack->size == 0) {
        dbgmsg("Execution has ended!");
        vm->alive = false;
    }
}

/*
 * The current method must have return type void. If the current method
 * is a synchronized method, the monitor acquired or reentered on invocation
 * of the method is released or exited (respectively) as if by execution
 * of a monitorexit instruction. If no exception is thrown, any values on
 * the operand stack of the current frame are discarded.
 * The interpreter then returns control to the invoker of the method,
 * reinstating the frame of the invoker.
 */
void do_RETURN(Thread *thread) {
    dbgmsg("RETURN");

    Stackframe* frame;

    // Pop stackframe of current method
    Stack_pop(thread->frameStack, (void**)&frame);
    frame = Stackframe_dispose(frame);

    // Release monitor if existing
    /*if (isAccessFlag(invokeStackFrame->method->Method, ACC_SYNCHRONIZED) == true) {
        do_MONITOREXIT(thread);
        current_frame(thread)->instPtr--;
    }*/
    
    check_end_of_exec(thread); 
}

void do_ARETURN(Thread *thread)
{
    dbgmsg("ARETURN");
    
    Stackframe* frame;
    
    // Pop stackframe of current method
    Stack_pop(thread->frameStack, (void**)&frame);
    
    // Pop the object reference from the current operand stacks and
    // push it onto the invokers operand stack
    Object* objref;
    Stack_pop(&(frame->operandStack), (void **) &objref);
    
    Stackframe* invokerFrame = current_frame(thread);
    Stack_push(&(invokerFrame->operandStack), objref);
    
    frame = Stackframe_dispose(frame);
}

void do_DRETURN(Thread *thread)
{
    check_end_of_exec(thread);
    dbgmsg("DRETURN");
    dbgmsg("Not implemented");
    exit(-10);
}

void do_FRETURN(Thread *thread)
{
    check_end_of_exec(thread);
    dbgmsg("FRETURN");
    dbgmsg("Not implemented");
    exit(-10);
}

void do_LRETURN(Thread *thread)
{
    check_end_of_exec(thread); 
    dbgmsg("LRETURN");
    dbgmsg("Not implemented");
    exit(-10);
}

void do_IRETURN(Thread *thread)
{
    check_end_of_exec(thread);
    dbgmsg("IRETURN");
    dbgmsg("Not implemented");
    exit(-10);
}

void do_RET(Thread *thread)
{
    check_end_of_exec(thread);
    dbgmsg("RET");
    dbgmsg("Not implemented");
    exit(-10);
}
