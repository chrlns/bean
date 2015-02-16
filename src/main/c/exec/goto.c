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

/* Branch always */
void do_GOTO(Thread *thread)
{
    Stackframe *frame = current_frame(thread);
    int16_t opcode = Get1ByteOperand(current_frame(thread));
    dbgmsg("GOTO");

    /* Original XAM had -= as operator here, don't know how that could work */
    //thread->InstructionPointer += (opcode - 2);
    frame->instPtr += (opcode - 3);
}

/* Branch always (far jump) */
void do_GOTO_W(Thread *thread)
{
    Stackframe *frame = current_frame(thread);
    int32_t opcode = Get4ByteOperand(current_frame(thread));
    dbgmsg("GOTO_W");

    //thread->InstructionPointer += (opcode - 4);
    frame->instPtr += (opcode - 5);
}
