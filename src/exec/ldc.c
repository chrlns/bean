/*
 *  Bean Java VM
 *  Copyright (C) 2005-2023 Christian Lins <christian@lins.me>
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
    Varframe* value = (Varframe*)malloc(sizeof(Varframe));
    uint8_t idx = *(++frame->instPtr); // Next byte is index byte
    struct CONSTANTPOOL* item = &frame->constants[idx - 1]; // -1 because real constant pool starts with 0
    //frame->instPtr++;

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
            // A reference to a String instance should be put onto the stack
            value->data.ptr = item->Data; /* Pointer to a CONSTANT_STRING_INFO structure */
            dbgmsg("Not implemented");
            exit(-10);
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
    dbgmsg("LDC_W");
    dbgmsg("Not implemented");
    exit(-10);
}

void do_LDC2_W(Thread *thread) {
    dbgmsg("LDC2_W");
    dbgmsg("Not implemented");
    exit(-10);
}
