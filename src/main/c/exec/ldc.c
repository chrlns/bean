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

/* Pushs an item from the runtime constant pool onto the operand stack. */
void do_LDC(struct VMTHREAD *thread)
{
    dbgmsg("LDC");

    struct CONSTANTPOOL *item = NULL;
    struct varframe_t *value =
        (struct varframe_t *) xam_alloc(sizeof(struct varframe_t));

    current_frame(thread)->instPtr++;
    item =
        &thread->RunningClass->
        ConstantPool[*current_frame(thread)->instPtr - 1];

    switch (item->Tag) {
    case CONSTANTPOOL_INTEGER:
        {
            /*value->Value.SignedInt = (int32_t)((struct CONSTANT_INTEGER_INFO*)item->Data)->Value; */
            break;
        }
    case CONSTANTPOOL_FLOAT:
        {
            /*value->Value.Float = (float)((struct CONSTANT_FLOAT_INFO*)item->Data)->Value; */
            break;
        }
    case CONSTANTPOOL_STRING:
        {
            /*value->Value.pointer = item->Data; *//* Pointer to a string info. */
            break;
        }
    }

    /* Push value onto the stack */
    stack_push(&(current_frame(thread)->operandStack), value);
}

void do_LDC_W(struct VMTHREAD *thread)
{
}

void do_LDC2_W(struct VMTHREAD *thread)
{
}
