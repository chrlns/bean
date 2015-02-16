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
#include <bvm_mem.h>
#include <bvm_types.h>

void JSR(Thread *thread, uint32_t offset)
{
    struct varframe_t *frame =
        (struct varframe_t *) xam_alloc(sizeof(struct varframe_t));

    /* At the beginning of this function the thread->InstructionPointer
       points to the last branchbyte, so we have to correct this... */
    current_frame(thread)->instPtr++;

    /* Push the return address onto the stack */
    frame->data.ptr = current_frame(thread)->instPtr + offset;
    frame->type = JAVATYPE_RETADDR;     /* Return address */
    stack_push(&(current_frame(thread)->operandStack), frame);
}

void do_JSR_W(Thread *thread)
{
    uint32_t offset;
    dbgmsg("JSR_W");

    offset = Get4ByteOperand(current_frame(thread));
    JSR(thread, offset - 4);
}

void do_JSR(Thread *thread)
{
    uint16_t offset;
    dbgmsg("JSR");

    offset = Get2ByteOperand(current_frame(thread));
    JSR(thread, (uint32_t) offset - 2);
}
