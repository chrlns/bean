/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>
#include <xam_link.h>
#include <xam_mem.h>

void do_INVOKEINTERFACE(struct VMTHREAD *thread)
{
    dbgmsg("INVOKEINTERFACE not implemented");
    current_frame(thread)->instPtr++;
}

/* 
 * Invoke instance method; dispatch based on runtime class type 
 * (virtual method invokation).
 */
void do_INVOKEVIRTUAL(struct VMTHREAD *thread)
{
    dbgmsg("INVOKEVIRTUAL");
}

/* 
 * Invoke instance method; special handling for superclass, private, 
 * and instance initialization method invocations. 
 */
void do_INVOKESPECIAL(struct VMTHREAD *thread)
{
    dbgmsg("INVOKESPECIAL not implemented")
        current_frame(thread)->instPtr++;
}

/* 
 * Invoke static class method. 
 * The invoked method must be declared as static and must not be abstract.
 */
void do_INVOKESTATIC(struct VMTHREAD *thread)
{
    dbgmsg("INVOKESTATIC");

    /* Index in the constant pool pointing to method reference */
    uint16_t index = Get2ByteOperand(current_frame(thread));
    uint16_t nargs = 0;         // TODO: Parse method descriptor 

    /* Create a new frame for the invoking method */
    struct stackframe_t *new_frame =
        xam_alloc(sizeof(struct stackframe_t));
    struct stackframe_t *cur_frame = current_frame(thread);

    new_frame->method = dlink(thread, index, NULL);

    /* Operand stack contains nargs arguments for the called method 
     * which form the contents of the new_frame's local var array */
    new_frame->localVarsLen = nargs;
    new_frame->localVars = xam_alloc(sizeof(struct varframe_t) * nargs);
    struct varframe_t *var;
    for (int n = 0; n < nargs; n++) {
        // TODO: Add handling for long and double
        stack_pop(&(cur_frame->operandStack), (void **) &var);
    }

    /* Push the new frame onto the frame stack */
    stack_push(&(thread->frameStack), (void *) new_frame);
}
