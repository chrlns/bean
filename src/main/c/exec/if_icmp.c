/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

void IF_ICMP(struct VMTHREAD *thread, bool(*cmpfnc) (int, int))
{
}

void do_IF_ICMPLE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIF_ICMPLE\n");
#endif
}

void do_IF_ICMPGT(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIF_ICMPGT\n");
#endif
}

void do_IF_ICMPGE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIF_ICMPGE\n");
#endif
}

void do_IF_ICMPLT(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIF_ICMPLT\n");
#endif
}

void do_IF_ICMPNE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tICMPNE\n");
#endif
}

void do_IF_ICMPEQ(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tNOP\n");
#endif
}
