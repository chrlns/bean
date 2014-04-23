/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "../include/xam.h"

void do_ISTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tISTORE\n");
#endif
}

void do_LSTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tLSTORE\n");
#endif
}

void do_LSTOREi(struct VMTHREAD *thread, int index)
{
#ifdef DEBUG
    printf("\tLSTOREi\n");
#endif
}

void do_ISTOREi(struct VMTHREAD *thread, int index)
{
#ifdef DEBUG
    printf("\tISTOREi\n");
#endif
}

void do_FSTOREi(struct VMTHREAD *thread, int index)
{
#ifdef DEBUG
    printf("\tFSTOREi\n");
#endif
}

void do_DSTOREi(struct VMTHREAD *thread, int index)
{
#ifdef DEBUG
    printf("\tDSTOREi\n");
#endif
}

void do_ASTOREi(struct VMTHREAD *thread, int index)
{
#ifdef DEBUG
    printf("\tASTOREi\n");
#endif
}

void do_FSTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tFSTORE\n");
#endif
}

void do_IASTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tIASTORE\n");
#endif
}

void do_FASTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tFASTORE\n");
#endif
}

void do_DASTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tDASTORE\n");
#endif
}

void do_AASTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tAASTORE\n");
#endif
}

void do_LASTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tLASTORE\n");
#endif
}

void do_BASTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tBASTORE\n");
#endif
}

void do_CASTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tCASTORE\n");
#endif
}

void do_SASTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tSASTORE\n");
#endif
}

void do_DSTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tDSTORE\n");
#endif
}

void do_ASTORE(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tASTORE\n");
#endif
}
