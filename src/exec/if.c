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

void IF(Thread *thread, bool(*cmpfnc) (int, int))
{
    dbgmsg("IF");
    dbgmsg("Not implemented");
    exit(-10);
}

/* Branch if int comparison with zero succeeds */
void do_IFLE(Thread *thread)
{
#ifdef DEBUG
    printf("\tIFLE\n");
#endif
    dbgmsg("Not implemented");
    exit(-10);
}

/* Branch if int comparison with zero succeeds */
void do_IFGT(Thread *thread)
{
#ifdef DEBUG
    printf("\tIFGT\n");
#endif
    dbgmsg("Not implemented");
    exit(-10);
}

/* Branch if int comparison with zero succeeds */
void do_IFGE(Thread *thread)
{
#ifdef DEBUG
    printf("\tIFGE\n");
#endif
    dbgmsg("Not implemented");
    exit(-10);
}

/* Branch if int comparison with zero succeeds */
void do_IFLT(Thread *thread)
{
#ifdef DEBUG
    printf("\tIFLT\n");
#endif
    dbgmsg("Not implemented");
    exit(-10);
}

/* Branch if int comparison with zero succeeds */
void do_IFNE(Thread *thread)
{
#ifdef DEBUG
    printf("\tIFNE\n");
#endif
    dbgmsg("Not implemented");
    exit(-10);
}

/* Branch if int comparison with zero succeeds */
void do_IFEQ(Thread *thread)
{
#ifdef DEBUG
    printf("\tIFEQ\n");
#endif
    dbgmsg("Not implemented");
    exit(-10);
}
