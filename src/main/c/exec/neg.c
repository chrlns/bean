/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Negates the double value on top of the operand stack. */
void do_DNEG(struct VMTHREAD *thread)
{
    dbgmsg("DNEG");

    double *value =
        (double *) current_frame(thread)->operandStack.top->data;

    *value = -(*value);         /* Negate the value */
}

/* Negates the float value on top of the operand stack. */
void do_FNEG(struct VMTHREAD *thread)
{
    dbgmsg("FNEG");

    float *value =
        (float *) current_frame(thread)->operandStack.top->data;;

    *value = -(*value);         /* Negate the value */
}

/* Negates the int value on top of the operand stack. */
void do_INEG(struct VMTHREAD *thread)
{
    dbgmsg("INEG");

    int *value = (int *) current_frame(thread)->operandStack.top->data;

    *value = -(*value);         /* Negate the value */
}

/* Negates the long value on top of the operand stack. */
void do_LNEG(struct VMTHREAD *thread)
{
    dbgmsg("LNEG");

    int64_t *value =
        (int64_t *) current_frame(thread)->operandStack.top->data;

    *value = -(*value);         /* Negate the value */
}
