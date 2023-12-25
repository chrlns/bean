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

#include <vm.h>

/**
 * Pops all elements of the given stack.
 * The elements itself are released to the free heap space.
 */
void Stack_destroy(Stack* stack)
{
    assert(stack != NULL);

    while (stack->size > 0) {
        void *data;
        Stack_pop(stack, &data);
        free(data);
    }
    
    free(stack);
}

/** Creates a new Stack instance ind initializes it */
Stack* Stack_new(unsigned int limit)
{
    assert(limit > 0);
    
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    stack->limit = limit;
    stack->size = 0;
    stack->top = NULL;
    
    return stack;
}

int Stack_pop(Stack* stack, void** data)
{
    #ifdef DEBUG
        printf("Stack_pop(%p) limit=%u, size=%u\n", (void*)stack, stack->limit, stack->size);
    #endif

    void *ptr;

    if (stack->size == 0) {
        return 1;  /* Stack underflow */
    } else {
        *data = stack->top->data;
        ptr = stack->top;
        stack->top = stack->top->next;
        stack->size--;
        free(ptr);
        return 0;
    }
}

int Stack_push(Stack* stack, void* data)
{
    #ifdef DEBUG
        printf("Stack_push(%p) limit=%u, size=%u\n", (void*)stack, stack->limit, stack->size);
    #endif

    if (stack->size == stack->limit) {
        return 1;  /* Stack overflow */
    } else {
        StackElement* new = malloc(sizeof(StackElement));
        new->data = data;
        new->next = stack->top;
        stack->top = new;
        stack->size++;
        return 0;
    }
}
