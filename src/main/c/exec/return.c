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
#include <bvm_opcode.h>
#include <bvm_mem.h>

/*
 * The current method must have return type void. If the current method
 * is a synchronized method, the monitor acquired or reentered on invocation
 * of the method is released or exited (respectively) as if by execution
 * of a monitorexit instruction. If no exception is thrown, any values on
 * the operand stack of the current frame are discarded.
 * The interpreter then returns control to the invoker of the method,
 * reinstating the frame of the invoker.
 */
void do_RETURN(struct VMTHREAD *thread)
{
    dbgmsg("RETURN");
/*
	//struct STACKFRAME*       stackFrame;
	struct INVOKESTACKFRAME* invokeStackFrame;

	// Pop stackframe of current method
	//stack_pop(&(current_frame(thread)->methodStack), (void**)&stackFrame); MethodStackPop(&thread->Stack);
	//InvokeStackPop(&thread->Stack, &invokeStackFrame);
	//stack_pop(&(current_frame(thread)->invokeStack), (void**)&invokeStackFrame);

	if(invokeStackFrame->method == NULL) {
		dbgmsg("Execution has ended!");
	}

	// Release monitor if existing
	if(isAccessFlag(invokeStackFrame->method->Method, ACC_SYNCHRONIZED) == true) {
		do_MONITOREXIT(thread);
		current_frame(thread)->instPtr--;
	}

	// Set new method
	thread->RunningClass       = invokeStackFrame->method->Class;
	thread->RunningMethod      = invokeStackFrame->method->Method;
	//thread->InstructionPointer = invokeStackFrame->instruction_ptr;

	xam_free(stackFrame);*/
}

void do_ARETURN(struct VMTHREAD *thread)
{
}

void do_DRETURN(struct VMTHREAD *thread)
{
}

void do_FRETURN(struct VMTHREAD *thread)
{
}

void do_LRETURN(struct VMTHREAD *thread)
{
}

void do_IRETURN(struct VMTHREAD *thread)
{
}

void do_RET(struct VMTHREAD *thread)
{
}
