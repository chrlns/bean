/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

void do_DUP(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tDUP\n");
#endif
}

void do_DUP_X1(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tDUP_X1\n");
#endif
}

void do_DUP_X2(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tDUP_X2\n");
#endif
}

void do_DUP2(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tDUP2\n");
#endif
}

void do_DUP2_X1(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tDUP2_X1\n");
#endif
}

void do_DUP2_X2(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tDUP2_X2\n");
#endif
}
