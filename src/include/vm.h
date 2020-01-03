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

#ifndef _VM_H_
#define _VM_H_

#include <assert.h>     /* If NDEBUG is defined "assert" is ignored */
#include <stdio.h>
#include <stdlib.h>     /* Necessary for malloc, realloc, exit, etc. */
#include <string.h>     /* Necessary for strcmp() */
#include <stdint.h>     /* Necessary for exact int types, e.g. int64_t */

#include <thread.h>
#include <class.h>
#include <stackframe.h>
#include <classloader.h>
#include <linker.h>

#define isAccessFlag(method, accFlag) \
    (method->AccessFlags & accFlag) == accFlag

#define true  1
#define false 0

/* Method Access Flags */
#define ACC_PUBLIC        0x0001
#define ACC_PRIVATE       0x0002
#define ACC_PROTECTED     0x0004
#define ACC_STATIC        0x0008
#define ACC_FINAL         0x0010
#define ACC_SYNCHRONIZED  0x0020
#define ACC_NATIVE        0x0100
#define ACC_ABSTRACT      0x0400
#define ACC_STRICT        0x0800

/* Define some (more or less posix compatible) signals */
#define SIGQUIT   3   /* Program should be exit its execution */
#define SIGKILL   9   /* Program is being terminated in short */
#define SIGCMPCT  66  /* Program should call Garbage Collector to compact. */

struct MONITOR {
    Thread* ThreadRef;
    void* ObjectRef;

    struct MONITOR* Next;
};

typedef struct VM {
    bool alive;
    Classloader* classloader;
    char* classpath;

    bool Initialized; /* Has the VM been initialized? */

    Class** PublicClasses; /* Holds the Public Classes */
    Thread* Threads; /* Threads of this application. Thread[0] is
                                          the Main Thread. */
    unsigned char ThreadNum;
    struct MONITOR* Monitors; /* Monitors */

    unsigned int* MemoryHeap; /* Array of int (pointern) representing the
                                          GC-Heap of the application. */
    bool DoCollectGarbage; /* This is true if the Garbage Collector must
                                          be called. */
} VM;

unsigned int BufferToInt(unsigned char[4]);
unsigned short BufferToShort(unsigned char[2]);

char* compose_path(char* className, char* basePath);

uint8_t Get1ByteOperand(Stackframe*);
uint16_t Get2ByteOperand(Stackframe*);
uint32_t Get4ByteOperand(Stackframe*);

#endif
