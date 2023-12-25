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

#include <classloader.h>
#include <debug.h>
#include <linker.h>
#include <vm.h>

extern VM* vm;

bool IsNative(Thread * thread, unsigned short methodIndex,
              struct LINKFLAGS * flags) {
    return false; // FIXME
}

/**
 * Parses an Method descriptor string.
 * For example for method "Object m(int i, double d, Thread t) {..}" => 
 * "(IDLjava/lang/Thread;)Ljava/lang/Object;"
 */
void Method_parseDescriptor(Method* method, const char* descriptor) {
    
}

/**
 * Finds, loads and initializes a new class specified by the
 * full qualified name.
 */
Class* Classloader_forName(const char* qualifiedName) {
    printf("Classload_forName: %s\n", qualifiedName);
    /* Search for already loaded class */
    for (int n = 0; n < vm->classloader->loaded_classes_num; n++) {
        //printf("Comparing %s with %s\n", qualifiedName, vm->classloader->loaded_classes[n].QualifiedName);
        if (strcmp(qualifiedName, vm->classloader->loaded_classes[n].QualifiedName) == 0) {
            dbgmsg("Class already loaded.");
            return &vm->classloader->loaded_classes[n];
        }
    }

    FILE* class_file = find_class_file(qualifiedName);
    if (class_file == NULL) {
        printf("Classfile %s not found!\n", qualifiedName);
        exit(-1);
        //return NULL; // FIXME We should raise an exception here
    }

    Class* class = Class_new();
    if (load_class_file(class_file, class) == false) {
        return NULL;
    }

    // Initialize the class instance
    class->QualifiedName = (char*)malloc(sizeof(char) * strlen(qualifiedName) + 1);
    strcpy(class->QualifiedName, qualifiedName);

    return class;
}


/* This method searches in the local constant pool for a method and returns the index
     of the method in the MethodLookupTable. */
Method* find_method_name(Class* vmclass, const char* qualifiedName)
{
    unsigned short n, nameIndex;

#ifdef DEBUG
    printf("Link: finding method %s...", qualifiedName);
#endif

    if (vmclass == NULL) {
        return NULL;
    }

    for (n = 0; n < vmclass->MethodsNum; n++) {
        nameIndex = vmclass->Methods[n].NameIndex - 1;  /* Constant Pool index starts with 1, so we must subtract one */
        if (strcmp(qualifiedName, ((struct CONSTANT_UTF8_INFO *)vmclass->ConstantPool[nameIndex].Data)->Text) == 0) {
            dbgmsg("Found method.");
            return &(vmclass->Methods[n]);
        }
    }

    dbgmsg("Method not found!");
    return NULL;
}

Method* find_method_nameidx(Class *vmclass, short methodNameIndex)
{
    for (uint16_t n = 0; n < vmclass->MethodsNum; n++) {
        if (vmclass->Methods[n].NameIndex == methodNameIndex + 1) {     /* +1 ? */
            return &(vmclass->Methods[n]);
        }
    }

    return NULL;
}

/*
 * This method tries to find a method by parsing the string identifier
 * and looking for method in local classes.
 */
Method* find_method_idx(Class *vmclass,
                               Thread *thread,
                               uint16_t methodIndex,
                               struct LINKFLAGS *flags)
{
    Class* methodClass;
    Method* methodInvoked;
    unsigned short classIndex, classNameIndex, nameTypeIndex,
        methodNameIndex;
    char* className;
    char* methodName;

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
        methodClass = Classloader_forName(className);
        methodInvoked = find_method_name(methodClass, methodName);      /* Search for method to be invoked */

        if (methodInvoked == NULL) {
            return NULL;
        }

        return methodInvoked;

        if (strcmp(methodClass->QualifiedName, "java/lang/Object") != 0) {
//          /* Find class constructor */
//          methodConstructor = FindMethodByName(methodClass, "<init>");

            /* Push StackFrames */
//          Stack_push(&thread->methodStack, clone_stackframe(&methodInvoked->Method->StackFrameRef));
//          Stack_push(&thread->methodStack, clone_stackframe(&methodConstructor->Method->StackFrameRef));

            /* The constructor must return to the invoked method, so we edit the return values... */
//          invokeStackFrame->method                    = methodInvoked;
//          invokeStackFrame->instruction_ptr = methodInvoked->Method->CodeInfo->Code;
            /* InvokeStackPush */
//          Stack_push(&thread->invokeStack, invokeStackFrame);

//          return methodConstructor;
            dbgmsg("Not implemented");
            exit(-1);
        }

        /* Class is the base-of-all java/lang/Object */
        if (strcmp((const char*)methodName, "<init>") == 0) {
            flags->AbortInvoke = true;
            return NULL;
        } else
            return methodInvoked;
    }
}

/* Dynamically finds a method to invoke */
Method* dlink(Thread *thread, unsigned short methodIndex,
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
