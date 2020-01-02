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

#ifndef _CLASS_H_
#define _CLASS_H_

#include <stdint.h>
#include <stdio.h>
#include <types.h>

#include <method.h>
#include <classfile.h>

typedef struct Class {
    uint16_t                AccessFlags;
    struct ATTRIBUTE_INFO*  Attributes;
    uint16_t                AttributesNum;
    struct CONSTANTPOOL*    ConstantPool;       // Is indexed from 1 to ConstantPoolNum-1
    uint16_t                ConstantPoolNum;
    struct FIELD_INFO*      Fields;
    uint16_t                FieldsNum;
    uint32_t                InstanceCounter;    // Counts the number of instances that use this class.
                                                // If that count is 0, the Garbage Collector can free this class.
    uint16_t*               Interfaces;
    uint16_t                InterfacesNum;
    uint16_t                MainMethodIndex;    // 0 means no method, >0 index in the Methods array.
    Method*   Methods;
    uint16_t                MethodsNum;
    const char*             QualifiedName;      // Full qualified name
    uint16_t                SuperClassIndex;
    uint16_t                ThisClassIndex;
    struct VERSION          Version;
} Class;

#endif