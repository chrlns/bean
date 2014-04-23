/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Determine if object is of given type */
void do_INSTANCEOF(struct VMTHREAD *thread)
{
    dbgmsg("INSTANCEOF");

    uint16_t index;

    index = Get2ByteOperand(current_frame(thread));
}
