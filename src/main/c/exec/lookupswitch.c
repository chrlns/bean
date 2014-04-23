/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Access jump table by key match and jump */
void do_LOOKUPSWITCH(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tLOOKUPSWITCH\n");
#endif

    /* This opcode is a little tricky because it uses padding bytes for
       address alignment (nobody knows why...), so the length of the
       operands is variable! */

}
