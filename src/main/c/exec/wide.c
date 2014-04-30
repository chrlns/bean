/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <bvm.h>

/* Extend local variables index by additional bytes
 * This instruction needs support by the following other opcodes:
 * iload, fload, aload, lload, dload, istore, fstore, astore, lstore, dstore, or ret (Type 1)
 * iinc (Type 2) */
void do_WIDE(struct VMTHREAD *thread)
{
    dbgmsg("WIDE");
}
