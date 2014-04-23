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

/* Integer division */
void do_IDIV(struct VMTHREAD *thread)
{
    dbgmsg("IDIV");

    int *value1;
    int *value2;
    int *result = xam_alloc(sizeof(int));
    struct stackframe_t *frame = current_frame(thread);

    stack_pop(&(frame->operandStack), (void **) &value2);
    stack_pop(&(frame->operandStack), (void **) &value1);

    *result = *value1 / *value2;

    stack_push(&(frame->operandStack), result);
}

/* Long integer division */
void do_LDIV(struct VMTHREAD *thread)
{
    dbgmsg("LDIV");

    int64_t *value1;
    int64_t *value2;
    int64_t *result = xam_alloc(sizeof(int64_t));
    struct stackframe_t *frame = current_frame(thread);

    stack_pop(&(frame->operandStack), (void **) &value2);
    stack_pop(&(frame->operandStack), (void **) &value1);

    *result = *value1 / *value2;

    stack_push(&(frame->operandStack), result);
}

/* Float division */
void do_FDIV(struct VMTHREAD *thread)
{
    dbgmsg("FDIV");

    float *value1;
    float *value2;
    float *result = xam_alloc(sizeof(float));
    struct stackframe_t *frame = current_frame(thread);

    stack_pop(&(frame->operandStack), (void **) &value2);
    stack_pop(&(frame->operandStack), (void **) &value1);

    *result = *value1 / *value2;

    stack_push(&(frame->operandStack), result);
}

/* Double division */
void do_DDIV(struct VMTHREAD *thread)
{
    dbgmsg("DDIV");

    double *value1;
    double *value2;
    double *result = xam_alloc(sizeof(double));
    struct stackframe_t *frame = current_frame(thread);

    stack_pop(&(frame->operandStack), (void **) &value2);
    stack_pop(&(frame->operandStack), (void **) &value1);

    *result = *value1 / *value2;

    stack_push(&(frame->operandStack), result);
}
