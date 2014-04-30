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

#ifndef _XAM_STACK_H_
#define _XAM_STACK_H_

#include <stdint.h>
#include "bvm_types.h"
#include "bvm_method.h"

#define NULL 0

struct stack_element_t
{
	void*                   data; /* data structure */
	struct stack_element_t* next; /* ptr to next element */
};

struct stack_t
{
	unsigned int limit;   /* maximum number of elements */
	unsigned int size;    /* current number of elements */
	struct stack_element_t* top;
};

/* This stackframe is attached to every method invocation. */
struct stackframe_t
{
	/* Local variable array */
	struct varframe_t* localVars;
	int16_t            localVarsLen;

	/* Operand stack */
	struct stack_t operandStack;
	int16_t        operandStackSize; /* Max. size of the operand stack */

	/* Reference to the constant pool */
	struct CONSTANTPOOL* constantPool;

	/* Pointer to the current running opcode. */
	unsigned char* instPtr;

	/* Invoked method */
	struct METHOD* method;
};

void stackframe_init(struct stackframe_t* frame, struct METHOD* method);

void stack_init(struct stack_t* stack, unsigned int limit);
void stack_free(struct stack_t* stack);
int stack_pop(struct stack_t* stack, void** data);
int stack_push(struct stack_t* stack, void* data);

#endif
