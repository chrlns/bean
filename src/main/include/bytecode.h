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

#ifndef _BYTECODE_H_
#define _BYTECODE_H_

#include <thread.h>

#define IL_NOP          0x00
#define IL_ACONST_NULL  0x01
#define IL_ICONST_M1    0x02
#define IL_ICONST_0     0x03
#define IL_ICONST_1     0x04
#define IL_ICONST_2     0x05
#define IL_ICONST_3     0x06
#define IL_ICONST_4     0x07
#define IL_ICONST_5     0x08
#define IL_LCONST_0     0x09
#define IL_LCONST_1     0x0A
#define IL_FCONST_0     0x0B
#define IL_FCONST_1     0x0C
#define IL_FCONST_2     0x0D
#define IL_DCONST_0     0x0E
#define IL_DCONST_1     0x0F
#define IL_BIPUSH       0x10
#define IL_SIPUSH       0x11
#define IL_LDC          0x12
#define IL_LDC_W        0x13
#define IL_LDC2_W       0x14
#define IL_ILOAD        0x15
#define IL_LLOAD        0x16
#define IL_FLOAD        0x17
#define IL_DLOAD        0x18
#define IL_ALOAD        0x19
#define IL_ILOAD_0      0x1A
#define IL_ILOAD_1      0x1B
#define IL_ILOAD_2      0x1C
#define IL_ILOAD_3      0x1D
#define IL_LLOAD_0      0x1E
#define IL_LLOAD_1      0x1F
#define IL_LLOAD_2      0x20
#define IL_LLOAD_3      0x21
#define IL_FLOAD_0      0x22
#define IL_FLOAD_1      0x23
#define IL_FLOAD_2      0x24
#define IL_FLOAD_3      0x25
#define IL_DLOAD_0      0x26
#define IL_DLOAD_1      0x27
#define IL_DLOAD_2      0x28
#define IL_DLOAD_3      0x29
#define IL_ALOAD_0      0x2A
#define IL_ALOAD_1      0x2B
#define IL_ALOAD_2      0x2C
#define IL_ALOAD_3      0x2D
#define IL_IALOAD       0x2E
#define IL_LALOAD       0x2F
#define IL_FALOAD       0x30
#define IL_DALOAD       0x31
#define IL_AALOAD       0x32
#define IL_BALOAD       0x33
#define IL_CALOAD       0x34
#define IL_SALOAD       0x35
#define IL_ISTORE       0x36
#define IL_LSTORE       0x37
#define IL_FSTORE       0x38
#define IL_DSTORE       0x39
#define IL_ASTORE       0x3A
#define IL_ISTORE_0     0x3B
#define IL_ISTORE_1     0x3C
#define IL_ISTORE_2     0x3D
#define IL_ISTORE_3     0x3E
#define IL_LSTORE_0     0x3F
#define IL_LSTORE_1     0x40
#define IL_LSTORE_2     0x41
#define IL_LSTORE_3     0x42
#define IL_FSTORE_0     0x43
#define IL_FSTORE_1     0x44
#define IL_FSTORE_2     0x45
#define IL_FSTORE_3     0x46
#define IL_DSTORE_0     0x47
#define IL_DSTORE_1     0x48
#define IL_DSTORE_2     0x49
#define IL_DSTORE_3     0x4A
#define IL_ASTORE_0     0x4B
#define IL_ASTORE_1     0x4C
#define IL_ASTORE_2     0x4D
#define IL_ASTORE_3     0x4E
#define IL_IASTORE      0x4F
#define IL_LASTORE      0x50
#define IL_FASTORE      0x51
#define IL_DASTORE      0x52
#define IL_AASTORE      0x53
#define IL_BASTORE      0x54
#define IL_CASTORE      0x55
#define IL_SASTORE      0x56
#define IL_POP          0x57
#define IL_POP2         0x58
#define IL_DUP          0x59
#define IL_DUP_X1       0x5A
#define IL_DUP_X2       0x5B
#define IL_DUP2         0x5C
#define IL_DUP2_X1      0x5D
#define IL_DUP2_X2      0x5E
#define IL_SWAP         0x5F
#define IL_IADD         0x60
#define IL_LADD         0x61
#define IL_FADD         0x62
#define IL_DADD         0x63
#define IL_ISUB         0x64
#define IL_LSUB         0x65
#define IL_FSUB         0x66
#define IL_DSUB         0x67
#define IL_IMUL         0x68
#define IL_LMUL         0x69
#define IL_FMUL         0x6A
#define IL_DMUL         0x6B
#define IL_IDIV         0x6C
#define IL_LDIV         0x6D
#define IL_FDIV         0x6E
#define IL_DDIV         0x6F
#define IL_IREM         0x70
#define IL_LREM         0x71
#define IL_FREM         0x72
#define IL_DREM         0x73
#define IL_INEG         0x74
#define IL_LNEG         0x75
#define IL_FNEG         0x76
#define IL_DNEG         0x77
#define IL_ISHL         0x78
#define IL_LSHL         0x79
#define IL_ISHR         0x7A
#define IL_LSHR         0x7B
#define IL_IUSHR        0x7C
#define IL_LUSHR        0x7D
#define IL_IAND         0x7E
#define IL_LAND         0x7F
#define IL_IOR          0x80
#define IL_LOR          0x81
#define IL_IXOR         0x82
#define IL_LXOR         0x83
#define IL_IINC         0x84
#define IL_I2L          0x85
#define IL_I2F          0x86
#define IL_I2D          0x87
#define IL_L2I          0x88
#define IL_L2F          0x89
#define IL_L2D          0x8A
#define IL_F2I          0x8B
#define IL_F2L          0x8C
#define IL_F2D          0x8D
#define IL_D2I          0x8E
#define IL_D2L          0x8F
#define IL_D2F          0x90
#define IL_I2B          0x91
#define IL_I2C          0x92
#define IL_I2S          0x93
#define IL_LCMP         0x94
#define IL_FCMPL        0x95
#define IL_FCMPG        0x96
#define IL_DCMPL        0x97
#define IL_DCMPG        0x98
#define IL_IFEQ         0x99
#define IL_IFNE         0x9A
#define IL_IFLT         0x9B
#define IL_IFGE         0x9C
#define IL_IFGT         0x9D
#define IL_IFLE         0x9E
#define IL_IF_ICMPEQ    0x9F
#define IL_IF_ICMPNE    0xA0
#define IL_IF_ICMPLT    0xA1
#define IL_IF_ICMPGE    0xA2
#define IL_IF_ICMPGT    0xA3
#define IL_IF_ICMPLE    0xA4
#define IL_IF_ACMPEQ    0xA5
#define IL_IF_ACMPNE    0xA6
#define IL_GOTO         0xA7
#define IL_JSR          0xA8
#define IL_RET          0xA9
#define IL_TABLESWITCH  0xAA
#define IL_LOOKUPSWITCH 0xAB
#define IL_IRETURN      0xAC
#define IL_LRETURN      0xAD
#define IL_FRETURN      0xAE
#define IL_DRETURN      0xAF
#define IL_ARETURN      0xB0
#define IL_RETURN       0xB1
#define IL_GETSTATIC    0xB2
#define IL_PUTSTATIC    0xB3
#define IL_GETFIELD     0xB4
#define IL_PUTFIELD     0xB5
#define IL_INVOKEVIRTUAL 0xB6
#define IL_INVOKESPECIAL 0xB7
#define IL_INVOKESTATIC 0xB8
#define IL_INVOKEINTERFACE 0xB9
#define IL_RESERVED1    0xBA
#define IL_NEW          0xBB
#define IL_NEWARRAY     0xBC
#define IL_ANEWARRAY    0xBD
#define IL_ARRAYLENGTH  0xBE
#define IL_ATHROW       0xBF
#define IL_CHECKCAST    0xC0
#define IL_INSTANCEOF   0xC1
#define IL_MONITORENTER 0xC2
#define IL_MONITOREXIT  0xC3
#define IL_WIDE         0xC4
#define IL_MULTIANEWARRAY 0xC5
#define IL_IFNULL       0xC6
#define IL_IFNONNULL    0xC7
#define IL_GOTO_W       0xC8
#define IL_JSR_W        0xC9

