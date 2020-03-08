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

/* Set static field in class */
void do_PUTSTATIC(Thread *thread)
{
    uint16_t index;
    Stackframe* frame = current_frame(thread);
    dbgmsg("PUTSTATIC");

    // Index of the value that is to be put in the class
    // within the constant pool
    index = Get2ByteOperand(current_frame(thread));

    struct CONSTANTPOOL item = frame->constants[index - 1];

    #ifdef DEBUG
        printf("\tPUTSTATIC Tag = %u\n", item.Tag);
    #endif

    if (item.Tag == CONSTANTPOOL_FIELDREF) {
        struct CONSTANT_REF_INFO* fieldRef = (struct CONSTANT_REF_INFO*)item.Data;
        #ifdef DEBUG
            printf("\tClassIndex = %u\n", fieldRef->ClassIndex);
            printf("\tNameAndTypeIndex = %u\n", fieldRef->NameAndTypeIndex);
        #endif
        struct CONSTANT_CLASS_INFO* classInfo = (struct CONSTANT_CLASS_INFO*)
            &frame->constants[fieldRef->ClassIndex - 1];
        struct CONSTANT_NAMETYPE_INFO* nameTypeInfo = (struct CONSTANT_NAMETYPE_INFO*)
            &frame->constants[fieldRef->NameAndTypeIndex - 1];
    } else {
        printf("Unexpected CONSTANTPOOL item!");
        exit(-1);
    }
}
