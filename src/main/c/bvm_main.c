/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <xam.h>
#include <xam_process.h>

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
        printf("xam [options] <classname>\n");
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
