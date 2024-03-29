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

#include <stdlib.h>

#include <vm.h>

/* Load reference from local variable. */
void do_ALOAD(Thread *thread)
{
    dbgmsg("Not implemented");
    exit(-10);
    /*struct OperandStackFrame obj; */

    /* Load var from LocalVarArray */

    /* Push obj onto the stack */

}

/* Pushes object reference from local vars [0] onto the stack
   var[0] is always the reference to the local class (this). */
void do_ALOADi(Thread *thread, uint8_t localVarIndex)
{
    Stackframe* frame = current_frame(thread);
    Varframe* localVar = malloc(sizeof(Varframe));

#ifdef DEBUG
    printf("\tALOAD_%u\n", localVarIndex);
#endif
    assert(frame->localVarsLen > localVarIndex);


    /* Values from the operand stack may be freed somewhere, so we
     * need a deep copy of the local var array value */
//      *localVar = stackframe->localVars[localVarIndex];

    /* Push value to operand stack */
    Stack_push(&(frame->operandStack), localVar);
}

void do_IALOAD(Thread *thread)
{
    dbgmsg("Not implemented");
    exit(-10);
}

void do_LALOAD(Thread *thread)
{
    dbgmsg("Not implemented");
    exit(-10);
}

void do_FALOAD(Thread *thread)
{
    dbgmsg("Not implemented");
    exit(-10);
}

void do_DALOAD(Thread *thread)
{
    dbgmsg("Not implemented");
    exit(-10);
}

void do_AALOAD(Thread *thread)
{
    dbgmsg("Not implemented");
    exit(-10);
}

void do_BALOAD(Thread *thread)
{
    dbgmsg("Not implemented");
    exit(-10);
}

void do_CALOAD(Thread *thread)
{
    dbgmsg("Not implemented");
    exit(-10);
}

void do_SALOAD(Thread *thread)
{
    dbgmsg("Not implemented");
    exit(-10);
}
