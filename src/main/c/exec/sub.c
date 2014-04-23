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

void do_ISUB(struct VMTHREAD *thread)
{
    dbgmsg("ISUB");

    int *value1;
    int *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) - (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}

void do_LSUB(struct VMTHREAD *thread)
{
    dbgmsg("LSUB");

    int64_t *value1;
    int64_t *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int64_t *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) - (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}

void do_FSUB(struct VMTHREAD *thread)
{
    dbgmsg("FSUB");

    float *value1;
    float *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (float *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) - (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}

void do_DSUB(struct VMTHREAD *thread)
{
    dbgmsg("DSUB");

    double *value1;
    double *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (double *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) - (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}
