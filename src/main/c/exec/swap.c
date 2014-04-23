/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Swap the top two operand stack values */
void do_SWAP(struct VMTHREAD *thread)
{
    dbgmsg("SWAP");

    void *value0;
    void *value1;
    struct stackframe_t *frame = current_frame(thread);

    /* Pop two values from operand stack */
    stack_pop(&(frame->operandStack), &value0);
    stack_pop(&(frame->operandStack), &value1);

    /* Push the two values swapped to the stack again */
    stack_push(&(frame->operandStack), value0);
    stack_push(&(frame->operandStack), value1);
}
