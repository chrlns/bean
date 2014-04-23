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

void do_ISHL(struct VMTHREAD *thread)
{
    dbgmsg("ISHL");

    int *value1;
    int *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int *) frame->operandStack.top->data;

    /* Shifting n bits left, where n are the lower 5bits of value2 */
    *value1 = (*value1) << ((*value2) & 0x1F);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}

void do_LSHL(struct VMTHREAD *thread)
{
    dbgmsg("LSHL");

    int64_t *value1;
    int *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int64_t *) frame->operandStack.top->data;

    /* Shifting n bits left, where n are the lower 6bits of value2 */
    *value1 = (*value1) << ((*value2) & 0x3F);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}

void do_ISHR(struct VMTHREAD *thread)
{
    dbgmsg("ISHR");

    int *value1;
    int *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int *) frame->operandStack.top->data;

    /* Shifting n bits left, where n are the lower 5bits of value2 */
    *value1 = (*value1) >> ((*value2) & 0x1F);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}

void do_LSHR(struct VMTHREAD *thread)
{
    dbgmsg("LSHR");

    int64_t *value1;
    int *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int64_t *) frame->operandStack.top->data;

    /* Shifting n bits left, where n are the lower 6bits of value2 */
    *value1 = (*value1) >> ((*value2) & 0x3F);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}

/* Logical shift right */
void do_IUSHR(struct VMTHREAD *thread)
{
    dbgmsg("IUSHR");

    int *value1;
    int *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int *) frame->operandStack.top->data;

    if (*value1 > 0) {
        *value1 = (*value1) >> (*value2 & 0x1F);
    } else if (*value1 < 0) {
        *value1 = (*value1 >> (*value2 & 0x1F)) + (2 << ~(*value2 & 0x1F));
    }

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}

/* Logical shift right */
void do_LUSHR(struct VMTHREAD *thread)
{
    dbgmsg("LUSHR");

    int64_t *value1;
    int *value2;
    struct stackframe_t *frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int64_t *) frame->operandStack.top->data;

    if (*value1 > 0) {
        *value1 = (*value1) >> (*value2 & 0x3F);
    } else if (*value1 < 0) {
        *value1 = (*value1 >> (*value2 & 0x3F)) + (2 << ~(*value2 & 0x3F));
    }

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    xam_free(value2);
}
