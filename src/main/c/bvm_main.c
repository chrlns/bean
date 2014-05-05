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
#include <bvm_process.h>

/* Global */
struct VM VM;

/* Function pointers */
unsigned int (*BufferToInt) (unsigned char[4]);
unsigned short (*BufferToShort) (unsigned char[2]);

int XamInit(void)
{
    dbgmsg("Initializing Bean Java VM...");

    /* Set some function pointer... */
    BufferToInt = &BufferToInt_LittleEndian;
    BufferToShort = &BufferToShort_LittleEndian;

    VM.Initialized = true;
    VM.LocalClassesNum = 0;
    VM.LibraryPath = "/usr/share/classpath";

    /* Initialize Monitors */
    VM.Monitors = NULL;

    return true;
}


int main(int argc, char *argv[])
{
    char* main_class = NULL;

    /* Parsing command line options */
    if (argc > 1) {
        for (int n = 1; n < argc; n++) {
            if (argv[n][0] == '-') {
                if (strcmp(argv[n], "-cp") == 0) {
                    VM.LibraryPath = argv[++n];
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
        printf("-cp\t Class path (currently only one supported)\n");
        return 0;
    }

    FILE* class_file = find_class_file(main_class);
    if (class_file == NULL) {
        printf("Could not open main class: %s\n", main_class);
        return 1;
    }

    /* Initalizing virtual machine... */
    if (VM.Initialized == false) {
        XamInit();
    }

    /* Creating init processes... */
    if (start_process(class_file) == false) {
        printf("Fatal Error: Could not start init process %s!\n", main_class);
        return 2;
    }

    dbgmsg("Start!");
    VM.Running = true;

    /* While using green thread model this method returns only when
     * the process ends. */
    exec_process();

    dbgmsg("Shutdown virtual machine...");
    return true;
}

bool XamSignal(unsigned int signal)
{
    return 0;
}
