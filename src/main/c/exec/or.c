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

/* Boolean OR int */
void do_IOR(Thread *thread)
{
    dbgmsg("IOR");

    int *value1;
    int *value2;
    int result;

    /* Pop two int values from operand stack */
    stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);
    stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);

    /* Perform bitwise OR operation */
    result = (*value1) | (*value2);

    /* Push result onto the operand stack */
    stack_push(&(current_frame(thread)->operandStack), &result);
}

void do_LOR(Thread *thread)
{
    dbgmsg("LOR");

    int64_t *value1;
    int64_t *value2;
    int64_t result;

    /* Pop two long values from operand stack */
    stack_pop(&(current_frame(thread)->operandStack), (void **) &value1);
    stack_pop(&(current_frame(thread)->operandStack), (void **) &value2);

    /* Perform bitwise exclusive OR operation */
    result = (*value1) | (*value2);

    /* Push result onto the operand stack */
    stack_push(&(current_frame(thread)->operandStack), &result);
}
