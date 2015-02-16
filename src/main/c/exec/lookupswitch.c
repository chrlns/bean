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

/* Access jump table by key match and jump */
void do_LOOKUPSWITCH(Thread *thread)
{
#ifdef DEBUG
    printf("\tLOOKUPSWITCH\n");
#endif

    /* This opcode is a little tricky because it uses padding bytes for
       address alignment (nobody knows why...), so the length of the
       operands is variable! */

}
