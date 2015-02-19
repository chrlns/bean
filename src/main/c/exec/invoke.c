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

void do_INVOKEINTERFACE(Thread *thread)
{
    dbgmsg("INVOKEINTERFACE not implemented");
    current_frame(thread)->instPtr++;
}

/*
 * Invoke instance method; dispatch based on runtime class type
 * (virtual method invokation).
 */
void do_INVOKEVIRTUAL(Thread *thread)
{
    dbgmsg("INVOKEVIRTUAL");

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

    // Pop nargs from operand stack

    // Pop object reference from operand stack

    // Invoke method
}

/*
 * Invoke instance method; special handling for superclass, private,
 * and instance initialization method invocations.
 */
void do_INVOKESPECIAL(Thread *thread)
{
    dbgmsg("INVOKESPECIAL not implemented")
        current_frame(thread)->instPtr++;
}

/*
 * Invoke static class method.
 * The invoked method must be declared as static and must not be abstract.
 */
void do_INVOKESTATIC(Thread *thread)
{
    dbgmsg("INVOKESTATIC");

    /* Index in the constant pool pointing to method reference */
    uint16_t index = Get2ByteOperand(current_frame(thread));
    uint16_t nargs = 0;         // TODO: Parse method descriptor

    /* Create a new frame for the invoking method */
    Stackframe *new_frame =
        malloc(sizeof(Stackframe));
    Stackframe *cur_frame = current_frame(thread);

    new_frame->method = dlink(thread, index, NULL);

    /* Operand stack contains nargs arguments for the called method
     * which form the contents of the new_frame's local var array */
    new_frame->localVarsLen = nargs;
    new_frame->localVars = malloc(sizeof(Varframe) * nargs);
    Varframe *var;
    for (int n = 0; n < nargs; n++) {
        // TODO: Add handling for long and double
        Stack_pop(&(cur_frame->operandStack), (void **) &var);
    }

    /* Push the new frame onto the frame stack */
    Stack_push(thread->frameStack, (void *) new_frame);
}
