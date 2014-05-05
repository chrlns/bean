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
#include <bvm_error.h>
#include <bvm_mem.h>

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
