/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
 
#define NULL 0
 
#ifndef STRUCT_METHOD_INFO
#define STRUCT_METHOD_INFO 

#include <stdint.h>
#include "xam_class.h"
#include "xam_stack.h"

/* A method, but without running information */
struct METHOD_INFO
{
	uint16_t AccessFlags;
	uint16_t NameIndex;
	uint16_t DescriptorIndex;
	uint16_t AttributesNum;
	struct ATTRIBUTE_INFO*      Attributes;
	struct ATTRIBUTE_INFO_CODE* CodeInfo;   /* Pointer to the Code Attribute */
	struct stackframe_t StackFrameRef;      /* Original stack frame */
};
#endif

#ifndef STRUCT_METHOD
#define STRUCT_METHOD

#include "xam_class.h"
#include "xam_stack.h"

/* Identifies a running method (method "instance", old: METHOD_FQID) */
struct METHOD
{
	struct VMCLASS*     Class;    /* Pointer to a class */
	struct STACKFRAME*  Frame;    /* Pointer to a StackFrame-copy of this method */
	struct METHOD_INFO* Method;   /* Pointer to the METHOD_INFO that describes this method */
};
#endif
