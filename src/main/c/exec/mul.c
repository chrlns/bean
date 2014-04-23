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

/* Integer multiplication */
void do_IMUL(struct VMTHREAD *thread)
{
    int *value1;
    int *value2;
    int *result = xam_alloc(sizeof(int));
    dbgmsg("IMUL");

    stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);
    stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);

    *result = (*value1) * (*value2);

    stack_push(&(current_frame(thread)->operandStack), result);
}

/* Long integer multiplication */
void do_LMUL(struct VMTHREAD *thread)
{
    int64_t *value1;
    int64_t *value2;
    int64_t *result = xam_alloc(sizeof(int64_t));
    dbgmsg("LMUL");

    stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);
    stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);

    *result = (*value1) * (*value2);

    stack_push(&(current_frame(thread)->operandStack), result);
}

/* Float multiplication */
void do_FMUL(struct VMTHREAD *thread)
{
    float *value1;
    float *value2;
    float *result = xam_alloc(sizeof(float));
    dbgmsg("FMUL");

    stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);
    stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);

    *result = (*value1) * (*value2);

    stack_push(&(current_frame(thread)->operandStack), result);
}

/* Double multiplication */
void do_DMUL(struct VMTHREAD *thread)
{
    double *value1;
    double *value2;
    double *result = xam_alloc(sizeof(double));
    dbgmsg("DMUL");

    stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);
    stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);

    *result = (*value1) * (*value2);

    stack_push(&(current_frame(thread)->operandStack), result);
}
