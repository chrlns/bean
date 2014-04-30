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
