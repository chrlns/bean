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

#ifndef _XAM_MEM_H_
#define _XAM_MEM_H_

#define NOGC // FIXME Use a Garbage Collector
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
