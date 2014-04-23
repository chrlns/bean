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

#include <xam.h>
#include <xam_io.h>
#include <xam_error.h>
#include <xam_mem.h>

bool ReadAttributeInfo(struct ATTRIBUTE_INFO *, IOHandle *);
bool ReadMethodInfo(struct VMCLASS *, IOHandle *, int, int);

bool LoadJavaClass(IOIdentifier file, struct VMCLASS *class)
{
    short n, m;
    int attributeCodeIndex = 0;
    int mainIndex = 0;
    unsigned char buffer1 = 0;
    unsigned char buffer2[2] = { 0, 0 };
    unsigned char buffer4[4] = { 0, 0, 0, 0 };
    uint64_t buffer8;
    IOHandle *classfile = NULL;

    classfile = IOOpen(file);

    /* Set init values */
    class->AccessFlags = 0x0000;

    if (classfile != NULL) {
#ifdef DEBUG
        printf("Class file opened.\n");
        printf("Class instance: 0x%p\n", (void *) class);
#endif

        /* Read Magic */
        IORead(buffer4, 4, classfile);
        if (buffer4[0] != 0xCA || buffer4[1] != 0xFE || buffer4[2] != 0xBA || buffer4[3] != 0xBE) {     /*
                                                                                                           printf("Class file has invalid magic! Read: %x %x %x %x\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]); */
            return RaiseException(ExceptionUnknown, "LoadJavaClass",
                                  __FILE__, __LINE__);
        }

        /* Read minor version */
        IORead(buffer2, 2, classfile);
        class->Version.Minor = BufferToShort(buffer2);

        /* Read major version */
        IORead(buffer2, 2, classfile);
        class->Version.Major = BufferToShort(buffer2);
#ifdef DEBUG
        printf("Class Version: %d.%d\n", class->Version.Major,
               class->Version.Minor);
#endif

        /* Read constant pool count */
        IORead(buffer2, 2, classfile);
        class->ConstantPoolNum = BufferToShort(buffer2);
#ifdef DEBUG
        printf("Constant pool count: %d\n", class->ConstantPoolNum);
#endif

        /* Allocate memory for constant pool */
        class->ConstantPool =
            (struct CONSTANTPOOL *) xam_alloc(class->ConstantPoolNum *
                                              sizeof(struct CONSTANTPOOL));

        /* Read constants from pool */
        for (n = 1; n < class->ConstantPoolNum; n++) {
            IORead(&buffer1, 1, classfile);
            class->ConstantPool[n - 1].Tag = buffer1;

#ifdef DEBUG
            printf("%d: Constant Type %d\t", n, buffer1);
#endif

            switch (class->ConstantPool[n - 1].Tag) {
            case CONSTANTPOOL_FIELDREF:
                {
                    /* Allocating memory for REF_INFO */
                    class->ConstantPool[n - 1].Data =
                        xam_alloc(sizeof(struct CONSTANT_REF_INFO));

                    /* Read class index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_REF_INFO *)
                     class->ConstantPool[n - 1].Data)->ClassIndex =
BufferToShort(buffer2);

                    /* Read name and type index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_REF_INFO *) class->ConstantPool[n -
                                                                      1].
                     Data)->NameAndTypeIndex = BufferToShort(buffer2);
#ifdef DEBUG
                    printf("CONSTANTPOOL_FIELDREF.\n");
#endif
                    break;
                }
            case CONSTANTPOOL_CLASS:
                {
                    /* Allocating memory for CLASS_INFO */
                    class->ConstantPool[n - 1].Data =
                        xam_alloc(sizeof(struct CONSTANT_CLASS_INFO));

                    /* Read name index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_CLASS_INFO *)
                     class->ConstantPool[n - 1].Data)->NameIndex =
BufferToShort(buffer2);

#ifdef DEBUG
                    printf
                        ("CONSTANTPOOL_CLASS (NameIndex=%d) read.\n",
                         ((struct CONSTANT_CLASS_INFO *)
                          class->ConstantPool[n - 1].Data)->NameIndex);
#endif
                    break;
                }
            case CONSTANTPOOL_METHODREF:
                {
                    /* Allocating memory for REF_INFO */
                    class->ConstantPool[n - 1].Data =
                        xam_alloc(sizeof(struct CONSTANT_REF_INFO));

                    /* Read class index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_REF_INFO *)
                     class->ConstantPool[n - 1].Data)->ClassIndex =
BufferToShort(buffer2);

                    /* Read name and type index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_REF_INFO *) class->ConstantPool[n -
                                                                      1].
                     Data)->NameAndTypeIndex = BufferToShort(buffer2);

#ifdef DEBUG
                    printf("CONSTANTPOOL_METHODREF.\n");
#endif
                    break;
                }
            case CONSTANTPOOL_INTERFACEMETHODREF:
                {
                    /* Allocating memory for REF_INFO */
                    class->ConstantPool[n - 1].Data =
                        xam_alloc(sizeof(struct CONSTANT_REF_INFO));

                    /* Read class index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_REF_INFO *)
                     class->ConstantPool[n - 1].Data)->ClassIndex =
BufferToShort(buffer2);

                    /* Read name and type index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_REF_INFO *) class->ConstantPool[n -
                                                                      1].
                     Data)->NameAndTypeIndex = BufferToShort(buffer2);

#ifdef DEBUG
                    printf("CONSTANTPOOL_INTERFACEMETHODREF.\n");
#endif
                    break;
                }
            case CONSTANTPOOL_STRING:
                {
                    /* Allocating memory for STRING_INFO */
                    class->ConstantPool[n - 1].Data =
                        xam_alloc(sizeof(struct CONSTANT_STRING_INFO));

                    /* Read string index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_STRING_INFO *)
                     class->ConstantPool[n - 1].Data)->StringIndex =
BufferToShort(buffer2);

#ifdef DEBUG
                    printf("CONSTANTPOOL_STRING.\n");
#endif
                    break;
                }
            case CONSTANTPOOL_INTEGER:
                {
                    class->ConstantPool[n - 1].Data =
                        xam_alloc(sizeof(struct CONSTANT_INTEGER_INFO));

                    /* Read integer */
                    IORead(buffer4, 4, classfile);
                    ((struct CONSTANT_INTEGER_INFO *)
                     class->ConstantPool[n - 1].Data)->Value =
BufferToInt(buffer4);

#ifdef DEBUG
                    printf("CONSTANTPOOL_INTEGER.\n");
#endif
                    break;
                }
            case CONSTANTPOOL_FLOAT:
                {
                    class->ConstantPool[n - 1].Data =
                        malloc(sizeof(struct CONSTANT_FLOAT_INFO));

                    /* Read float */
                    IORead(buffer4, 4, classfile);
                    ((struct CONSTANT_FLOAT_INFO *)
                     class->ConstantPool[n - 1].Data)->Value =
(float) BufferToInt(buffer4);

#ifdef DEBUG
                    printf("CONSTANTPOOL_FLOAT.\n");
#endif
                    break;
                }
            case CONSTANTPOOL_LONG:
                {
                    class->ConstantPool[n - 1].Data =
                        malloc(sizeof(struct CONSTANT_LONG_INFO));
                    IORead((void *) &buffer8, 8, classfile);
                    buffer8 = bswp64(buffer8);
                    ((struct CONSTANT_LONG_INFO *)
                     class->ConstantPool[n - 1].Data)->Value = buffer8;
                    dbgmsg("CONSTANTPOOL_LONG");
                    break;
                }
            case CONSTANTPOOL_DOUBLE:
                {
                    class->ConstantPool[n - 1].Data =
                        malloc(sizeof(struct CONSTANT_DOUBLE_INFO));
/*
                    IORead(buffer4, 4, classfile);
                    ((struct CONSTANT_DOUBLE_INFO*)class->ConstantPool[n-1].Data)->Value.HighValue = (float)BufferToInt(buffer4);
                    IORead(buffer4, 4, classfile);
                    ((struct CONSTANT_DOUBLE_INFO*)class->ConstantPool[n-1].Data)->Value.LowValue = (float)BufferToInt(buffer4);
*/
#ifdef DEBUG
                    printf("CONSTANTPOOL_DOUBLE.\n");
#endif
                    break;
                }
            case CONSTANTPOOL_NAMEANDTYPE:
                {
                    /* Allocating memory for NAMEANDTYPE_INFO */
                    class->ConstantPool[n - 1].Data =
                        xam_alloc(sizeof(struct CONSTANT_NAMETYPE_INFO));

                    /* Read name index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_NAMETYPE_INFO *)
                     class->ConstantPool[n -
                                         1].Data)->NameIndex =
                        BufferToShort(buffer2);

                    /* Read descriptor index */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_NAMETYPE_INFO *)
                     class->ConstantPool[n -
                                         1].Data)->DescriptorIndex =
                        BufferToShort(buffer2);

#ifdef DEBUG
                    printf("CONSTANTPOOL_NAMETYPE.\n");
#endif
                    break;
                }
            case CONSTANTPOOL_UTF8:
                {
                    /* Allocating memory for UTF8_INFO */
                    class->ConstantPool[n - 1].Data =
                        malloc(sizeof(struct CONSTANT_UTF8_INFO));

                    /* Read length */
                    IORead(buffer2, 2, classfile);
                    ((struct CONSTANT_UTF8_INFO *)
                     class->ConstantPool[n - 1].Data)->Length =
BufferToShort(buffer2);

                    /* Allocating memory for string */
                    ((struct CONSTANT_UTF8_INFO *)
                     class->ConstantPool[n - 1].Data)->Text = (char *)
                        xam_alloc(((struct CONSTANT_UTF8_INFO *) class->
                                   ConstantPool[n -
                                                1].Data)->Length *
                                  sizeof(char) + 1);

                    /* Read string */
                    IORead((unsigned char *) ((struct CONSTANT_UTF8_INFO *)
                                              class->ConstantPool[n -
                                                                  1].Data)->
                           Text, ((struct CONSTANT_UTF8_INFO *)
                                  class->ConstantPool[n - 1].Data)->Length,
                           classfile);

                    /* Terminating zero character */
                    ((struct CONSTANT_UTF8_INFO *) class->ConstantPool[n -
                                                                       1].
                     Data)->Text[((struct CONSTANT_UTF8_INFO *) class->
                                  ConstantPool[n - 1].Data)->Length] = 0;

#ifdef DEBUG
                    printf
                        ("CONSTANTPOOL_UTF8 -> %s (%d/%d)\n",
                         ((struct CONSTANT_UTF8_INFO *)
                          class->ConstantPool[n -
                                              1].Data)->Text,
                         ((struct CONSTANT_UTF8_INFO *)
                          class->ConstantPool[n -
                                              1].Data)->Length, buffer1);
#endif

                    /* Check for default attribute names */
                    if (strcmp(((struct CONSTANT_UTF8_INFO *)
                                class->ConstantPool[n -
                                                    1].Data)->Text,
                               "Code") == 0) {
                        attributeCodeIndex = n;
                    }

                    break;
                }
            default:
                {
                    printf("Unknown constant type: %d!\n",
                           class->ConstantPool[n - 1].Tag);
                    IOClose(classfile);
                    return false;
                }
            }
        }

        /* Read access flags */
        IORead(buffer2, 2, classfile);
        class->AccessFlags = BufferToShort(buffer2);

        /* Read this class index */
        IORead(buffer2, 2, classfile);
        class->ThisClassIndex = BufferToShort(buffer2);

        /* Read super class index */
        IORead(buffer2, 2, classfile);
        class->SuperClassIndex = BufferToShort(buffer2);

        /* Read interface count */
        IORead(buffer2, 2, classfile);
        class->InterfacesNum = BufferToShort(buffer2);

        /* Read interface indices */
        class->Interfaces =
            (unsigned short *) xam_alloc(sizeof(unsigned short) *
                                         class->InterfacesNum);
        for (n = 0; n < class->InterfacesNum; n++) {
            IORead(buffer2, 2, classfile);
            class->Interfaces[n] = BufferToShort(buffer2);
        }

        /* Read fields count */
        IORead(buffer2, 2, classfile);
        class->FieldsNum = BufferToShort(buffer2);

        /* Read fields */
        class->Fields =
            (struct FIELD_INFO *) xam_alloc(sizeof(struct FIELD_INFO) *
                                            class->FieldsNum);
        for (n = 0; n < class->FieldsNum; n++) {
            /* Read access flags */
            IORead(buffer2, 2, classfile);
            class->Fields[n].AccessFlags = BufferToShort(buffer2);

            /* Read name index */
            IORead(buffer2, 2, classfile);
            class->Fields[n].NameIndex = BufferToShort(buffer2);

            /* Read descriptor index */
            IORead(buffer2, 2, classfile);
            class->Fields[n].DescriptorIndex = BufferToShort(buffer2);

            /* Read attributes count */
            IORead(buffer2, 2, classfile);
            class->Fields[n].AttributesNum = BufferToShort(buffer2);

            /* Read attributes */
            class->Fields[n].Attributes = (struct ATTRIBUTE_INFO *)
                xam_alloc(sizeof(struct ATTRIBUTE_INFO) *
                          class->Fields[n].AttributesNum);
            for (m = 0; m < class->Fields[n].AttributesNum; m++) {
                /* Read attribute name index */
                IORead(buffer2, 2, classfile);
                class->Fields[n].Attributes[m].AttributeNameIndex =
                    BufferToShort(buffer2);

                /* Read length of info array */
                IORead(buffer4, 4, classfile);
                class->Fields[n].Attributes[m].AttributeLength =
                    BufferToInt(buffer4);

                /* Allocate space for infos */
                class->Fields[n].Attributes[m].Info =
                    (unsigned char *) xam_alloc(class->
                                                Fields[n].Attributes
                                                [m].AttributeLength);
                IORead(class->Fields[n].Attributes[m].Info,
                       class->Fields[n].Attributes[m].AttributeLength,
                       classfile);
            }
        }

        /* Read methods */
        ReadMethodInfo(class, classfile, mainIndex, attributeCodeIndex);

        /* Read attributes count */
        IORead(buffer2, 2, classfile);
        class->AttributesNum = BufferToShort(buffer2);

        /* Read attributes */
        class->Attributes = (struct ATTRIBUTE_INFO *)
            xam_alloc(sizeof(struct ATTRIBUTE_INFO) *
                      class->AttributesNum);
        for (m = 0; m < class->AttributesNum; m++) {
            /* Read attribute name index */
            IORead(buffer2, 2, classfile);
            class->Attributes[m].AttributeNameIndex =
                BufferToShort(buffer2);

            /* Read length of info array */
            IORead(buffer4, 4, classfile);
            class->Attributes[m].AttributeLength = BufferToInt(buffer4);

            /* Allocate space for infos */
            class->Attributes[m].Info = (unsigned char *)
                xam_alloc(sizeof(struct ATTRIBUTE_INFO) *
                          class->Attributes[m].AttributeLength);
            IORead(class->Attributes[m].Info,
                   class->Attributes[m].AttributeLength, classfile);
        }
    } else {
#ifdef DEBUG
        printf("IO-Error: %s %p\n", file.filename,
               (void *) file.filebuffer);
#endif
        return RaiseException(ExceptionIO, "LoadJavaClass", __FILE__,
                              __LINE__);
    }

    if (IOEnd(classfile) == false) {
        printf("Class not wellformed: unused data at end of file!\n");
        return false;
    }

    IOClose(classfile);

    return true;
}

