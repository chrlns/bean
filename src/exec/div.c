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

#include <debug.h>
#include <vm.h>

/* Integer division */
void do_IDIV(Thread *thread)
{
    dbgmsg("IDIV");

    int *value1;
    int *value2;
    int *result = malloc(sizeof(int));
    Stackframe *frame = current_frame(thread);

    Stack_pop(&(frame->operandStack), (void **) &value2);
    Stack_pop(&(frame->operandStack), (void **) &value1);

    *result = *value1 / *value2;

    Stack_push(&(frame->operandStack), result);
}

/* Long integer division */
void do_LDIV(Thread *thread)
{
    dbgmsg("LDIV");

    int64_t *value1;
    int64_t *value2;
    int64_t *result = malloc(sizeof(int64_t));
    Stackframe *frame = current_frame(thread);

    Stack_pop(&(frame->operandStack), (void **) &value2);
    Stack_pop(&(frame->operandStack), (void **) &value1);

    *result = *value1 / *value2;

    Stack_push(&(frame->operandStack), result);
}

/* Float division */
void do_FDIV(Thread *thread)
{
    dbgmsg("FDIV");

    float *value1;
    float *value2;
    float *result = malloc(sizeof(float));
    Stackframe *frame = current_frame(thread);

    Stack_pop(&(frame->operandStack), (void **) &value2);
    Stack_pop(&(frame->operandStack), (void **) &value1);

    *result = *value1 / *value2;

    Stack_push(&(frame->operandStack), result);
}

/* Double division */
void do_DDIV(Thread *thread)
{
    dbgmsg("DDIV");

    double *value1;
    double *value2;
    double *result = malloc(sizeof(double));
    Stackframe *frame = current_frame(thread);

    Stack_pop(&(frame->operandStack), (void **) &value2);
    Stack_pop(&(frame->operandStack), (void **) &value1);

    *result = *value1 / *value2;

    Stack_push(&(frame->operandStack), result);
}
