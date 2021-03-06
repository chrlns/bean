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

/* Branch if reference is NULL */
void do_IFNULL(Thread *thread)
{
    dbgmsg("IFNULL");

    Varframe *ref;
    uint16_t offset;
    Stackframe *frame = current_frame(thread);

    /* Pop reference from operand stack */
    Stack_pop(&(frame->operandStack), (void **) &ref);

    /* Get branch offset */
    offset = Get2ByteOperand(current_frame(thread));

    /* Check if we should branch (ref == NULL) */
    if (ref->data.ptr == NULL) {
        /* -1 because the IP points to the first operand byte */
        current_frame(thread)->instPtr += offset - 1;   // Correct?
    } else {
        /* else do nothing (continue with execution) */
        //thread->InstructionPointer++; // done in exec_thread
    }
}
