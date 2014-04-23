/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Branch always */
void do_GOTO(struct VMTHREAD *thread)
{
    struct stackframe_t *frame = current_frame(thread);
    int16_t opcode = Get1ByteOperand(current_frame(thread));
    dbgmsg("GOTO");

    /* Original XAM had -= as operator here, don't know how that could work */
    //thread->InstructionPointer += (opcode - 2);
    frame->instPtr += (opcode - 3);
}

/* Branch always (far jump) */
void do_GOTO_W(struct VMTHREAD *thread)
{
    struct stackframe_t *frame = current_frame(thread);
    int32_t opcode = Get4ByteOperand(current_frame(thread));
    dbgmsg("GOTO_W");

    //thread->InstructionPointer += (opcode - 4);
    frame->instPtr += (opcode - 5);
}
