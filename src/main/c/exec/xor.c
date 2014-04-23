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

/* Boolean XOR int */
void do_IXOR(struct VMTHREAD *thread)
{
    dbgmsg("IXOR");

    int *value1;
    int *value2;
    int *result = xam_alloc(sizeof(int));
    struct stackframe_t *frame = current_frame(thread);

    /* Pop two int values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value1);
    stack_pop(&(frame->operandStack), (void **) &value2);

    /* Perform bitwise exclusive OR operation */
    *result = (*value1) ^ (*value2);

    /* Push result onto the operand stack */
    stack_push(&(frame->operandStack), result);
}

void do_LXOR(struct VMTHREAD *thread)
{
    dbgmsg("LXOR");

    int64_t *value1;
    int64_t *value2;
    int64_t *result = xam_alloc(sizeof(int64_t));
    struct stackframe_t *frame = current_frame(thread);

    /* Pop two long values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value1);
    stack_pop(&(frame->operandStack), (void **) &value2);

    /* Perform bitwise exclusive OR operation */
    *result = (*value1) ^ (*value2);

    /* Push result onto the operand stack */
    stack_push(&(frame->operandStack), result);
}
