/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>
#include <xam_link.h>

bool IsNative(struct VMTHREAD * thread, unsigned short methodIndex,
              struct LINKFLAGS * flags)
{
    unsigned short classIndex, classNameIndex, nameTypeIndex,
        methodNameIndex;
    StringUTF8 *className;
    StringUTF8 *methodName;
    struct VMCLASS *vmclass = thread->RunningClass;
    struct OperandStackFrame *value0;
    struct OperandStackFrame *value1;

    /* The Constant Pool Index is indexed beginning with 1 not 0... */
    methodIndex--;

    classIndex =
        ((struct CONSTANT_REF_INFO *) vmclass->
         ConstantPool[methodIndex].Data)->ClassIndex - 1;
    classNameIndex =
        ((struct CONSTANT_CLASS_INFO *) vmclass->
         ConstantPool[classIndex].Data)->NameIndex - 1;
    className =
        ((struct CONSTANT_UTF8_INFO
          *) (vmclass->ConstantPool[classNameIndex].Data))->Text;

    nameTypeIndex =
        ((struct CONSTANT_REF_INFO *) vmclass->
         ConstantPool[methodIndex].Data)->NameAndTypeIndex - 1;
    methodNameIndex =
        ((struct CONSTANT_NAMETYPE_INFO *)
         vmclass->ConstantPool[nameTypeIndex].Data)->NameIndex - 1;
    methodName =
        ((struct CONSTANT_UTF8_INFO *)
         vmclass->ConstantPool[methodNameIndex].Data)->Text;
/*
  // Check for println method
  if(strcmp(methodName, "println") == 0)
  {
    flags->IsNative    = true;
    flags->AbortInvoke = true;

    value0 = OperandStackPop(&thread->Stack);

    printf("%s\n", ((struct CONSTANT_UTF8_INFO*)thread->RunningClass->ConstantPool[((struct CONSTANT_STRING_INFO*)value0.UnsignedInt)->StringIndex - 1].Data)->Text);

    return true;
  }*/

    /* Check for build-in Java methods */
    if (strcmp(className, "Xerxys/Native/Java") == 0) {
        return false;
    }

    /* Check for methods of the nativ interface */
    if (strcmp(className, "Xerxys/Native/x86") == 0) {
        if (strcmp(methodName, "callNucleus") == 0) {
            flags->IsNative = true;
            flags->AbortInvoke = true;
            value0 = NULL;
            value1 = NULL;
/*   TODO   stack_pop(&thread->operandStack, &value1);
      stack_pop(&thread->operandStack, &value0);*/

            /*   printf("CALL NUCLEUS: %s with %s\n",
               ((struct CONSTANT_UTF8_INFO*)thread->RunningClass->
               ConstantPool[((struct CONSTANT_STRING_INFO*)value0.
               Value.UnsignedInt)->StringIndex - 1].Data)->Text,
               ((struct CONSTANT_UTF8_INFO*)thread->RunningClass->ConstantPool[
               ((struct CONSTANT_STRING_INFO*)value1.Value.UnsignedInt)->StringIndex - 1]
               .Data)->Text);
             */
            return true;
        }
    }

    return false;
}
