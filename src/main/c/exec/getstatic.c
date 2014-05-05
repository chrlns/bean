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

/* Get static field from class */
void do_GETSTATIC(struct VMTHREAD *thread)
{
    struct CONSTANT_CLASS_INFO *classInfo = NULL;
    struct CONSTANTPOOL *constant = NULL;
    struct CONSTANT_NAMETYPE_INFO *nameTypeInfo = NULL;
    struct CONSTANT_REF_INFO *refInfo = NULL;
    
    uint16_t operand = 0;
    struct stackframe_t* frame = current_frame(thread);
    assert(frame != NULL);

    operand = Get2ByteOperand(frame);

    dbgmsg("GETSTATIC");

    constant = (struct CONSTANTPOOL *)&(frame->constants[operand - 1]);

    assert(constant != NULL);
    assert(constant->Tag == CONSTANTPOOL_FIELDREF);
    assert(constant->Data != NULL);

    refInfo   = (struct CONSTANT_REF_INFO *)constant->Data;
    classInfo = (struct CONSTANT_CLASS_INFO *)
        frame->constants[refInfo->ClassIndex - 1].Data;
    nameTypeInfo = (struct CONSTANT_NAMETYPE_INFO *)
        frame->constants[refInfo->NameAndTypeIndex - 1].Data;
}
