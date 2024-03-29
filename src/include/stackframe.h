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

#ifndef _STACKFRAME_H_
#define _STACKFRAME_H_

#include <classfile.h>
#include <object.h>
#include <stack.h>
#include <types.h>

/* This stackframe is attached to every method invocation. */
typedef struct Stackframe
{
    /* Local variable array */
    Varframe* localVars;
    int16_t   localVarsLen;

    /* Operand stack */
    Stack operandStack;

    /* Reference to the constant pool */
    struct CONSTANTPOOL* constants;

    /* Pointer to the current running opcode. */
    unsigned char* instPtr;

    /* Invoked method */
    Method* method;

    Object* object;
} Stackframe;

void* Stackframe_dispose(Stackframe*);
#endif