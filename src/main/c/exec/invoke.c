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

#include <stdlib.h>

#include <classfile.h>
#include <debug.h>
#include <linker.h>
#include <vm.h>

extern Stackframe* Stackframe_create_init_push(Thread*, Class*, Method*);

/*
 * Basic invoke function.
 */
void invoke(Thread *thread)
{
    Stackframe* frame = current_frame(thread);
    uint16_t idx = Get2ByteOperand(frame);

    // Constant representing name and type of the to be invoked method
    struct CONSTANT_NAMETYPE_INFO* nameTypeInfo =
        (struct CONSTANT_NAMETYPE_INFO*)frame->constants[idx - 1].Data;
    struct CONSTANT_STRING_INFO* name = (struct CONSTANT_STRING_INFO*)frame->constants[nameTypeInfo->NameIndex - 1].Data;
    struct CONSTANT_STRING_INFO* desc = (struct CONSTANT_STRING_INFO*)frame->constants[nameTypeInfo->DescriptorIndex - 1].Data;
    struct CONSTANT_UTF8_INFO* nameStr = (struct CONSTANT_UTF8_INFO*)frame->constants[name->StringIndex - 1].Data;
    struct CONSTANT_UTF8_INFO* descStr = (struct CONSTANT_UTF8_INFO*)frame->constants[desc->StringIndex - 1].Data;

#ifdef DEBUG
    printf("\tName %u: %s (%u chars)\n", name->StringIndex, nameStr->Text, nameStr->Length);
    printf("\tDesc %u: %s (%u chars)\n", desc->StringIndex, descStr->Text, descStr->Length);
#endif
    
    // Resolve class identified by nameStr->Text
    Class* targetClass = find_class_by_name(nameStr->Text);
    
    // Find method in class
    Method* targetMethod = find_method_name(targetClass, descStr->Text);

    uint16_t nargs = 0;         // TODO: Parse method descriptor
    
    // Pop nargs from operand stack
    /* Operand stack contains nargs arguments for the called method
     * which form the contents of the new_frame's local var array */
    //new_frame->localVarsLen = nargs;
    //new_frame->localVars = malloc(sizeof(Varframe) * nargs);
    Varframe *var;
    for (int n = 0; n < nargs; n++) {
        // TODO: Add handling for long and double
        Stack_pop(&(frame->operandStack), (void **) &var);
    }
    
    // Pop object reference from operand stack
    void* objRef;
    Stack_pop(&(frame->operandStack), &objRef);

    // Invoke method by constructing a new Stackframe and 
    // push it onto the Thread's frameStack
    Stackframe* newFrame 
            = Stackframe_create_init_push(thread, targetClass, targetMethod);
}

void do_INVOKEINTERFACE(Thread *thread)
{
    dbgmsg("INVOKEINTERFACE");
    invoke(thread);
}

/*
 * Invoke instance method; dispatch based on runtime class type
 * (virtual method invokation).
 */
void do_INVOKEVIRTUAL(Thread *thread)
{
    dbgmsg("INVOKEDYNAMIC");
    invoke(thread);
}

/*
 * Invoke instance method; special handling for superclass, private,
 * and instance initialization method invocations.
 */
void do_INVOKESPECIAL(Thread *thread)
{
    dbgmsg("INVOKESPECIAL")
    invoke(thread);
}

/*
 * Invoke static class method.
 * The invoked method must be declared as static and must not be abstract.
 */
void do_INVOKESTATIC(Thread *thread)
{
    dbgmsg("INVOKESTATIC");
    invoke(thread);
}
