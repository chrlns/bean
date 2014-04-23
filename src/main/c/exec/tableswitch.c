/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "../include/xam.h"

/* Access jump table by index and jump */
void do_TABLESWITCH(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tTABLESWITCH\n");
#endif

    /* This opcode is a little tricky because it uses 0 to 3 bytes for
       address alignment, so the operands are of variable size and additionally
       of variable number! */
}
