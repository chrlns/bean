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

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <debug.h>
#include <stackframe.h>
#include <thread.h>
#include <bytecode.h>

uint8_t Get1ByteOperand(Stackframe* frame)
{
    return *(++frame->instPtr);
}

uint16_t Get2ByteOperand(Stackframe* frame)
{
    uint16_t operand = 0x0000;

    operand = Get1ByteOperand(frame);
    operand = operand << 8;
    operand = operand | Get1ByteOperand(frame);

    return operand;
}

uint32_t Get4ByteOperand(Stackframe * frame)
{
    uint32_t operand = 0x00000000;

    operand = Get2ByteOperand(frame);
    operand = operand << 16;
    operand = operand | Get2ByteOperand(frame);

    return operand;
}

int exec_thread(Thread *thread)
{
    Stackframe* frame = current_frame(thread);
    
#ifdef DEBUG
    assert(frame != NULL);
    printf("Opcode %x (%p)\tClass %p\n",
           *(frame->instPtr), (void *) frame->instPtr,
           (void *) thread->RunningClass);
#endif

    // Instruction pointer is incremented by one AFTER execution,
    // except for the INVOKE and RETURN statements where this is handled in
    // the appropriate do-functions.
    uint8_t opcode = *(frame->instPtr);
    switch (opcode) {
    case IL_NOP:{              /* No operation */
            // Simply do nothing but incrementing IP
            break;
        }
    case IL_ACONST_NULL:       /* Pushes a NULL-reference onto the stack */
        {
            do_ACONST_NULL(thread);
            break;
        }
    case IL_ICONST_M1:         /* Pushes int -1 onto the stack */
        {
            do_ICONSTi(thread, -1);
            break;
        }
    case IL_ICONST_0:          /* Pushes int 0 onto the stack */
        {
            do_ICONSTi(thread, 0);
            break;
        }
    case IL_ICONST_1:          /* Pushes int 1 onto the stack */
        {
            do_ICONSTi(thread, 1);
            break;
        }
    case IL_ICONST_2:          /* Pushes int 2 onto the stack */
        {
            do_ICONSTi(thread, 2);
            break;
        }
    case IL_ICONST_3:          /* Pushes int 3 onto the stack */
        {
            do_ICONSTi(thread, 3);
            break;
        }
    case IL_ICONST_4:          /* Pushes int 4 onto the stack */
        {
            do_ICONSTi(thread, 4);
            break;
        }
    case IL_ICONST_5:          /* Pushes int 5 onto the stack */
        {
            do_ICONSTi(thread, 5);
            break;
        }
    case IL_LCONST_0:          /* Pushes long 0 onto the stack */
        {
            do_LCONSTi(thread, 0);
            break;
        }
    case IL_LCONST_1:          /* Pushes long 1 onto the stack */
        {
            do_LCONSTi(thread, 1);
            break;
        }
    case IL_FCONST_0:          /* Pushes 0.0f onto the stack */
        {
            do_FCONSTi(thread, 0.0f);
            break;
        }
    case IL_FCONST_1:          /* Pushes 1.0f onto the stack */
        {
            do_FCONSTi(thread, 1.0f);
            break;
        }
    case IL_FCONST_2:          /* Pushes 2.0f onto the stack */
        {
            do_FCONSTi(thread, 2.0f);
            break;
        }
    case IL_DCONST_0:          /* Pushes 0.0 onto the stack */
        {
            do_DCONSTi(thread, 0.0);
            break;
        }
    case IL_DCONST_1:          /* Pushes 1.0 onto the stack */
        {
            do_DCONSTi(thread, 1.0);
            break;
        }
    case IL_BIPUSH:            /* Expands a byte and pushes it as int onto the stack */
        {
            do_BIPUSH(thread);
            break;
        }
    case IL_SIPUSH:            /* Expands a short and pushes it as int onto the stack */
        {
            do_SIPUSH(thread);
            break;
        }
    case IL_LDC:               /* Pushes a 32-bit constant-pool entry */
        {
            do_LDC(thread);
            break;
        }
    case IL_LDC_W:             /* Pushes a 32-bit constant-pool entry (indexed by two bytes) */
        {
            do_LDC_W(thread);
            break;
        }
    case IL_LDC2_W:            /* Pushes a 64-bit constant-pool entry */
        {
            do_LDC2_W(thread);
            break;
        }
    case IL_ILOAD:             /* Pushes int from local variable index onto the stack */
        {
            do_ILOAD(thread);
            break;
        }
    case IL_LLOAD:             /* Pushes long from local variable index onto the stack */
        {
            do_LLOAD(thread);
            break;
        }
    case IL_FLOAD:             /* Pushes float from local variable index onto the stack */
        {
            do_FLOAD(thread);
            break;
        }
    case IL_DLOAD:             /* Pushes float from local variable index onto the stack */
        {
            do_DLOAD(thread);
            break;
        }
    case IL_ALOAD:             /* Pushes object reference from local vars onto the stack */
        {
            do_ALOAD(thread);
            break;
        }
    case IL_ILOAD_0:           /* Pushes int from local vars [0] onto the stack */
        {
            do_ILOADi(thread, 0);
            break;
        }
    case IL_ILOAD_1:           /* Pushes int from local vars [1] onto the stack */
        {
            do_ILOADi(thread, 1);
            break;
        }
    case IL_ILOAD_2:           /* Pushes int from local vars [2] onto the stack */
        {
            do_ILOADi(thread, 2);
            break;
        }
    case IL_ILOAD_3:           /* Pushes int from local vars [3] onto the stack */
        {
            do_ILOADi(thread, 3);
            break;
        }
    case IL_LLOAD_0:           /* Pushes long from local vars [0] onto the stack */
        {
            do_LLOADi(thread, 0);
            break;
        }
    case IL_LLOAD_1:           /* Pushes long from local vars [1] onto the stack */
        {
            do_LLOADi(thread, 1);
            break;
        }
    case IL_LLOAD_2:           /* Pushes long from local vars [2] onto the stack */
        {
            do_LLOADi(thread, 2);
            break;
        }
    case IL_LLOAD_3:           /* Pushes long from local vars [3] onto the stack */
        {
            do_LLOADi(thread, 3);
            break;
        }
    case IL_FLOAD_0:           /* Pushes float from local vars [0] onto the stack */
        {
            do_FLOADi(thread, 0);
            break;
        }
    case IL_FLOAD_1:           /* Pushes float from local vars [1] onto the stack */
        {
            do_FLOADi(thread, 1);
            break;
        }
    case IL_FLOAD_2:           /* Pushes float from local vars [2] onto the stack */
        {
            do_FLOADi(thread, 2);
            break;
        }
    case IL_FLOAD_3:           /* Pushes float from local vars [3] onto the stack */
        {
            do_FLOADi(thread, 3);
            break;
        }
    case IL_DLOAD_0:           /* Pushes double from local vars [0] onto the stack */
        {
            do_DLOADi(thread, 0);
            break;
        }
    case IL_DLOAD_1:           /* Pushes double from local vars [1] onto the stack */
        {
            do_DLOADi(thread, 1);
            break;
        }
    case IL_DLOAD_2:           /* Pushes double from local vars [2] onto the stack */
        {
            do_DLOADi(thread, 2);
            break;
        }
    case IL_DLOAD_3:           /* Pushes double from local vars [3] onto the stack */
        {
            do_DLOADi(thread, 3);
            break;
        }
    case IL_ALOAD_0:           /* Pushes object reference from local vars [0] onto the stack */
        {
            do_ALOADi(thread, 0);
            break;
        }
    case IL_ALOAD_1:
        {
            do_ALOADi(thread, 1);
            break;
        }
    case IL_ALOAD_2:
        {
            do_ALOADi(thread, 2);
            break;
        }
    case IL_ALOAD_3:
        {
            do_ALOADi(thread, 3);
            break;
        }
    case IL_IALOAD:
        {
            do_IALOAD(thread);
            break;
        }
    case IL_LALOAD:
        {
            do_LALOAD(thread);
            break;
        }
    case IL_FALOAD:
        {
            do_FALOAD(thread);
            break;
        }
    case IL_DALOAD:
        {
            do_DALOAD(thread);
            break;
        }
    case IL_AALOAD:
        {
            do_AALOAD(thread);
            break;
        }
    case IL_BALOAD:
        {
            do_BALOAD(thread);
            break;
        }
    case IL_CALOAD:
        {
            do_CALOAD(thread);
            break;
        }
    case IL_SALOAD:
        {
            do_SALOAD(thread);
            break;
        }
    case IL_ISTORE:
        {
            do_ISTORE(thread);
            break;
        }
    case IL_LSTORE:
        {
            do_LSTORE(thread);
            break;
        }
    case IL_FSTORE:
        {
            do_FSTORE(thread);
            break;
        }
    case IL_DSTORE:
        {
            do_DSTORE(thread);
            break;
        }
    case IL_ASTORE:
        {
            do_ASTORE(thread);
            break;
        }
    case IL_ISTORE_0:
        {
            do_ISTOREi(thread, 0);
            break;
        }
    case IL_ISTORE_1:
        {
            do_ISTOREi(thread, 1);
            break;
        }
    case IL_ISTORE_2:
        {
            do_ISTOREi(thread, 2);
            break;
        }
    case IL_ISTORE_3:
        {
            do_ISTOREi(thread, 3);
            break;
        }
    case IL_LSTORE_0:
        {
            do_LSTOREi(thread, 0);
            break;
        }
    case IL_LSTORE_1:
        {
            do_LSTOREi(thread, 1);
            break;
        }
    case IL_LSTORE_2:
        {
            do_LSTOREi(thread, 2);
            break;
        }
    case IL_LSTORE_3:
        {
            do_LSTOREi(thread, 3);
            break;
        }
    case IL_FSTORE_0:
        {
            do_FSTOREi(thread, 0);
            break;
        }
    case IL_FSTORE_1:
        {
            do_FSTOREi(thread, 1);
            break;
        }
    case IL_FSTORE_2:
        {
            do_FSTOREi(thread, 2);
            break;
        }
    case IL_FSTORE_3:
        {
            do_FSTOREi(thread, 3);
            break;
        }
    case IL_DSTORE_0:
        {
            do_DSTOREi(thread, 0);
            break;
        }
    case IL_DSTORE_1:
        {
            do_DSTOREi(thread, 1);
            break;
        }
    case IL_DSTORE_2:
        {
            do_DSTOREi(thread, 2);
            break;
        }
    case IL_DSTORE_3:
        {
            do_DSTOREi(thread, 3);
            break;
        }
    case IL_ASTORE_0:
        {
            do_ASTOREi(thread, 0);
            break;
        }
    case IL_ASTORE_1:
        {
            do_ASTOREi(thread, 1);
            break;
        }
    case IL_ASTORE_2:
        {
            do_ASTOREi(thread, 2);
            break;
        }
    case IL_ASTORE_3:
        {
            do_ASTOREi(thread, 3);
            break;
        }
    case IL_IASTORE:
        {
            do_IASTORE(thread);
            break;
        }
    case IL_LASTORE:
        {
            do_LASTORE(thread);
            break;
        }
    case IL_FASTORE:
        {
            do_FASTORE(thread);
            break;
        }
    case IL_DASTORE:
        {
            do_DASTORE(thread);
            break;
        }
    case IL_AASTORE:
        {
            do_AASTORE(thread);
            break;
        }
    case IL_BASTORE:
        {
            do_BASTORE(thread);
            break;
        }
    case IL_CASTORE:
        {
            do_CASTORE(thread);
            break;
        }
    case IL_SASTORE:
        {
            do_SASTORE(thread);
            break;
        }
    case IL_POP:
        {
            do_POP(thread);
            break;
        }
    case IL_POP2:
        {
            do_POP2(thread);
            break;
        }
    case IL_DUP:
        {
            do_DUP(thread);
            break;
        }
    case IL_DUP_X1:
        {
            do_DUP_X1(thread);
            break;
        }
    case IL_DUP_X2:
        {
            do_DUP_X2(thread);
            break;
        }
    case IL_DUP2:
        {
            do_DUP2(thread);
            break;
        }
    case IL_DUP2_X1:
        {
            do_DUP2_X1(thread);
            break;
        }
    case IL_DUP2_X2:
        {
            do_DUP2_X2(thread);
            break;
        }
    case IL_SWAP:
        {
            do_SWAP(thread);
            break;
        }
    case IL_IADD:
        {
            do_IADD(thread);
            break;
        }
    case IL_LADD:
        {
            do_LADD(thread);
            break;
        }
    case IL_FADD:
        {
            do_FADD(thread);
            break;
        }
    case IL_DADD:
        {
            do_DADD(thread);
            break;
        }
    case IL_ISUB:
        {
            do_ISUB(thread);
            break;
        }
    case IL_LSUB:
        {
            do_LSUB(thread);
            break;
        }
    case IL_FSUB:
        {
            do_FSUB(thread);
            break;
        }
    case IL_DSUB:
        {
            do_DSUB(thread);
            break;
        }
    case IL_IMUL:
        {
            do_IMUL(thread);
            break;
        }
    case IL_LMUL:
        {
            do_LMUL(thread);
            break;
        }
    case IL_FMUL:
        {
            do_FMUL(thread);
            break;
        }
    case IL_DMUL:
        {
            do_DMUL(thread);
            break;
        }
    case IL_IDIV:
        {
            do_IDIV(thread);
            break;
        }
    case IL_LDIV:
        {
            do_LDIV(thread);
            break;
        }
    case IL_FDIV:
        {
            do_FDIV(thread);
            break;
        }
    case IL_DDIV:
        {
            do_DDIV(thread);
            break;
        }
    case IL_IREM:
        {
            do_IREM(thread);
            break;
        }
    case IL_LREM:
        {
            do_LREM(thread);
            break;
        }
    case IL_FREM:
        {
            do_FREM(thread);
            break;
        }
    case IL_DREM:
        {
            do_DREM(thread);
            break;
        }
    case IL_INEG:
        {
            do_INEG(thread);
            break;
        }
    case IL_LNEG:
        {
            do_LNEG(thread);
            break;
        }
    case IL_FNEG:
        {
            do_FNEG(thread);
            break;
        }
    case IL_DNEG:
        {
            do_DNEG(thread);
            break;
        }
    case IL_ISHL:
        {
            do_ISHL(thread);
            break;
        }
    case IL_LSHL:
        {
            do_LSHL(thread);
            break;
        }
    case IL_ISHR:
        {
            do_ISHR(thread);
            break;
        }
    case IL_LSHR:
        {
            do_LSHR(thread);
            break;
        }
    case IL_IUSHR:
        {
            do_IUSHR(thread);
            break;
        }
    case IL_LUSHR:
        {
            do_LUSHR(thread);
            break;
        }
    case IL_IAND:
        {
            do_IAND(thread);
            break;
        }
    case IL_LAND:
        {
            do_LAND(thread);
            break;
        }
    case IL_IOR:
        {
            do_IOR(thread);
            break;
        }
    case IL_LOR:
        {
            do_LOR(thread);
            break;
        }
    case IL_IXOR:
        {
            do_IXOR(thread);
            break;
        }
    case IL_LXOR:
        {
            do_LXOR(thread);
            break;
        }
    case IL_IINC:
        {
            do_IINC(thread);
            break;
        }
    case IL_I2L:
        {
            do_I2L(thread);
            break;
        }
    case IL_I2F:
        {
            do_I2F(thread);
            break;
        }
    case IL_I2D:
        {
            do_I2D(thread);
            break;
        }
    case IL_L2I:
        {
            do_L2I(thread);
            break;
        }
    case IL_L2F:
        {
            do_L2F(thread);
            break;
        }
    case IL_L2D:
        {
            do_L2D(thread);
            break;
        }
    case IL_F2I:
        {
            do_F2I(thread);
            break;
        }
    case IL_F2L:
        {
            do_F2L(thread);
            break;
        }
    case IL_F2D:
        {
            do_F2D(thread);
            break;
        }
    case IL_D2I:
        {
            do_D2I(thread);
            break;
        }
    case IL_D2L:
        {
            do_D2L(thread);
            break;
        }
    case IL_D2F:
        {
            do_D2F(thread);
            break;
        }
    case IL_I2B:
        {
            do_I2B(thread);
            break;
        }
    case IL_I2C:
        {
            do_I2C(thread);
            break;
        }
    case IL_I2S:
        {
            do_I2S(thread);
            break;
        }
    case IL_LCMP:
        {
            do_LCMP(thread);
            break;
        }
    case IL_FCMPL:
        {
            do_FCMPL(thread);
            break;
        }
    case IL_FCMPG:
        {
            do_FCMPG(thread);
            break;
        }
    case IL_DCMPL:
        {
            do_DCMPL(thread);
            break;
        }
    case IL_DCMPG:
        {
            do_DCMPG(thread);
            break;
        }
    case IL_IFEQ:
        {
            do_IFEQ(thread);
            break;
        }
    case IL_IFNE:
        {
            do_IFNE(thread);
            break;
        }
    case IL_IFLT:
        {
            do_IFLT(thread);
            break;
        }
    case IL_IFGE:
        {
            do_IFGE(thread);
            break;
        }
    case IL_IFGT:
        {
            do_IFGT(thread);
            break;
        }
    case IL_IFLE:
        {
            do_IFLE(thread);
            break;
        }
    case IL_IF_ICMPEQ:
        {
            do_IF_ICMPEQ(thread);
            break;
        }
    case IL_IF_ICMPNE:
        {
            do_IF_ICMPNE(thread);
            break;
        }
    case IL_IF_ICMPLT:
        {
            do_IF_ICMPLT(thread);
            break;
        }
    case IL_IF_ICMPGE:
        {
            do_IF_ICMPGE(thread);
            break;
        }
    case IL_IF_ICMPGT:
        {
            do_IF_ICMPGT(thread);
            break;
        }
    case IL_IF_ICMPLE:
        {
            do_IF_ICMPLE(thread);
            break;
        }
    case IL_IF_ACMPEQ:
        {
            do_IF_ACMPEQ(thread);
            break;
        }
    case IL_IF_ACMPNE:
        {
            do_IF_ACMPNE(thread);
            break;
        }
    case IL_GOTO:
        {
            do_GOTO(thread);
            break;
        }
    case IL_JSR:
        {
            do_JSR(thread);
            break;
        }
    case IL_RET:
        {
            do_RET(thread);
            break;
        }
    case IL_TABLESWITCH:
        {
            do_TABLESWITCH(thread);
            break;
        }
    case IL_LOOKUPSWITCH:
        {
            do_LOOKUPSWITCH(thread);
            break;
        }
    case IL_IRETURN:
        {
            do_IRETURN(thread);
            break;
        }
    case IL_LRETURN:
        {
            do_LRETURN(thread);
            break;
        }
    case IL_FRETURN:
        {
            do_FRETURN(thread);
            break;
        }
    case IL_DRETURN:
        {
            do_DRETURN(thread);
            break;
        }
    case IL_ARETURN:
        {
            do_ARETURN(thread);
            break;
        }
    case IL_RETURN:
        {
            do_RETURN(thread);
            break;
        }
    case IL_GETSTATIC:
        {
            do_GETSTATIC(thread);
            break;
        }
    case IL_PUTSTATIC:
        {
            do_PUTSTATIC(thread);
            break;
        }
    case IL_GETFIELD:
        {
            do_GETFIELD(thread);
            break;
        }
    case IL_PUTFIELD:
        {
            do_PUTFIELD(thread);
            break;
        }
    case IL_INVOKEVIRTUAL:
        {
            do_INVOKEVIRTUAL(thread);
            break;
        }
    case IL_INVOKESPECIAL:
        {
            do_INVOKESPECIAL(thread);
            break;
        }
    case IL_INVOKESTATIC:
        {
            do_INVOKESTATIC(thread);
            break;
        }
    case IL_INVOKEINTERFACE:
        {
            do_INVOKEINTERFACE(thread);
            break;
        }
    case IL_NEW:
        {
            do_NEW(thread);
            break;
        }
    case IL_NEWARRAY:
        {
            do_NEWARRAY(thread);
            break;
        }
    case IL_ANEWARRAY:
        {
            do_ANEWARRAY(thread);
            break;
        }
    case IL_ARRAYLENGTH:
        {
            do_ARRAYLENGTH(thread);
            break;
        }
    case IL_ATHROW:
        {
            do_ATHROW(thread);
            break;
        }
    case IL_CHECKCAST:
        {
            do_CHECKCAST(thread);
            break;
        }
    case IL_INSTANCEOF:
        {
            do_INSTANCEOF(thread);
            break;
        }
    case IL_MONITORENTER:
        {
            do_MONITORENTER(thread);
            break;
        }
    case IL_MONITOREXIT:
        {
            do_MONITOREXIT(thread);
            break;
        }
    case IL_WIDE:
        {
            do_WIDE(thread);
            break;
        }
    case IL_MULTIANEWARRAY:
        {
            do_MULTIANEWARRAY(thread);
            break;
        }
    case IL_IFNULL:
        {
            do_IFNULL(thread);
            break;
        }
    case IL_IFNONNULL:
        {
            do_IFNONNULL(thread);
            break;
        }
    case IL_GOTO_W:
        {
            do_GOTO_W(thread);
            break;
        }
    case IL_JSR_W:
        {
            do_JSR_W(thread);
            break;
        }

        /* Reserved opcodes: */
    case IL_RESERVED1:
    case IL_BREAKPOINT:
    case IL_IMPDEP1:
    case IL_IMPDEP2:{
            // Do nothing
            break;
        }

    default:{
            /* Throw unknown opcode exception */
            printf("Unknown opcode %x\n", *(frame->instPtr));
            exit(false);
            break;
        }
    }

    // Instruction pointer is incremented by one. Some opcodes have already
    // incremented the pointer, but the last incrementation is done here
    frame->instPtr++;

#ifdef INTERACTIVE
    printf("Press any key to continue execution...\n");
    getchar();
#endif

    return true;
}
