/*
 *  Bean Java VM
 *  Copyright (C) 2005-2014 Christian Lins <christian@lins.me>
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

#include <bvm.h>
#include <bvm_mem.h>

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
