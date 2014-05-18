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

#include <bvm.h>
#include <bvm_class.h>
#include <bvm_io.h>
#include <bvm_link.h>
#include <bvm_mem.h>

bool IsNative(struct VMTHREAD * thread, unsigned short methodIndex,
              struct LINKFLAGS * flags);

/**
 * Finds, loads and initializes a new class specified by the
 * full qualified name.
 */
struct VMCLASS *FindClassByName(char* qualifiedName)
{
    IOIdentifier fileID;
    struct VMCLASS *class = NULL;
    int n;

    /* Search for already loaded class */
    for (n = 0; n < VM.LocalClassesNum; n++) {
        if (strcmp(qualifiedName, VM.LocalClasses[n]->QualifiedName) == 0) {
#ifdef DEBUG
            printf("Class already loaded.\n");
#endif
            return VM.LocalClasses[n];
        }
    }

    FILE* class_file = find_class_file(qualifiedName);
    if (class_file == NULL) {
        printf("Classfile %s not found!\n", qualifiedName);
        return NULL;
    }

    VM.LocalClassesNum++;
    VM.LocalClasses = (struct VMCLASS **) xam_realloc(VM.LocalClasses,
                                                      sizeof(struct VMCLASS
                                                             *) *
                                                      VM.LocalClassesNum);

    class = (struct VMCLASS *) xam_alloc(sizeof(struct VMCLASS));
    VM.LocalClasses[VM.LocalClassesNum - 1] = class;

    if (load_class_file(class_file, class) == false) {
        return NULL;
    }

    /* We must initialize the class file later */

    return class;
}

struct VMCLASS *FindClassByNameIndex(struct VMCLASS *localClass,
                                     unsigned short nameIndex)
{
    return NULL;
}

/* This method searches in the local constant pool for a method and returns the index
     of the method in the MethodLookupTable. */
struct method_t* find_method_name(struct VMCLASS *vmclass,
                                const char *qualifiedName)
{
    unsigned short n, nameIndex;
    struct method_t* method;

#ifdef DEBUG
    printf("Link: finding method %s...", qualifiedName);
#endif

    if (vmclass == NULL) {
        return NULL;
    }

    for (n = 0; n < vmclass->MethodsNum; n++) {
        nameIndex = vmclass->Methods[n].NameIndex - 1;  /* Constant Pool index starts with 1, so we must subtract one */
        if (strcmp
            (qualifiedName,
             ((struct CONSTANT_UTF8_INFO *)
              vmclass->ConstantPool[nameIndex].Data)->Text) == 0) {
            method = (struct method_t*)xam_alloc(sizeof(struct method_t));
            method->method_info = &(vmclass->Methods[n]);
            method->class = vmclass;

#ifdef DEBUG
            printf("Found!\n");
#endif

            return method;
        }
    }

#ifdef DEBUG
    printf("NOT found!\n");
#endif

    return NULL;
}

struct method_t* find_method_nameidx(struct VMCLASS *vmclass,
                                   short methodNameIndex)
{
    unsigned short n;
    struct method_t* method;

    for (n = 0; n < vmclass->MethodsNum; n++) {
        if (vmclass->Methods[n].NameIndex == methodNameIndex + 1) {     /* +1 ? */
            method = (struct method_t *) xam_alloc(sizeof(struct method_t));
            method->method_info = &(vmclass->Methods[n]);
            method->class = vmclass;
            return method;
        }
    }

    return NULL;
}

/*
 * This method tries to find a method by parsing the string identifier
 * and looking for method in local classes.
 */
struct method_t *find_method_idx(struct VMCLASS *vmclass,
                               struct VMTHREAD *thread,
                               uint16_t methodIndex,
                               struct LINKFLAGS *flags)
{
    struct VMCLASS *methodClass;
    struct method_t* methodInvoked;
    unsigned short classIndex, classNameIndex, nameTypeIndex,
        methodNameIndex;
    char *className;
    char *methodName;

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

#ifdef DEBUG
    printf("Find method %s (%d)(%d %d) in %s (%d %d)..\n",
           methodName, methodIndex, nameTypeIndex, methodNameIndex,
           className, classIndex, classNameIndex);
#endif

    if (classIndex + 1 == vmclass->ThisClassIndex) {
        return find_method_nameidx(vmclass, methodNameIndex);
    } else {
        methodClass = FindClassByName(className);
        methodInvoked = find_method_name(methodClass, methodName);      /* Search for method to be invoked */

        if (methodInvoked == NULL) {
            return NULL;
        }

        return methodInvoked;

        if (strcmp(methodClass->QualifiedName, "java/lang/Object") != 0) {
//          /* Find class constructor */
//          methodConstructor = FindMethodByName(methodClass, "<init>");

            /* Push StackFrames */
//          stack_push(&thread->methodStack, clone_stackframe(&methodInvoked->Method->StackFrameRef));
//          stack_push(&thread->methodStack, clone_stackframe(&methodConstructor->Method->StackFrameRef));

            /* The constructor must return to the invoked method, so we edit the return values... */
//          invokeStackFrame->method                    = methodInvoked;
//          invokeStackFrame->instruction_ptr = methodInvoked->Method->CodeInfo->Code;
            /* InvokeStackPush */
//          stack_push(&thread->invokeStack, invokeStackFrame);

//          return methodConstructor;
            dbgmsg("Not implemented");
            return NULL;
        }

        /* Class is the base-of-all java/lang/Object */
        if (strcmp(methodName, "<init>") == 0) {
            flags->AbortInvoke = true;
            return NULL;
        } else
            return methodInvoked;
    }
}

/* Dynamically finds a method to invoke */
struct method_t* dlink(struct VMTHREAD *thread, unsigned short methodIndex,
                     struct LINKFLAGS *flags)
{
    if (IsNative(thread, methodIndex, flags) == false) {
        return find_method_idx(thread->RunningClass, thread,
                               methodIndex, flags);
    } else {
        dbgmsg("Native linking not yet supported!");
        return NULL;
    }
}
