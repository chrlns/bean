/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>
#include <xam_error.h>
#include <xam_mem.h>

/*
 * Pops all elements of the given stack.
 * The elements itself are released to the free heap space.
 */
void stack_free(struct stack_t *stack)
{
    assert(stack != NULL);

    while (stack->size > 0) {
        void *data;
        stack_pop(stack, &data);
        xam_free(data);
    }
}

/* Initializes the given stack struct. */
void stack_init(struct stack_t *stack, unsigned int limit)
{
    assert(stack != NULL);

    stack->limit = limit;
    stack->size = 0;
    stack->top = NULL;
}

int stack_pop(struct stack_t *stack, void **data)
{
    void *ptr;

    if (stack->size == 0) {
        return 1;               /* Stack underflow */
    } else {
        *data = stack->top->data;
        ptr = stack->top;
        stack->top = stack->top->next;
        stack->size--;
        xam_free(ptr);
        return 0;
    }
}

int stack_push(struct stack_t *stack, void *data)
{
    if (stack->size == stack->limit) {
        return 1;               /* Stack overflow */
    } else {
        struct stack_element_t *new =
            xam_alloc(sizeof(struct stack_element_t));
        new->data = data;
        new->next = stack->top;
        stack->top = new;
        stack->size++;
        return 0;
    }
}

void stackframe_init(struct stackframe_t *frame, struct METHOD *method)
{
    frame->method = method;
    frame->instPtr = method->Method->CodeInfo->Code;
}
