/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Branch if reference is NULL */
void do_IFNULL(struct VMTHREAD *thread)
{
    dbgmsg("IFNULL");

    struct varframe_t *ref;
    uint16_t offset;
    struct stackframe_t *frame = current_frame(thread);

    /* Pop reference from operand stack */
    stack_pop(&(frame->operandStack), (void **) &ref);

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
