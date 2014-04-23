/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>
#include <xam_mem.h>

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
