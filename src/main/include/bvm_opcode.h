/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_OPCODE_H_
#define _XAM_OPCODE_H_

#include "xam_process.h"
#include "xam_types.h"

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
void do_NOP(struct VMTHREAD* thread);
void do_ACONST_NULL(struct VMTHREAD* thread);
void do_ICONSTi(struct VMTHREAD* thread, int32_t constant);
void do_LCONSTi(struct VMTHREAD* thread, int64_t);
void do_FCONSTi(struct VMTHREAD* thread, float);
void do_DCONSTi(struct VMTHREAD* thread, double);
void do_BIPUSH(struct VMTHREAD* thread);
void do_SIPUSH(struct VMTHREAD* thread);
void do_LDC(struct VMTHREAD* thread);
void do_LDC_W(struct VMTHREAD* thread);
void do_LDC2_W(struct VMTHREAD* thread);
void do_ILOAD(struct VMTHREAD* thread);
void do_ILOADi(struct VMTHREAD* thread, int32_t);
void do_LLOAD(struct VMTHREAD* thread);
void do_LLOADi(struct VMTHREAD* thread, int32_t);
void do_FLOAD(struct VMTHREAD* thread);
void do_FLOADi(struct VMTHREAD* thread, int32_t);
void do_DLOAD(struct VMTHREAD* thread);
void do_DLOADi(struct VMTHREAD* thread, int32_t);
void do_ALOAD(struct VMTHREAD* thread);
void do_ALOADi(struct VMTHREAD* thread, int16_t);
void do_IALOAD(struct VMTHREAD* thread);
void do_LALOAD(struct VMTHREAD* thread);
void do_FALOAD(struct VMTHREAD* thread);
void do_DALOAD(struct VMTHREAD* thread);
void do_AALOAD(struct VMTHREAD* thread);
void do_BALOAD(struct VMTHREAD* thread);
void do_CALOAD(struct VMTHREAD* thread);
void do_SALOAD(struct VMTHREAD* thread);
void do_ISTORE(struct VMTHREAD* thread);
void do_LSTORE(struct VMTHREAD* thread);
void do_FSTORE(struct VMTHREAD* thread);
void do_DSTORE(struct VMTHREAD* thread);
void do_ASTORE(struct VMTHREAD* thread);
void do_ISTOREi(struct VMTHREAD* thread, int16_t);
void do_LSTOREi(struct VMTHREAD* thread, int16_t);
void do_FSTOREi(struct VMTHREAD* thread, int16_t);
void do_DSTOREi(struct VMTHREAD* thread, int16_t);
void do_ASTOREi(struct VMTHREAD* thread, int16_t);
void do_IASTORE(struct VMTHREAD* thread);
void do_LASTORE(struct VMTHREAD* thread);
void do_FASTORE(struct VMTHREAD* thread);
void do_DASTORE(struct VMTHREAD* thread);
void do_AASTORE(struct VMTHREAD* thread);
void do_BASTORE(struct VMTHREAD* thread);
void do_CASTORE(struct VMTHREAD* thread);
void do_SASTORE(struct VMTHREAD* thread);
void do_POP(struct VMTHREAD* thread);
void do_POP2(struct VMTHREAD* thread);
void do_DUP(struct VMTHREAD* thread);
void do_DUP_X1(struct VMTHREAD* thread);
void do_DUP_X2(struct VMTHREAD* thread);
void do_DUP2(struct VMTHREAD* thread);
void do_DUP2_X1(struct VMTHREAD* thread);
void do_DUP2_X2(struct VMTHREAD* thread);
void do_SWAP(struct VMTHREAD* thread);
void do_IADD(struct VMTHREAD* thread);
void do_LADD(struct VMTHREAD* thread);
void do_FADD(struct VMTHREAD* thread);
void do_DADD(struct VMTHREAD* thread);
void do_ISUB(struct VMTHREAD* thread);
void do_LSUB(struct VMTHREAD* thread);
void do_FSUB(struct VMTHREAD* thread);
void do_DSUB(struct VMTHREAD* thread);
void do_IMUL(struct VMTHREAD* thread);
void do_LMUL(struct VMTHREAD* thread);
void do_FMUL(struct VMTHREAD* thread);
void do_DMUL(struct VMTHREAD* thread);
void do_IDIV(struct VMTHREAD* thread);
void do_LDIV(struct VMTHREAD* thread);
void do_FDIV(struct VMTHREAD* thread);
void do_DDIV(struct VMTHREAD* thread);
void do_IREM(struct VMTHREAD* thread);
void do_LREM(struct VMTHREAD* thread);
void do_FREM(struct VMTHREAD* thread);
void do_DREM(struct VMTHREAD* thread);
void do_INEG(struct VMTHREAD* thread);
void do_LNEG(struct VMTHREAD* thread);
void do_FNEG(struct VMTHREAD* thread);
void do_DNEG(struct VMTHREAD* thread);
void do_ISHL(struct VMTHREAD* thread);
void do_LSHL(struct VMTHREAD* thread);
void do_ISHR(struct VMTHREAD* thread);
void do_LSHR(struct VMTHREAD* thread);
void do_IUSHR(struct VMTHREAD* thread);
void do_LUSHR(struct VMTHREAD* thread);
void do_IAND(struct VMTHREAD* thread);
void do_LAND(struct VMTHREAD* thread);
void do_IOR(struct VMTHREAD* thread);
void do_LOR(struct VMTHREAD* thread);
void do_IXOR(struct VMTHREAD* thread);
void do_LXOR(struct VMTHREAD* thread);
void do_IINC(struct VMTHREAD* thread);
void do_I2L(struct VMTHREAD* thread);
void do_I2F(struct VMTHREAD* thread);
void do_I2D(struct VMTHREAD* thread);
void do_L2I(struct VMTHREAD* thread);
void do_L2F(struct VMTHREAD* thread);
void do_L2D(struct VMTHREAD* thread);
void do_F2I(struct VMTHREAD* thread);
void do_F2L(struct VMTHREAD* thread);
void do_F2D(struct VMTHREAD* thread);
void do_D2I(struct VMTHREAD* thread);
void do_D2L(struct VMTHREAD* thread);
void do_D2F(struct VMTHREAD* thread);
void do_I2B(struct VMTHREAD* thread);
void do_I2C(struct VMTHREAD* thread);
void do_I2S(struct VMTHREAD* thread);
void do_LCMP(struct VMTHREAD* thread);
void do_FCMPL(struct VMTHREAD* thread);
void do_FCMPG(struct VMTHREAD* thread);
void do_DCMPL(struct VMTHREAD* thread);
void do_DCMPG(struct VMTHREAD* thread);
void do_IFEQ(struct VMTHREAD* thread);
void do_IFNE(struct VMTHREAD* thread);
void do_IFLT(struct VMTHREAD* thread);
void do_IFGE(struct VMTHREAD* thread);
void do_IFGT(struct VMTHREAD* thread);
void do_IFLE(struct VMTHREAD* thread);
void do_IF_ICMPEQ(struct VMTHREAD* thread);
void do_IF_ICMPNE(struct VMTHREAD* thread);
void do_IF_ICMPLT(struct VMTHREAD* thread);
void do_IF_ICMPGE(struct VMTHREAD* thread);
void do_IF_ICMPGT(struct VMTHREAD* thread);
void do_IF_ICMPLE(struct VMTHREAD* thread);
void do_IF_ACMPEQ(struct VMTHREAD* thread);
void do_IF_ACMPNE(struct VMTHREAD* thread);
void do_GOTO(struct VMTHREAD* thread);
void do_JSR(struct VMTHREAD* thread);
void do_RET(struct VMTHREAD* thread);
void do_TABLESWITCH(struct VMTHREAD* thread);
void do_LOOKUPSWITCH(struct VMTHREAD* thread);
void do_IRETURN(struct VMTHREAD* thread);
void do_LRETURN(struct VMTHREAD* thread);
void do_FRETURN(struct VMTHREAD* thread);
void do_DRETURN(struct VMTHREAD* thread);
void do_ARETURN(struct VMTHREAD* thread);
void do_RETURN(struct VMTHREAD* thread);
void do_GETSTATIC(struct VMTHREAD* thread);
void do_PUTSTATIC(struct VMTHREAD* thread);
void do_GETFIELD(struct VMTHREAD* thread);
void do_PUTFIELD(struct VMTHREAD* thread);
void do_INVOKEVIRTUAL(struct VMTHREAD* thread);
void do_INVOKESPECIAL(struct VMTHREAD* thread);
void do_INVOKESTATIC(struct VMTHREAD* thread);
void do_INVOKEINTERFACE(struct VMTHREAD* thread);
void do_RESERVED1(struct VMTHREAD* thread);
void do_NEW(struct VMTHREAD* thread);
void do_NEWARRAY(struct VMTHREAD* thread);
void do_ANEWARRAY(struct VMTHREAD* thread);
void do_ARRAYLENGTH(struct VMTHREAD* thread);
void do_ATHROW(struct VMTHREAD* thread);
void do_CHECKCAST(struct VMTHREAD* thread);
void do_INSTANCEOF(struct VMTHREAD* thread);
void do_MONITORENTER(struct VMTHREAD* thread);
void do_MONITOREXIT(struct VMTHREAD* thread);
void do_WIDE(struct VMTHREAD* thread);
void do_MULTIANEWARRAY(struct VMTHREAD* thread);
void do_IFNULL(struct VMTHREAD* thread);
void do_IFNONNULL(struct VMTHREAD* thread);
void do_GOTO_W(struct VMTHREAD* thread);
void do_JSR_W(struct VMTHREAD* thread);

/* Reserved opcodes(struct VMTHREAD* thread); */
void do_BREAKPOINT(struct VMTHREAD* thread);
void do_IMPDEP1(struct VMTHREAD* thread);
void do_IMPDEP2(struct VMTHREAD* thread);

#endif
