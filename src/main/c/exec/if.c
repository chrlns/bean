/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

void IF(struct VMTHREAD *thread, bool(*cmpfnc) (int, int))
{
}

/* Branch if int comparison with zero succeeds */
void do_IFLE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIFLE\n");
#endif
}

/* Branch if int comparison with zero succeeds */
void do_IFGT(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIFGT\n");
#endif
}

/* Branch if int comparison with zero succeeds */
void do_IFGE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIFGE\n");
#endif
}

/* Branch if int comparison with zero succeeds */
void do_IFLT(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIFLT\n");
#endif
}

/* Branch if int comparison with zero succeeds */
void do_IFNE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIFNE\n");
#endif
}

/* Branch if int comparison with zero succeeds */
void do_IFEQ(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIFEQ\n");
#endif
}
