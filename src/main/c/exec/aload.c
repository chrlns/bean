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
#include <bvm_mem.h>

/* Load reference from local variable. */
void do_ALOAD(struct VMTHREAD *thread)
{
    /*struct OperandStackFrame obj; */

    /* Load var from LocalVarArray */

    /* Push obj onto the stack */
}

/* Pushes object reference from local vars [0] onto the stack
   var[0] is always the reference to the local class (this). */
void do_ALOADi(struct VMTHREAD *thread, uint8_t localVarIndex)
{
    /*struct stackframe_t* stackframe = (struct stackframe_t*)thread->methodStack.top;
       struct varframe_t* localVar = xam_alloc(sizeof(struct varframe_t));

       #ifdef DEBUG
       printf("\tALOAD_%u\n", localVarIndex);
       #endif
       assert(stackframe->localVarsLen > localVarIndex);

     */
    /* Values from the operand stack may be freed somewhere, so we
     * need a deep copy of the local var array value */
//      *localVar = stackframe->localVars[localVarIndex];

    /* Push value to operand stack */
//      stack_push(&(thread->operandStack), localVar);
}

void do_IALOAD(struct VMTHREAD *thread)
{
}

void do_LALOAD(struct VMTHREAD *thread)
{
}

void do_FALOAD(struct VMTHREAD *thread)
{
}

void do_DALOAD(struct VMTHREAD *thread)
{
}

void do_AALOAD(struct VMTHREAD *thread)
{
}

void do_BALOAD(struct VMTHREAD *thread)
{
}

void do_CALOAD(struct VMTHREAD *thread)
{
}

void do_SALOAD(struct VMTHREAD *thread)
{
}
