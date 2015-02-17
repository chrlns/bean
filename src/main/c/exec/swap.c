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

#include <debug.h>
#include <vm.h>

/* Swap the top two operand stack values */
void do_SWAP(Thread *thread)
{
    dbgmsg("SWAP");

    void *value0;
    void *value1;
    Stackframe *frame = current_frame(thread);

    /* Pop two values from operand stack */
    Stack_pop(&(frame->operandStack), &value0);
    Stack_pop(&(frame->operandStack), &value1);

    /* Push the two values swapped to the stack again */
    Stack_push(&(frame->operandStack), value0);
    Stack_push(&(frame->operandStack), value1);
}
