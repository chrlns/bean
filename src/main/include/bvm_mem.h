/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_MEM_H_
#define _XAM_MEM_H_

#ifdef NOGC

/* Use standard malloc */
#define xam_alloc(size) \
  malloc(size)
#define xam_realloc(ptr, newsize) \
  realloc(ptr, newsize);
#define xam_free(ptr) \
  free(ptr)

#else

#include <gc/gc.h>

/* Use macros of libgc */
#define xam_alloc(size) \
  GC_MALLOC(size)
#define xam_realloc(ptr, size) \
  GC_REALLOC(ptr, size)
#define xam_free(ptr)

#endif

#endif
