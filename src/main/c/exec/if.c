/*
 *  Bean Java VM
 *  Copyright (C) 2005-2014 Christian Lins <christian@lins.me>
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

#include <bvm.h>

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