/* Reserved opcodes: */
#define IL_BREAKPOINT   0xCA
#define IL_IMPDEP1      0xFE
#define IL_IMPDEP2      0xFF


/* Methods */
void do_NOP(Thread* thread);
void do_ACONST_NULL(Thread* thread);
void do_ICONSTi(Thread* thread, int32_t constant);
void do_LCONSTi(Thread* thread, int64_t);
void do_FCONSTi(Thread* thread, float);
void do_DCONSTi(Thread* thread, double);
void do_BIPUSH(Thread* thread);
void do_SIPUSH(Thread* thread);
void do_LDC(Thread* thread);
void do_LDC_W(Thread* thread);
void do_LDC2_W(Thread* thread);
void do_ILOAD(Thread* thread);
void do_ILOADi(Thread* thread, int32_t);
void do_LLOAD(Thread* thread);
void do_LLOADi(Thread* thread, int32_t);
void do_FLOAD(Thread* thread);
void do_FLOADi(Thread* thread, int32_t);
void do_DLOAD(Thread* thread);
void do_DLOADi(Thread* thread, int32_t);
void do_ALOAD(Thread* thread);
void do_ALOADi(Thread* thread, int16_t);
void do_IALOAD(Thread* thread);
void do_LALOAD(Thread* thread);
void do_FALOAD(Thread* thread);
void do_DALOAD(Thread* thread);
void do_AALOAD(Thread* thread);
void do_BALOAD(Thread* thread);
void do_CALOAD(Thread* thread);
void do_SALOAD(Thread* thread);
void do_ISTORE(Thread* thread);
void do_LSTORE(Thread* thread);
void do_FSTORE(Thread* thread);
void do_DSTORE(Thread* thread);
void do_ASTORE(Thread* thread);
void do_ISTOREi(Thread* thread, int16_t);
void do_LSTOREi(Thread* thread, int16_t);
void do_FSTOREi(Thread* thread, int16_t);
void do_DSTOREi(Thread* thread, int16_t);
void do_ASTOREi(Thread* thread, int16_t);
void do_IASTORE(Thread* thread);
void do_LASTORE(Thread* thread);
void do_FASTORE(Thread* thread);
void do_DASTORE(Thread* thread);
void do_AASTORE(Thread* thread);
void do_BASTORE(Thread* thread);
void do_CASTORE(Thread* thread);
void do_SASTORE(Thread* thread);
void do_POP(Thread* thread);
void do_POP2(Thread* thread);
void do_DUP(Thread* thread);
void do_DUP_X1(Thread* thread);
void do_DUP_X2(Thread* thread);
void do_DUP2(Thread* thread);
void do_DUP2_X1(Thread* thread);
void do_DUP2_X2(Thread* thread);
void do_SWAP(Thread* thread);
void do_IADD(Thread* thread);
void do_LADD(Thread* thread);
void do_FADD(Thread* thread);
void do_DADD(Thread* thread);
void do_ISUB(Thread* thread);
void do_LSUB(Thread* thread);
void do_FSUB(Thread* thread);
void do_DSUB(Thread* thread);
void do_IMUL(Thread* thread);
void do_LMUL(Thread* thread);
void do_FMUL(Thread* thread);
void do_DMUL(Thread* thread);
void do_IDIV(Thread* thread);
void do_LDIV(Thread* thread);
void do_FDIV(Thread* thread);
void do_DDIV(Thread* thread);
void do_IREM(Thread* thread);
void do_LREM(Thread* thread);
void do_FREM(Thread* thread);
void do_DREM(Thread* thread);
void do_INEG(Thread* thread);
void do_LNEG(Thread* thread);
void do_FNEG(Thread* thread);
void do_DNEG(Thread* thread);
void do_ISHL(Thread* thread);
void do_LSHL(Thread* thread);
void do_ISHR(Thread* thread);
void do_LSHR(Thread* thread);
void do_IUSHR(Thread* thread);
void do_LUSHR(Thread* thread);
void do_IAND(Thread* thread);
void do_LAND(Thread* thread);
void do_IOR(Thread* thread);
void do_LOR(Thread* thread);
void do_IXOR(Thread* thread);
void do_LXOR(Thread* thread);
void do_IINC(Thread* thread);
void do_I2L(Thread* thread);
void do_I2F(Thread* thread);
void do_I2D(Thread* thread);
void do_L2I(Thread* thread);
void do_L2F(Thread* thread);
void do_L2D(Thread* thread);
void do_F2I(Thread* thread);
void do_F2L(Thread* thread);
void do_F2D(Thread* thread);
void do_D2I(Thread* thread);
void do_D2L(Thread* thread);
void do_D2F(Thread* thread);
void do_I2B(Thread* thread);
void do_I2C(Thread* thread);
void do_I2S(Thread* thread);
void do_LCMP(Thread* thread);
void do_FCMPL(Thread* thread);
void do_FCMPG(Thread* thread);
void do_DCMPL(Thread* thread);
void do_DCMPG(Thread* thread);
void do_IFEQ(Thread* thread);
void do_IFNE(Thread* thread);
void do_IFLT(Thread* thread);
void do_IFGE(Thread* thread);
void do_IFGT(Thread* thread);
void do_IFLE(Thread* thread);
void do_IF_ICMPEQ(Thread* thread);
void do_IF_ICMPNE(Thread* thread);
void do_IF_ICMPLT(Thread* thread);
void do_IF_ICMPGE(Thread* thread);
void do_IF_ICMPGT(Thread* thread);
void do_IF_ICMPLE(Thread* thread);
void do_IF_ACMPEQ(Thread* thread);
void do_IF_ACMPNE(Thread* thread);
void do_GOTO(Thread* thread);
void do_JSR(Thread* thread);
void do_RET(Thread* thread);
void do_TABLESWITCH(Thread* thread);
void do_LOOKUPSWITCH(Thread* thread);
void do_IRETURN(Thread* thread);
void do_LRETURN(Thread* thread);
void do_FRETURN(Thread* thread);
void do_DRETURN(Thread* thread);
void do_ARETURN(Thread* thread);
void do_RETURN(Thread* thread);
void do_GETSTATIC(Thread* thread);
void do_PUTSTATIC(Thread* thread);
void do_GETFIELD(Thread* thread);
void do_PUTFIELD(Thread* thread);
void do_INVOKEVIRTUAL(Thread* thread);
void do_INVOKESPECIAL(Thread* thread);
void do_INVOKESTATIC(Thread* thread);
void do_INVOKEINTERFACE(Thread* thread);
void do_RESERVED1(Thread* thread);
void do_NEW(Thread* thread);
void do_NEWARRAY(Thread* thread);
void do_ANEWARRAY(Thread* thread);
void do_ARRAYLENGTH(Thread* thread);
void do_ATHROW(Thread* thread);
void do_CHECKCAST(Thread* thread);
void do_INSTANCEOF(Thread* thread);
void do_MONITORENTER(Thread* thread);
void do_MONITOREXIT(Thread* thread);
void do_WIDE(Thread* thread);
void do_MULTIANEWARRAY(Thread* thread);
void do_IFNULL(Thread* thread);
void do_IFNONNULL(Thread* thread);
void do_GOTO_W(Thread* thread);
void do_JSR_W(Thread* thread);

/* Reserved opcodes(Thread* thread); */
void do_BREAKPOINT(Thread* thread);
void do_IMPDEP1(Thread* thread);
void do_IMPDEP2(Thread* thread);

#endif
