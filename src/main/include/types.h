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

#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>

#define JAVATYPE_REFERENCE  0x00
#define JAVATYPE_RETADDR    0x01
#define JAVATYPE_LONG       0x02
#define JAVATYPE_INT        0x03
#define JAVATYPE_BYTE       0x04

typedef unsigned char   bool;
typedef int32_t           Boolean;    /* Java Type Boolean */
typedef char   StringUTF8;
typedef short  StringUTF16;

union __varframe_data
{
	Boolean BooleanValue;
	uint8_t   ByteValue;
	float FloatValue;
	int16_t   SignedInt16Value;
	int32_t   SignedInt32Value;
	uint32_t  UnsignedInt32Value;
	void* ptr;
};

/* Frame for references on the operand stack frame */
typedef struct
{
	uint8_t type;
	union __varframe_data data;
} VarFrame;

#endif
