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

#include <debug.h>
#include <linker.h>
#include <vm.h>

/* Fetch field from object */
void do_GETFIELD(Thread *thread)
{
    dbgmsg("GETFIELD");

    //uint16_t index = Get2ByteOperand(current_frame(thread));
    dbgmsg("Not implemented");
    exit(-10);
}

/* Get static field from class */
void do_GETSTATIC(Thread *thread) {
    dbgmsg("GETSTATIC");
    
    struct CONSTANT_CLASS_INFO *classInfo = NULL;
    struct CONSTANTPOOL *constant = NULL;
    struct CONSTANT_NAMETYPE_INFO *nameTypeInfo = NULL;
    struct CONSTANT_REF_INFO *refInfo = NULL;
    struct CONSTANT_UTF8_INFO *className = NULL;
    struct CONSTANT_UTF8_INFO *typeName = NULL;
    struct CONSTANT_UTF8_INFO *descName = NULL;

    uint16_t operand = 0;
    Stackframe* frame = current_frame(thread);
    assert(frame != NULL);

    operand = Get2ByteOperand(frame);
    constant = (struct CONSTANTPOOL *) &(frame->constants[operand - 1]);

    assert(constant != NULL);
    assert(constant->Tag == CONSTANTPOOL_FIELDREF);
    assert(constant->Data != NULL);

    refInfo = (struct CONSTANT_REF_INFO *) constant->Data;
    classInfo = (struct CONSTANT_CLASS_INFO *)
            frame->constants[refInfo->ClassIndex - 1].Data;
    nameTypeInfo = (struct CONSTANT_NAMETYPE_INFO *)
            frame->constants[refInfo->NameAndTypeIndex - 1].Data;

    className = (struct CONSTANT_UTF8_INFO *) frame->constants[classInfo->NameIndex - 1].Data;
#ifdef DEBUG
    printf("\tClass name = %s\n", className->Text);
#endif

    typeName = (struct CONSTANT_UTF8_INFO *) frame->constants[nameTypeInfo->NameIndex - 1].Data;
#ifdef DEBUG
    printf("\tField name = %s\n", typeName->Text);
#endif

    descName = (struct CONSTANT_UTF8_INFO *) frame->constants[nameTypeInfo->DescriptorIndex - 1].Data;
#ifdef DEBUG
    printf("\tField descriptor = %s\n", descName->Text);
#endif

    // We have to make sure that the given class and field type are
    // already loaded. If not they must be loaded now.
    Class* class = Classloader_forName(className->Text);

    // Push the scalar type value or object reference onto the stack
    // FIXME
    dbgmsg("Not implemented");
    exit(-10);
}
