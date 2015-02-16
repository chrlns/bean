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

#include <thread.h>


void do_IADD(Thread* thread)
{
    dbgmsg("IADD");
    int *value1;
    int *value2;
    Stackframe* frame = current_frame(thread);

    /* Retrieving values from operand stack */
    Stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) + (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    free(value2);
}

void do_LADD(Thread* thread)
{
    dbgmsg("LADD");
    int64_t *value1;
    int64_t *value2;
    Stackframe* frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int64_t *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) + (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    free(value2);
}

void do_FADD(Thread* thread)
{
    dbgmsg("FADD");
    float *value1;
    float *value2;
    Stackframe* frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (float *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) + (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    free(value2);
}

void do_DADD(Thread* thread)
{
    dbgmsg("DADD");
    double *value1;
    double *value2;
    Stackframe* frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (double *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) + (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    free(value2);
}

void do_ISUB(Thread* thread)
{
    dbgmsg("ISUB");

    int *value1;
    int *value2;
    Stackframe* frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) - (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    free(value2);
}

void do_LSUB(Thread* thread)
{
    dbgmsg("LSUB");

    int64_t *value1;
    int64_t *value2;
    Stackframe* frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (int64_t *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) - (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    free(value2);
}

void do_FSUB(Thread* thread)
{
    dbgmsg("FSUB");

    float *value1;
    float *value2;
    Stackframe* frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (float *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) - (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    free(value2);
}

void do_DSUB(Thread* thread)
{
    dbgmsg("DSUB");

    double *value1;
    double *value2;
    Stackframe* frame = current_frame(thread);

    /* Retrieving values from operand stack */
    stack_pop(&(frame->operandStack), (void **) &value2);
    value1 = (double *) frame->operandStack.top->data;

    /* Subtracting */
    *value1 = (*value1) - (*value2);

    /* As we're modifying the stack top directly, we do not need to push
     * the result back. But we should free value2. */
    free(value2);
}
