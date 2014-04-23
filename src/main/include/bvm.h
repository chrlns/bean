/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_H_
#define _XAM_H_

#ifndef DEBUG
#define NDEBUG
#define dbgmsg(msg)
#else
#define dbgmsg(msg) \
	printf("DEBUG: %s\n", msg);
#endif

#include "xam_method.h"
#include "xam_process.h"

/* These are the only stdc-lib includes */
#include <assert.h>     /* If NDEBUG is defined "assert" is ignored */
#include <stdio.h>
#include <stdlib.h>     /* Necessary for malloc, realloc, exit, etc. */
#include <string.h>     /* Necessary for strcmp() */
#include <stdint.h>	    /* Necessary for exact int types, e.g. int64_t */

bool isAccessFlag(struct METHOD_INFO* method, uint16_t accFlag);

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

struct MONITOR
{
  struct VMTHREAD* ThreadRef;
  void*            ObjectRef;

  struct MONITOR*  Next;
};

struct VM
{
  char*             ClassPath;
  char*             LibraryPath;

  bool              Initialized; /* Has the VM been initialized? */
  bool              Running;     /* Is the VM running? */

  struct VMCLASS**  PublicClasses;     /* Holds the Public Classes */
  struct VMTHREAD*  Threads;           /* Threads of this application. Thread[0] is
                                          the Main Thread. */
  unsigned char     ThreadNum;
  struct MONITOR*   Monitors;          /* Monitors */
  struct VMCLASS**  LocalClasses;      /* Pointer to the non public classes. */
  unsigned int      LocalClassesNum;   /* Number of local loaded classes. */

  unsigned int*     MemoryHeap;        /* Array of int (pointern) representing the
                                          GC-Heap of the application. */
  bool              DoCollectGarbage;  /* This is true if the Garbage Collector must
                                          be called. */
};                                     /* Nucleus can set this var = true before
                                          swapping or it lacks of memory. */

extern struct VM VM;
extern unsigned int   (*BufferToInt)(unsigned char[4]);
extern unsigned short (*BufferToShort)(unsigned char[2]);

unsigned int BufferToInt_LittleEndian(unsigned char[4]);
unsigned int BufferToInt_BigEndian(unsigned char[4]);
unsigned short BufferToShort_LittleEndian(unsigned char[2]);
unsigned short BufferToShort_BigEndian(unsigned char[2]);

char* compose_path(char* className, char* basePath);

uint8_t  Get1ByteOperand(struct stackframe_t*);
uint16_t Get2ByteOperand(struct stackframe_t*);
uint32_t  Get4ByteOperand(struct stackframe_t*);

#endif
