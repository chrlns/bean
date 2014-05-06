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

/* Create new object */
void do_NEW(struct VMTHREAD *thread)
{
    dbgmsg("NEW");

    struct stackframe_t* frame = current_frame(thread);
    uint16_t index = Get2ByteOperand(frame);
    struct CONSTANT_CLASS_INFO *class_info = (struct CONSTAND_CLASS_INFO*)
    	frame->constants[index - 1];
    struct CONSTANT_UTF8_INFO *class_name = (struct CONSTANT_UTF8_INFO*)
    	frame->constants[class_info->NameIndex - 1];
#ifdef DEBUG
    printf("\tClass name = %s\n", class_name->Text);
#endif
    struct vmobject_t* obj = (struct vmobject_t *)xam_malloc(sizeof(struct vmobject_t));
    stack_push(&(frame->operandStack), obj);
}
