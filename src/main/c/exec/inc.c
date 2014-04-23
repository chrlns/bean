/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

void do_IINC_WIDE(struct VMTHREAD *thread, int index, int value)
{
    /* Increment variable in local variable array */
}

/*
 * Increments the variable specified by the first operand (index)
 * by the int value of the seconds operand.
 */
void do_IINC(struct VMTHREAD *thread)
{
    dbgmsg("IINC");

    int index, value;

    index = Get1ByteOperand(current_frame(thread));     /* Increments IP by one */
    value = Get1ByteOperand(current_frame(thread));     /* Increments IP by one */
    do_IINC_WIDE(thread, index, value);
}