bool ReadAttributeInfo(struct ATTRIBUTE_INFO * attributeInfo,
                       IOHandle * classfile)
{
    unsigned char buffer2[2];
    unsigned char buffer4[4];

#ifdef DEBUG
    printf("Begin reading ATTRIBUTE_INFO...\n");
#endif

    /* Read attribute name index */
    if (IORead(buffer2, 2, classfile) == 2) {
        attributeInfo->AttributeNameIndex = BufferToShort(buffer2);
    } else {
#ifdef DEBUG
        printf("Read of ATTRIBUTE_INFO.AttributeNameIndex failed!\n");
#endif
        return false;
    }

    /* Read length of info array */
    if (IORead(buffer4, 4, classfile) == 4) {
        attributeInfo->AttributeLength = BufferToInt(buffer4);
    } else {
#ifdef DEBUG
        printf("Read ATTRIBUTE_INFO.AttributeLength!\n");
#endif
        return false;
    }

    /* Allocate space for infos */
    attributeInfo->Info =
        (unsigned char *) xam_alloc(sizeof(unsigned char) *
                                    attributeInfo->AttributeLength);

    if (attributeInfo->Info == NULL) {
        return false;
    }

    if (IORead
        (attributeInfo->Info, attributeInfo->AttributeLength,
         classfile) != attributeInfo->AttributeLength) {
#ifdef DEBUG
        printf("Read of ATTRIBUTE_INFO failed!\n");
#endif
        return false;
    }
#ifdef DEBUG
    printf("Read of ATTRIBUTE_INFO succeeded!\n");
#endif

    return true;
}

