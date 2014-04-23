/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>
#include <xam_mem.h>
#include <xam_types.h>

void JSR(struct VMTHREAD *thread, uint32_t offset)
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

void do_JSR_W(struct VMTHREAD *thread)
{
    uint32_t offset;
    dbgmsg("JSR_W");

    offset = Get4ByteOperand(current_frame(thread));
    JSR(thread, offset - 4);
}

void do_JSR(struct VMTHREAD *thread)
{
    uint16_t offset;
    dbgmsg("JSR");

    offset = Get2ByteOperand(current_frame(thread));
    JSR(thread, (uint32_t) offset - 2);
}
