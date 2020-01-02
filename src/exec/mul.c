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

#include <debug.h>
#include <vm.h>

/* Integer multiplication */
void do_IMUL(Thread *thread)
{
    int *value1;
    int *value2;
    int *result = malloc(sizeof(int));
    dbgmsg("IMUL");

    Stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);
    Stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);

    *result = (*value1) * (*value2);

    Stack_push(&(current_frame(thread)->operandStack), result);
}

/* Long integer multiplication */
void do_LMUL(Thread *thread)
{
    int64_t *value1;
    int64_t *value2;
    int64_t *result = malloc(sizeof(int64_t));
    dbgmsg("LMUL");

    Stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);
    Stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);

    *result = (*value1) * (*value2);

    Stack_push(&(current_frame(thread)->operandStack), result);
}

/* Float multiplication */
void do_FMUL(Thread *thread)
{
    float *value1;
    float *value2;
    float *result = malloc(sizeof(float));
    dbgmsg("FMUL");

    Stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);
    Stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);

    *result = (*value1) * (*value2);

    Stack_push(&(current_frame(thread)->operandStack), result);
}

/* Double multiplication */
void do_DMUL(Thread *thread)
{
    double *value1;
    double *value2;
    double *result = malloc(sizeof(double));
    dbgmsg("DMUL");

    Stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);
    Stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);

    *result = (*value1) * (*value2);

    Stack_push(&(current_frame(thread)->operandStack), result);
}
