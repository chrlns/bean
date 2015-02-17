/*
 *  Bean Java VM
 *  Copyright (C) 2005-2015 Christian Lins <christian@lins.me>
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

#include <debug.h>
#include <platform.h>
#include <vm.h>

bool ReadAttributeInfo(struct ATTRIBUTE_INFO *, FILE*);
bool ReadMethodInfo(Class *, FILE*, int, int);

bool load_class_file(FILE* classfile, Class *class)
{
    short n, m;
    int attributeCodeIndex = 0;
    int mainIndex = 0;
    unsigned char buffer1 = 0;
    unsigned char buffer2[2] = { 0, 0 };
    unsigned char buffer4[4] = { 0, 0, 0, 0 };
    uint64_t buffer8;

    /* Set init values */
    class->AccessFlags = 0x0000;

    if (classfile != NULL) {
#ifdef DEBUG
        printf("Class file opened.\n");
        printf("Class instance: 0x%p\n", (void *) class);
#endif

        /* Read Magic */
        fread(buffer4, 1, 4, classfile);
        if (buffer4[0] != 0xCA || buffer4[1] != 0xFE || buffer4[2] != 0xBA || buffer4[3] != 0xBE) {
#ifdef DEBUG
            printf("Class file has invalid magic! Read: %x %x %x %x\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
#endif
            return false;
        }

        /* Read minor version */
        fread(buffer2, 1, 2, classfile);
        class->Version.Minor = BufferToShort(buffer2);

        /* Read major version */
        fread(buffer2, 1, 2, classfile);
        class->Version.Major = BufferToShort(buffer2);
#ifdef DEBUG
        printf("Class Version: %d.%d\n", class->Version.Major,
               class->Version.Minor);
#endif

        /* Read constant pool count */
        fread(buffer2, 1, 2, classfile);
        class->ConstantPoolNum = BufferToShort(buffer2);
#ifdef DEBUG
        printf("Constant pool count: %d\n", class->ConstantPoolNum);
#endif

        /* Allocate memory for constant pool */
        class->ConstantPool =
            (struct CONSTANTPOOL *) malloc(class->ConstantPoolNum *
                                              sizeof(struct CONSTANTPOOL));

        /* Read constants from pool */
        for (n = 1; n < class->ConstantPoolNum; n++) {
            fread(&buffer1, 1, 1, classfile);
            class->ConstantPool[n - 1].Tag = buffer1;

#ifdef DEBUG
            printf("%d: Constant Type %d\t", n, buffer1);
#endif

            switch (class->ConstantPool[n - 1].Tag) {
            case CONSTANTPOOL_FIELDREF:
                {
                    /* Allocating memory for REF_INFO */
                    class->ConstantPool[n - 1].Data =
                        malloc(sizeof(struct CONSTANT_REF_INFO));

                    /* Read class index */
                    fread(buffer2, 1, 2, classfile);
                    ((struct CONSTANT_REF_INFO *)
                        class->ConstantPool[n - 1].Data)->ClassIndex = BufferToShort(buffer2);

                    /* Read name and type index */
                    fread(buffer2, 1, 2, classfile);
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
                        malloc(sizeof(struct CONSTANT_CLASS_INFO));

                    /* Read name index */
                    fread(buffer2, 1, 2, classfile);
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
                        malloc(sizeof(struct CONSTANT_REF_INFO));

                    /* Read class index */
                    fread(buffer2, 1, 2, classfile);
                    ((struct CONSTANT_REF_INFO *)
                     class->ConstantPool[n - 1].Data)->ClassIndex =
BufferToShort(buffer2);

                    /* Read name and type index */
                    fread(buffer2, 1, 2, classfile);
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
                        malloc(sizeof(struct CONSTANT_REF_INFO));

                    /* Read class index */
                    fread(buffer2, 1, 2, classfile);
                    ((struct CONSTANT_REF_INFO *)
                     class->ConstantPool[n - 1].Data)->ClassIndex =
BufferToShort(buffer2);

                    /* Read name and type index */
                    fread(buffer2, 1, 2, classfile);
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
                        malloc(sizeof(struct CONSTANT_STRING_INFO));

                    /* Read string index */
                    fread(buffer2, 1, 2, classfile);
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
                        malloc(sizeof(struct CONSTANT_INTEGER_INFO));

                    /* Read integer */
                    fread(buffer4, 1, 4, classfile);
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
                    fread(buffer4, 1, 4, classfile);
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
                    fread((void *) &buffer8, 1, 8, classfile);
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
                        malloc(sizeof(struct CONSTANT_NAMETYPE_INFO));

                    /* Read name index */
                    fread(buffer2, 1, 2, classfile);
                    ((struct CONSTANT_NAMETYPE_INFO *)
                     class->ConstantPool[n -
                                         1].Data)->NameIndex =
                        BufferToShort(buffer2);

                    /* Read descriptor index */
                    fread(buffer2, 1, 2, classfile);
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
                    fread(buffer2, 1, 2, classfile);
                    ((struct CONSTANT_UTF8_INFO *)
                     class->ConstantPool[n - 1].Data)->Length =
BufferToShort(buffer2);

                    /* Allocating memory for string */
                    ((struct CONSTANT_UTF8_INFO *)
                     class->ConstantPool[n - 1].Data)->Text = (char *)
                        malloc(((struct CONSTANT_UTF8_INFO *) class->
                                   ConstantPool[n -
                                                1].Data)->Length *
                                  sizeof(char) + 1);

                    /* Read string */
                    fread((unsigned char*)((struct CONSTANT_UTF8_INFO *)
                        class->ConstantPool[n - 1].Data)->Text, 1,
                        ((struct CONSTANT_UTF8_INFO *)
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
                    fclose(classfile);
                    return false;
                }
            }
        }

        /* Read access flags */
        fread(buffer2, 1, 2, classfile);
        class->AccessFlags = BufferToShort(buffer2);

        /* Read this class index */
        fread(buffer2, 1, 2, classfile);
        class->ThisClassIndex = BufferToShort(buffer2);

        /* Read super class index */
        fread(buffer2, 1, 2, classfile);
        class->SuperClassIndex = BufferToShort(buffer2);

        /* Read interface count */
        fread(buffer2, 1, 2, classfile);
        class->InterfacesNum = BufferToShort(buffer2);

        /* Read interface indices */
        class->Interfaces =
            (unsigned short *) malloc(sizeof(unsigned short) *
                                         class->InterfacesNum);
        for (n = 0; n < class->InterfacesNum; n++) {
            fread(buffer2, 1, 2, classfile);
            class->Interfaces[n] = BufferToShort(buffer2);
        }

        /* Read fields count */
        fread(buffer2, 1, 2, classfile);
        class->FieldsNum = BufferToShort(buffer2);

        /* Read fields */
        class->Fields =
            (struct FIELD_INFO *) malloc(sizeof(struct FIELD_INFO) *
                                            class->FieldsNum);
        for (n = 0; n < class->FieldsNum; n++) {
            /* Read access flags */
            fread(buffer2, 1, 2, classfile);
            class->Fields[n].AccessFlags = BufferToShort(buffer2);

            /* Read name index */
            fread(buffer2, 1, 2, classfile);
            class->Fields[n].NameIndex = BufferToShort(buffer2);

            /* Read descriptor index */
            fread(buffer2, 1, 2, classfile);
            class->Fields[n].DescriptorIndex = BufferToShort(buffer2);

            /* Read attributes count */
            fread(buffer2, 1, 2, classfile);
            class->Fields[n].AttributesNum = BufferToShort(buffer2);

            /* Read attributes */
            class->Fields[n].Attributes = (struct ATTRIBUTE_INFO *)
                malloc(sizeof(struct ATTRIBUTE_INFO) *
                          class->Fields[n].AttributesNum);
            for (m = 0; m < class->Fields[n].AttributesNum; m++) {
                /* Read attribute name index */
                fread(buffer2, 1, 2, classfile);
                class->Fields[n].Attributes[m].AttributeNameIndex =
                    BufferToShort(buffer2);

                /* Read length of info array */
                fread(buffer4, 1, 4, classfile);
                class->Fields[n].Attributes[m].AttributeLength =
                    BufferToInt(buffer4);

                /* Allocate space for infos */
                class->Fields[n].Attributes[m].Info =
                    (unsigned char *) malloc(class->
                                                Fields[n].Attributes
                                                [m].AttributeLength);
                fread(class->Fields[n].Attributes[m].Info, 1,
                       class->Fields[n].Attributes[m].AttributeLength,
                       classfile);
            }
        }

        /* Read methods */
        ReadMethodInfo(class, classfile, mainIndex, attributeCodeIndex);

        /* Read attributes count */
        fread(buffer2, 1, 2, classfile);
        class->AttributesNum = BufferToShort(buffer2);

        /* Read attributes */
        class->Attributes = (struct ATTRIBUTE_INFO *)
            malloc(sizeof(struct ATTRIBUTE_INFO) *
                      class->AttributesNum);
        for (m = 0; m < class->AttributesNum; m++) {
            /* Read attribute name index */
            fread(buffer2, 1, 2, classfile);
            class->Attributes[m].AttributeNameIndex =
                BufferToShort(buffer2);

            /* Read length of info array */
            fread(buffer4, 1, 4, classfile);
            class->Attributes[m].AttributeLength = BufferToInt(buffer4);

            /* Allocate space for infos */
            class->Attributes[m].Info = (unsigned char *)
                malloc(sizeof(struct ATTRIBUTE_INFO) *
                          class->Attributes[m].AttributeLength);
            fread(class->Attributes[m].Info, 1,
                   class->Attributes[m].AttributeLength, classfile);
        }
    } else {
#ifdef DEBUG
        printf("IO-Error: %u\n", ferror(classfile));
#endif
        return false;
    }

    if (!feof(classfile)) {
        printf("Class not wellformed: unused data at end of file!\n");
    }

    fclose(classfile);

    return true;
}

bool ReadAttributeInfo(struct ATTRIBUTE_INFO * attributeInfo,
                       FILE* classfile)
{
    unsigned char buffer2[2];
    unsigned char buffer4[4];

#ifdef DEBUG
    printf("Begin reading ATTRIBUTE_INFO...\n");
#endif

    /* Read attribute name index */
    if (fread(buffer2, 1, 2, classfile) == 2) {
        attributeInfo->AttributeNameIndex = BufferToShort(buffer2);
    } else {
#ifdef DEBUG
        printf("Read of ATTRIBUTE_INFO.AttributeNameIndex failed!\n");
#endif
        return false;
    }

    /* Read length of info array */
    if (fread(buffer4, 1, 4, classfile) == 4) {
        attributeInfo->AttributeLength = BufferToInt(buffer4);
    } else {
#ifdef DEBUG
        printf("Read ATTRIBUTE_INFO.AttributeLength!\n");
#endif
        return false;
    }

    /* Allocate space for infos */
    attributeInfo->Info =
        (unsigned char *) malloc(sizeof(unsigned char) *
                                    attributeInfo->AttributeLength);

    if (attributeInfo->Info == NULL) {
        return false;
    }

    if (fread
        (attributeInfo->Info, 1, attributeInfo->AttributeLength,
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

bool ReadMethodInfo(Class * vmclass, FILE* classfile,
                    int mainIndex, int attributeCodeIndex)
{
    register short n, m, i;
    unsigned char buffer2[2];

    dbgmsg("Begin reading method_info_t...\n");

    /* Read methods count */
    if (fread(buffer2, 1, 2, classfile) == 2) {
        vmclass->MethodsNum = BufferToShort(buffer2);
    } else {
        return false;
    }

    /* Read methods */
    vmclass->Methods =
        (Method *) malloc(sizeof(Method) *
                                         vmclass->MethodsNum);

    if (vmclass->Methods == NULL) {
        return false;
    }

    for (n = 0; n < vmclass->MethodsNum; n++) {
        /* Read access flags */
        fread(buffer2, 1, 2, classfile);
        vmclass->Methods[n].AccessFlags = BufferToShort(buffer2);

        /* Read name index */
        fread(buffer2, 1, 2, classfile);
        vmclass->Methods[n].NameIndex = BufferToShort(buffer2);
        if (vmclass->Methods[n].NameIndex == mainIndex)
            vmclass->MainMethodIndex = n + 1;

        /* Read descriptor index */
        fread(buffer2, 1, 2, classfile);
        vmclass->Methods[n].DescriptorIndex = BufferToShort(buffer2);

        /* Read attributes count */
        fread(buffer2, 1, 2, classfile);
        vmclass->Methods[n].AttributesNum = BufferToShort(buffer2);

        /* Read attributes */
        vmclass->Methods[n].Attributes = (struct ATTRIBUTE_INFO *)
            malloc(sizeof(struct ATTRIBUTE_INFO) *
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
                    malloc(sizeof(struct ATTRIBUTE_INFO_CODE));
                vmclass->Methods[n].CodeInfo->AttributeNameIndex =
                    attributeCodeIndex;

                /* Attribute Length */
                vmclass->Methods[n].CodeInfo->AttributeLength
                    = vmclass->Methods[n].Attributes[m].AttributeLength;

                /* Read Max Stack (2 Byte) */
                vmclass->Methods[n].operandStackSize =
                    BufferToShort(vmclass->Methods[n].Attributes[m].Info +
                                  0);

                /* Allocate operand stack */
                /*vmclass->Methods[n].StackFrameRef.OperandStack
                   = (struct OperandStackFrame*)malloc(sizeof(struct OperandStackFrame) * vmclass->Methods[n].StackFrameRef.OperandStackSize);
                 */
                /* Read Max Locals (2 Byte) */
                vmclass->Methods[n].localVarsLen
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
                    malloc(sizeof(unsigned char) *
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
                    malloc(sizeof(struct ATTRIBUTE_INFO) *
                              vmclass->Methods[n].CodeInfo->AttributesNum);
            }
        }
    }

    /* Set full qualified name */
    vmclass->QualifiedName = "";

    return true;
}

FILE* find_class_file(const char* class)
{
    FILE* file;

    // Argument class is the Java class name with slashes as separator
    // instead of points, e.g. "java/lang/System".
    char* class_file = malloc(sizeof(char) * (strlen(class) + 7));
    strcpy(class_file, class);

    // At first we add ".class"
    strncat(class_file, ".class", 6);

    // Then we try all classpaths for the given class file
    // (currently there is only one classpath (and "."))
    file = fopen(class_file, "rb");
#ifdef DEBUG
    printf("Trying '%s'\n", class_file);
#endif
    if (file != NULL) {
        free(class_file);
        return file;
    }

    // FIXME
    char* class_file_path = malloc(sizeof(char) *
        (strlen(class_file) + /*strlen(VM.LibraryPath) +*/ 1));
    //strcpy(class_file_path, VM.LibraryPath);
    strncat(class_file_path, class_file, strlen(class_file));
    file = fopen(class_file_path, "rb");
#ifdef DEBUG
    printf("Trying '%s'\n", class_file_path);
#endif    

    // If we found it, we return the FILE handle to it
    free(class_file);
    return file;
}