bool ReadMethodInfo(struct VMCLASS * vmclass, IOHandle * classfile,
                    int mainIndex, int attributeCodeIndex)
{
    register short n, m, i;
    unsigned char buffer2[2];

    dbgmsg("Begin reading METHOD_INFO...\n");

    /* Read methods count */
    if (IORead(buffer2, 2, classfile) == 2) {
        vmclass->MethodsNum = BufferToShort(buffer2);
    } else {
        return false;
    }

    /* Read methods */
    vmclass->Methods =
        (struct METHOD_INFO *) xam_alloc(sizeof(struct METHOD_INFO) *
                                         vmclass->MethodsNum);

    if (vmclass->Methods == NULL) {
        return false;
    }

    for (n = 0; n < vmclass->MethodsNum; n++) {
        /* Read access flags */
        IORead(buffer2, 2, classfile);
        vmclass->Methods[n].AccessFlags = BufferToShort(buffer2);

        /* Read name index */
        IORead(buffer2, 2, classfile);
        vmclass->Methods[n].NameIndex = BufferToShort(buffer2);
        if (vmclass->Methods[n].NameIndex == mainIndex)
            vmclass->MainMethodIndex = n + 1;

        /* Read descriptor index */
        IORead(buffer2, 2, classfile);
        vmclass->Methods[n].DescriptorIndex = BufferToShort(buffer2);

        /* Read attributes count */
        IORead(buffer2, 2, classfile);
        vmclass->Methods[n].AttributesNum = BufferToShort(buffer2);

        /* Read attributes */
        vmclass->Methods[n].Attributes = (struct ATTRIBUTE_INFO *)
            xam_alloc(sizeof(struct ATTRIBUTE_INFO) *
                      vmclass->Methods[n].AttributesNum);

        for (m = 0; m < vmclass->Methods[n].AttributesNum; m++) {
            /* Read standard attribute */
            ReadAttributeInfo(vmclass->Methods[n].Attributes + m,
                              classfile);

            /* Check for special attributes */
            if (vmclass->Methods[n].Attributes[m].AttributeNameIndex ==
                attributeCodeIndex) {
                dbgmsg("Code Info detected\n");

                vmclass->Methods[n].CodeInfo =
                    (struct ATTRIBUTE_INFO_CODE *)
                    xam_alloc(sizeof(struct ATTRIBUTE_INFO_CODE));
                vmclass->Methods[n].CodeInfo->AttributeNameIndex =
                    attributeCodeIndex;

                /* Attribute Length */
                vmclass->Methods[n].CodeInfo->AttributeLength
                    = vmclass->Methods[n].Attributes[m].AttributeLength;

                /* Read Max Stack (2 Byte) */
                vmclass->Methods[n].StackFrameRef.operandStackSize =
                    BufferToShort(vmclass->Methods[n].Attributes[m].Info +
                                  0);

                /* Allocate operand stack */
                /*vmclass->Methods[n].StackFrameRef.OperandStack
                   = (struct OperandStackFrame*)xam_alloc(sizeof(struct OperandStackFrame) * vmclass->Methods[n].StackFrameRef.OperandStackSize);
                 */
                /* Read Max Locals (2 Byte) */
                vmclass->Methods[n].StackFrameRef.localVarsLen
                    =
                    BufferToShort(vmclass->Methods[n].Attributes[m].Info +
                                  2);
                /* Where is StackFrameRef.localVars initialized?
                 * Does it make sense to store the localVarsLen in a stackframe?
                 * */

                /* Read Code Length (4 Byte) */
                vmclass->Methods[n].CodeInfo->CodeLength
                    =
                    BufferToInt(vmclass->Methods[n].Attributes[m].Info +
                                4);
#ifdef DEBUG
                printf("Code Length %d\n",
                       vmclass->Methods[n].CodeInfo->CodeLength);
#endif

                /* Code */
                vmclass->Methods[n].CodeInfo->Code =
                    xam_alloc(sizeof(unsigned char) *
                              vmclass->Methods[n].CodeInfo->CodeLength);
                for (i = 0;
                     i <
                     (int) vmclass->Methods[n].CodeInfo->CodeLength; i++)
                    vmclass->Methods[n].CodeInfo->Code[i] =
                        *(vmclass->Methods[n].Attributes[m].Info + 8 + i);

                /* Exception Table Length (2 Byte) */
                vmclass->Methods[n].CodeInfo->ExceptionTableLength =
                    BufferToShort(vmclass->Methods[n].Attributes[m].Info +
                                  8 +
                                  vmclass->Methods[n].
                                  CodeInfo->CodeLength);
#ifdef DEBUG
                printf("Exception Table Length: %d\n",
                       vmclass->Methods[n].CodeInfo->ExceptionTableLength);
#endif

                /* Exception Table */

                /* Attributes Num */
                vmclass->Methods[n].CodeInfo->AttributesNum
                    =
                    BufferToShort(vmclass->Methods[n].Attributes[m].Info +
                                  10 +
                                  vmclass->Methods[n].
                                  CodeInfo->CodeLength +
                                  vmclass->Methods[n].
                                  CodeInfo->ExceptionTableLength * 8);
#ifdef DEBUG
                printf("AttributesNum: %d\n",
                       vmclass->Methods[n].CodeInfo->AttributesNum);
#endif

                /* Attribute Infos */
                vmclass->Methods[n].CodeInfo->Attributes
                    = (struct ATTRIBUTE_INFO *)
                    xam_alloc(sizeof(struct ATTRIBUTE_INFO) *
                              vmclass->Methods[n].CodeInfo->AttributesNum);
            }
        }
    }

    /* Set full qualified name */
    vmclass->QualifiedName = "";

    return true;
}

int XamPreloadClass(void *mempointer, int memsize,
                    const char *fullQualifiedName)
{
    IOIdentifier file;
    file.filebuffer = (unsigned char *) mempointer;
    file.filebuffer_len = memsize;
    file.filename = NULL;

    /* Create class struct */
    VM.LocalClassesNum++;
    VM.LocalClasses =
        (struct VMCLASS **) xam_realloc(VM.LocalClasses,
                                        sizeof(struct VMCLASS *) *
                                        VM.LocalClassesNum);

    if (LoadJavaClass(file, VM.LocalClasses[VM.LocalClassesNum - 1]) ==
        false) {
        return false;
    } else {
        VM.LocalClasses[VM.LocalClassesNum - 1]->QualifiedName =
            fullQualifiedName;
    }

#ifdef DEBUG
    printf("Class %s preloaded.\n",
           VM.LocalClasses[VM.LocalClassesNum - 1]->QualifiedName);
#endif

    return true;
}
