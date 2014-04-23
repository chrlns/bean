/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_IO_H_
#define _XAM_IO_H_

#include "xam_error.h"

// __LITTLE_ENDIAN__ must be provided by the compiler
#ifdef __LITTLE_ENDIAN__ 
#define bswp16(x) \
	x << 8 | x >> 8
#define bswp32(x) \
	bswp16(x) << 16 | bswp16(x)
#define bswp64(x) \
	bswp32(x) << 32 | bswp32(x) 
#else
#ifdef __BIG_ENDIAN__
#define bswp16(x) (x)
#define bswp32(x) (x)
#define bswp64(x) (x)
#else
#error "Endianess not defined!"
#endif
#endif

typedef struct
{
  bool           Allocated;
  unsigned char* Buffer;
  unsigned int   Length;
  unsigned int   Pointer;
} IOHandle;

typedef struct
{
  char*           filename;
  unsigned char*  filebuffer;
  unsigned int    filebuffer_len;
} IOIdentifier;

void      IOClose(IOHandle* io);
bool      IOEnd(IOHandle* io);
IOHandle* IOOpen(IOIdentifier id);
int       IORead(unsigned char* buffer, int count, IOHandle* io);

#endif
