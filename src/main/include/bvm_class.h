/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_CLASS_H_
#define _XAM_CLASS_H_

#include <stdint.h>
#include "xam_types.h"
#include "xam_stack.h"

#define JAVAMAGIC 0xCAFEBABE
#define NULL 0

#define CONSTANTPOOL_CLASS              7
#define CONSTANTPOOL_FIELDREF           9
#define CONSTANTPOOL_METHODREF          10
#define CONSTANTPOOL_INTERFACEMETHODREF 11
#define CONSTANTPOOL_STRING             8
#define CONSTANTPOOL_INTEGER            3
#define CONSTANTPOOL_FLOAT              4
#define CONSTANTPOOL_LONG               5
#define CONSTANTPOOL_DOUBLE             6
#define CONSTANTPOOL_NAMEANDTYPE        12
#define CONSTANTPOOL_UTF8               1

struct VERSION
{
	uint16_t Major;
	uint16_t Minor;
};

struct CONSTANT_CLASS_INFO
{
	uint16_t NameIndex;
};

struct CONSTANT_REF_INFO
{
	uint16_t ClassIndex;
	uint16_t NameAndTypeIndex;
};

struct CONSTANT_STRING_INFO
{
	uint16_t StringIndex;
};

struct CONSTANT_FLOAT_INFO
{
	float Value;
};

struct CONSTANT_INTEGER_INFO
{
	int32_t Value;
};

struct CONSTANT_LONG_INFO
{
	int64_t Value;
};

struct CONSTANT_DOUBLE_INFO
{
	double Value;
};

struct CONSTANT_NAMETYPE_INFO
{
	uint16_t NameIndex;
	uint16_t DescriptorIndex;
};

struct CONSTANT_UTF8_INFO
{
	uint16_t Length;
	StringUTF8* Text;
};

struct CONSTANTPOOL
{
	uint8_t Tag;
	void* Data;	/* Pointer to a dynamically allocated structure. */
};


/*********************
 * ATTRIBUTE STRUCTS *
 *********************/

struct ATTRIBUTE_INFO
{
	uint16_t AttributeNameIndex;
	uint32_t AttributeLength;
	unsigned char* Info;
};

struct ATTRIBUTE_INFO_CONSTANTVALUE
{
	uint16_t AttributeNameIndex;
	uint32_t AttributeLength;
	uint16_t ConstantValueIndex;
};

struct EXCEPTIONTABLE_ENTRY
{
	uint16_t StartPC, EndPC;
	uint16_t HandlerPC;
	uint16_t CatchType;
};

struct ATTRIBUTE_INFO_CODE
{
	uint16_t AttributeNameIndex;
	uint32_t AttributeLength;
	uint16_t MaxStack;
	uint16_t MaxLocals;
	uint32_t CodeLength;
	unsigned char*  Code;
	uint16_t ExceptionTableLength;
	struct EXCEPTIONTABLE_ENTRY* ExceptionTable;
	uint16_t AttributesNum;
	struct ATTRIBUTE_INFO* Attributes;
};

struct ATTRIBUTE_INFO_EXCEPTION
{
	uint16_t  AttributeNameIndex;
	uint32_t  AttributeLength;
	uint16_t  ExceptionNum;
	uint16_t* ExceptionIndexTable;
};

struct ATTRIBUTE_INFO_INNERCLASS
{
	uint16_t AttributeNameIndex;
	uint32_t AttributeLength;
	uint16_t InnerClassesNum;
/* Inner classes table */
};

struct ATTRIBUTE_INFO_SYNTHETIC
{
	uint16_t AttributeNameIndex;
	uint32_t AttributeLength;     /* Must be zero. */
};

struct ATTRIBUTE_INFO_SOURCEFILE
{
	uint16_t AttributeNameIndex;
	uint32_t AttributeLength;
	uint16_t SourceFileIndex;     /* Index in the constant pool table. */
};

struct LINENUMBERTABLE_ENTRY
{
	uint16_t StartPC;
	uint16_t LineNumber;
};

struct ATTRIBUTE_INFO_LINENUMBERTABLE
{
	uint16_t AttributeNameIndex;
	uint32_t AttributeLength;
	uint16_t LineNumberTableLength;
	struct LINENUMBERTABLE_ENTRY* LineNumberTable;
};

struct LOCALVARIABLETABLE_ENTRY
{
	uint16_t StartPC;
	uint16_t Length;
	uint16_t NameIndex;
	uint16_t DescriptorIndex;
	uint16_t Index;
};

struct ATTRIBUTE_INFO_LOCALVARIABLETABLE
{
	uint16_t AttributeNameIndex;
	uint32_t AttributeLength;
	uint16_t LocalVariableTableLength;
	struct LOCALVARIABLETABLE_ENTRY* LocalVariableTable;
};

struct ATTRIBUTE_INFO_DEPRECATED
{
	uint16_t AttributeNameIndex;
	uint32_t AttributeLength;     /* Must be zero. */
};


/* INFO STRUCTS */

struct FIELD_INFO
{
	uint16_t AccessFlags;
	uint16_t NameIndex;
	uint16_t DescriptorIndex;
	uint16_t AttributesNum;
	struct ATTRIBUTE_INFO *Attributes;
};

/* Represents a Java class */
struct VMCLASS
{
	uint16_t                  AccessFlags;
	struct ATTRIBUTE_INFO*  Attributes;
	uint16_t                  AttributesNum;
	struct CONSTANTPOOL*    ConstantPool;       /* Is indexed from 1 to ConstantPoolNum-1 */
	uint16_t                  ConstantPoolNum;
	struct FIELD_INFO*      Fields;
	uint16_t                  FieldsNum;
	uint32_t                  InstanceCounter;    /* Counts the number of instances that use this class.
                                                 If that count is 0, the Garbage Collector can free this class.*/
	uint16_t*                 Interfaces;
	uint16_t                  InterfacesNum;
	uint16_t                  MainMethodIndex;    /* 0 means no method, >0 index in the Methods array. */
	struct METHOD_INFO*     Methods;
	uint16_t                  MethodsNum;
	const char*             QualifiedName;      /* Full qualified name */
	uint16_t                  SuperClassIndex;
	uint16_t                  ThisClassIndex;
	struct VERSION          Version;
};

#endif
