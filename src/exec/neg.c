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

/* Negates the double value on top of the operand stack. */
void do_DNEG(Thread *thread) {
    dbgmsg("DNEG");

    double *value = (double *) current_frame(thread)->operandStack.top->data;

    *value = -(*value); /* Negate the value */
}

/* Negates the float value on top of the operand stack. */
void do_FNEG(Thread *thread) {
    dbgmsg("FNEG");

    float *value = (float *) current_frame(thread)->operandStack.top->data;
    ;

    *value = -(*value); /* Negate the value */
}

/* Negates the int value on top of the operand stack. */
void do_INEG(Thread *thread) {
    dbgmsg("INEG");

    int32_t *value = (int32_t*) current_frame(thread)->operandStack.top->data;

    *value = -(*value); /* Negate the value */
}

/* Negates the long value on top of the operand stack. */
void do_LNEG(Thread *thread) {
    dbgmsg("LNEG");

    int64_t *value = (int64_t *) current_frame(thread)->operandStack.top->data;

    *value = -(*value); /* Negate the value */
}
