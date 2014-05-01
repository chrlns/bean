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
    dbgmsg("Initializing Xerxys Artificia Machina...");

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

#ifndef XERXYS
int main(int argc, char *argv[])
{
    void *mempointer = NULL;
    int memsize = 0;
#else
int XamStart(int argc, char *argv[], void *mempointer, int memsize)
{
#endif
    int n;
    char *processFile = NULL;
    IOIdentifier processFileID;

    /* Parsing command line options */
    if (argc > 1) {
        for (n = 1; n < argc; n++) {
            if (argv[n][0] == '-') {
                switch (argv[n][1]) {
                case 'f':      /* Filename of startup class */
                    {
                        processFile = argv[++n];
                        break;
                    }
                case 'l':      /* Path to the classlib */
                    {
                        VM.LibraryPath = argv[++n];
                        break;
                    }
                default:       /* Handling of long parameter names */
                    {
                        if (strcmp(argv[n], "-bootclasspath") == 0) {
                            VM.LibraryPath = argv[++n];
                        }
                        break;
                    }
                }
            } else {
                /* Could be the name of the startup class */
                processFile = argv[n];
            }
        }
    }

    if (processFile == NULL && mempointer == NULL) {
        printf("bean [options] <classname>\n");
        printf("Missing options!\n");
        printf("-bootclasspath\t Class library path\n");

        return false;
    }

    processFileID.filename = strncat(processFile, ".class", 6);
    processFileID.filebuffer = (unsigned char *) mempointer;
    processFileID.filebuffer_len = memsize;

    /* Initalizing virtual machine... */
    if (VM.Initialized == false) {
        XamInit();
    }

    /* Creating init processes... */
    if (start_process(processFileID) == false) {
        printf("Fatal Error: Could not start init process %s!\n",
               processFile);
        return false;
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
