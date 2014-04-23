/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Get static field from class */
void do_GETSTATIC(struct VMTHREAD *thread)
{
    struct CONSTANT_CLASS_INFO *classInfo = NULL;
    struct CONSTANTPOOL *constant = NULL;
    struct CONSTANT_NAMETYPE_INFO *nameTypeInfo = NULL;
    struct CONSTANT_REF_INFO *refInfo = NULL;
    uint16_t operand = 0;

    assert(thread != NULL);
    assert(thread->RunningClass != NULL);
    assert(thread->RunningClass->ConstantPool != NULL);

    operand = Get2ByteOperand(current_frame(thread));

    dbgmsg("GETSTATIC");

    constant = (struct CONSTANTPOOL *)
        &(thread->RunningClass->ConstantPool[operand - 1]);

    assert(constant != NULL);
    assert(constant->Tag == CONSTANTPOOL_FIELDREF);
    assert(constant->Data != NULL);

    refInfo = (struct CONSTANT_REF_INFO *) constant->Data;
    classInfo = (struct CONSTANT_CLASS_INFO *)
        thread->RunningClass->ConstantPool[refInfo->ClassIndex - 1].Data;
    nameTypeInfo = (struct CONSTANT_NAMETYPE_INFO *)
        thread->RunningClass->ConstantPool[refInfo->NameAndTypeIndex -
                                           1].Data;
}
