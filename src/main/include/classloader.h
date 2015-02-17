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

#ifndef _CLASSLOADER_H_
#define _CLASSLOADER_H_

#include <stdint.h>
#include <stdio.h>

#include <class.h>
#include <types.h>

/* Represents a Java object */
typedef struct {
    Class*    class;
    Varframe* fields;
    uint16_t  fields_num;
} Object;

bool load_class_file(FILE* classfile, Class* clazz);

typedef struct Classloader {
    Class* loaded_classes;
    int    loaded_classes_num;
} Classloader;

Classloader* Classloader_new(void);
void Classloader_destroy(Classloader* cl);

Class* Class_new(void);

#endif
