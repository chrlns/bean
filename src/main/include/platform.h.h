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

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

// The following byte order defines are GCC specific defines
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define bswp16(x) \
	x << 8 | x >> 8
#define bswp32(x) \
	bswp16(x) << 16 | bswp16(x)
#define bswp64(x) \
	bswp32(x) << 32 | bswp32(x)
#else
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define bswp16(x) (x)
#define bswp32(x) (x)
#define bswp64(x) (x)
#else
#error "Endianess not defined!"
#endif
#endif

#endif
