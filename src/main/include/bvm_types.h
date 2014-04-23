/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_TYPES_H_
#define _XAM_TYPES_H_

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
struct varframe_t
{
	uint8_t type;
	union __varframe_data data;
};

#endif
