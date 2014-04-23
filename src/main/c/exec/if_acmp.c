/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Branch if reference comparison succeeds */
void do_IF_ACMPEQ(struct VMTHREAD *thread)
{
    int16_t offset;
    dbgmsg("IF_ACMPEQ");

    offset = Get2ByteOperand(current_frame(thread));
}

/* Branch if reference comparison succeeds */
void do_IF_ACMPNE(struct VMTHREAD *thread)
{
    int16_t offset;
    dbgmsg("IF_ACMPNE");

    offset = Get2ByteOperand(current_frame(thread));
}
