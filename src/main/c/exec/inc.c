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

void do_IINC_WIDE(Thread *thread, int index, int value)
{
    /* Increment variable in local variable array */
}

/*
 * Increments the variable specified by the first operand (index)
 * by the int value of the seconds operand.
 */
void do_IINC(Thread *thread)
{
    dbgmsg("IINC");

    int index, value;

    index = Get1ByteOperand(current_frame(thread));     /* Increments IP by one */
    value = Get1ByteOperand(current_frame(thread));     /* Increments IP by one */
    do_IINC_WIDE(thread, index, value);
}
