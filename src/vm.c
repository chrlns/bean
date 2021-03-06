/*
 *  Bean Java VM
 *  Copyright (C) 2005-2020 Christian Lins <christian@lins.me>
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

#include <class.h>
#include <debug.h>
#include <thread_fn.h>
#include <vm.h>

VM* vm;

/*
 * Constructor for VM.
 * Creates, initializes and returns a new VM instance.
 */
VM* VM_new() {
    VM* vm = (VM*)malloc(sizeof(VM));

    vm->alive = true;
    vm->classloader = Classloader_new();
    vm->classpath = "./";
	vm->ThreadNum = 0;
	vm->Threads = NULL;

    return vm;
}

/*
 * Destroys the VM instance and frees its resources.
 */
void VM_destroy(VM* vm) {
    Classloader_destroy(vm->classloader);
    free(vm);
}

int main(int argc, char *argv[])
{
    char* main_class = NULL;
    bool argXexecstep = false;

    /* Create new VM instance */
    vm = VM_new();    
    
    /* Parsing command line options */
    if (argc > 1) {
        for (int n = 1; n < argc; n++) {
            if (argv[n][0] == '-') {
                if (strcmp(argv[n], "-cp") == 0) {
                    vm->classpath = argv[++n];
                } else if (strcmp(argv[n], "-Xexecstep") == 0) {
                    argXexecstep = true;
                } else {
                    printf("Unknown argument '%s'\n", argv[n]);
                }
            } else {
                /* Could be the name of the startup class */
                main_class = argv[n];
            }
        }
    }

    if (main_class == NULL) {
        printf("bean [options] <classname>\n");
        printf("Missing options!\n");
        printf("-cp\t\t Class path (currently only one supported)\n");
        printf("-Xexecstep\t Pause execution after every instruction\n");
        return 0;
    }

    Class* mainClass = Classloader_forName(main_class);
    if (mainClass == NULL) {
        printf("Could not open main class: %s\n", main_class);
        return 1;
    }

    /* Creating init processes... */
    if (start_process(mainClass) == false) {
        printf("Fatal Error: Could not start init process %s!\n", main_class);
        return 2;
    }

    dbgmsg("Start!");
    while (vm->alive) {
        Thread* thread = Thread_next_ready();
        Thread_exec(thread, argXexecstep);
    }

    dbgmsg("Shutdown virtual machine...");
    return 0;
}
