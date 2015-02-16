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

/* Branch if reference comparison succeeds */
void do_IF_ACMPEQ(Thread *thread)
{
    int16_t offset;
    dbgmsg("IF_ACMPEQ");

    offset = Get2ByteOperand(current_frame(thread));
}

/* Branch if reference comparison succeeds */
void do_IF_ACMPNE(Thread *thread)
{
    int16_t offset;
    dbgmsg("IF_ACMPNE");

    offset = Get2ByteOperand(current_frame(thread));
}
