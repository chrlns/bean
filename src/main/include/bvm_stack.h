/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_STACK_H_
#define _XAM_STACK_H_

#include <stdint.h>
#include "xam_types.h"
#include "xam_method.h"

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
