/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

void do_DLOAD(struct VMTHREAD *thread)
{
    dbgmsg("DLOAD");
}

/* Pushes object reference from local vars [0] onto the stack
   var[0] is always the reference to the local class (this). */
void do_DLOADi(struct VMTHREAD *thread, int localVarIndex)
{
    dbgmsg("DLOADi");
}
