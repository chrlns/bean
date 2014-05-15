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

#ifndef _CLASSLOADER_H_
#define _CLASSLOADER_H_

#include <stdint.h>
#include <stdio.h>
#include "bvm_types.h"
#include "bvm_stack.h"

#define JAVAMAGIC 0xCAFEBABE

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
    void* Data; /* Pointer to a dynamically allocated structure. */
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

struct vmobject_t {
    struct VMCLASS*    class;
    struct varframe_t* fields;
    uint16_t           fields_num;
};

bool load_class_file(FILE* classfile, struct VMCLASS* class);

typedef struct Classloader {
    Class* loaded_classes;
    int    loaded_classes_num;
};

Classloader* Classloader_new(void);
void Classloader_destroy(Classloader* cl);

#endif
