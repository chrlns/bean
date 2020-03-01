/*
 *  Bean Java VM
 *  Copyright (C) 2005-2020 Christian Lins <christian@lins.me>
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

/* Pushs an item from the runtime constant pool onto the operand stack. */
void do_LDC(Thread *thread) {
    dbgmsg("LDC");
    
    Stackframe* frame = current_frame(thread);
    Varframe *value = (Varframe*)malloc(sizeof (Varframe));
    struct CONSTANTPOOL* item = &frame->constants[*(frame->instPtr)];
    frame->instPtr++;

#ifdef DEBUG
    printf("\tLDC Tag = %u\n", item->Tag);
#endif
    switch (item->Tag) {
        case CONSTANTPOOL_UTF8: {
            value->data.ptr = item->Data; /* Pointer to a CONSTANT_UTF8_INFO structure */
            break;
        }
        case CONSTANTPOOL_INTEGER: {
            value->data.SignedInt32Value = (int32_t) ((struct CONSTANT_INTEGER_INFO*) item->Data)->Value;
            break;
        }
        case CONSTANTPOOL_FLOAT: {
            value->data.FloatValue = (float) ((struct CONSTANT_FLOAT_INFO*) item->Data)->Value;
            break;
        }
        case CONSTANTPOOL_STRING: {
            value->data.ptr = item->Data; /* Pointer to a CONSTANT_STRING_INFO structure */
            break;
        }
#ifdef DEBUG
        default: {
            dbgmsg("LDC Unknown Constant Pool Type. Exit!");
            exit(-1);
        }
#endif
    }

    /* Push value onto the stack */
    Stack_push(&(current_frame(thread)->operandStack), value);
}

void do_LDC_W(Thread *thread) {
}

void do_LDC2_W(Thread *thread) {
}
