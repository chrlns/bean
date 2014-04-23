/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Boolean AND int */
void do_IAND(struct VMTHREAD *thread)
{
    dbgmsg("IAND");
    int *value1;
    int *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Pop two int values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value1);
    stack_pop(&(frame->operandStack), (void **) &value2);

    /* Perform bitwise AND operation */
    int result = (*value1) & (*value2);

    /* Push result onto the operand stack */
    stack_push(&(frame->operandStack), &result);
}

void do_LAND(struct VMTHREAD *thread)
{
    dbgmsg("LAND");
    int64_t *value1;
    int64_t *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Pop two long values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value1);
    stack_pop(&(frame->operandStack), (void **) &value2);

    /* Perform bitwise exclusive OR operation */
    int64_t result = (*value1) & (*value2);

    /* Push result onto the operand stack */
    stack_push(&(frame->operandStack), &result);
}
