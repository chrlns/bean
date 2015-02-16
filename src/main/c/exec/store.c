/*
 *  Bean Java VM
 *  Copyright (C) 2005-2015 Christian Lins <christian@lins.me>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <vm.h>

void do_ISTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tISTORE\n");
#endif
}

void do_LSTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tLSTORE\n");
#endif
}

void do_LSTOREi(Thread *thread, int index)
{
#ifdef DEBUG
    printf("\tLSTOREi\n");
#endif
}

void do_ISTOREi(Thread *thread, int index)
{
#ifdef DEBUG
    printf("\tISTOREi\n");
#endif
}

void do_FSTOREi(Thread *thread, int index)
{
#ifdef DEBUG
    printf("\tFSTOREi\n");
#endif
}

void do_DSTOREi(Thread *thread, int index)
{
#ifdef DEBUG
    printf("\tDSTOREi\n");
#endif
}

void do_ASTOREi(Thread *thread, int index)
{
#ifdef DEBUG
    printf("\tASTOREi\n");
#endif
}

void do_FSTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tFSTORE\n");
#endif
}

void do_IASTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tIASTORE\n");
#endif
}

void do_FASTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tFASTORE\n");
#endif
}

void do_DASTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tDASTORE\n");
#endif
}

void do_AASTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tAASTORE\n");
#endif
}

void do_LASTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tLASTORE\n");
#endif
}

void do_BASTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tBASTORE\n");
#endif
}

void do_CASTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tCASTORE\n");
#endif
}

void do_SASTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tSASTORE\n");
#endif
}

void do_DSTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tDSTORE\n");
#endif
}

void do_ASTORE(Thread *thread)
{
#ifdef DEBUG
    printf("\tASTORE\n");
#endif
}
