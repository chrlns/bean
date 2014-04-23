/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>
#include <xam_io.h>
#include <xam_mem.h>

void IOClose(IOHandle * io)
{
    if (io == NULL) {
        return;
    }

    if (io->Allocated == true) {
        xam_free(io->Buffer);
    }

    xam_free(io);
}

bool IOEnd(IOHandle * io)
{
    if (io == NULL) {
        return true;
    }

    if (io->Length <= io->Pointer) {
        return true;
    } else {
        return false;
    }
}

IOHandle *IOOpen(IOIdentifier id)
{
    IOHandle *io = NULL;
    FILE *file = NULL;
    register int n = 0;
    register int readBytes = 0;

    if (id.filename == NULL
        && (id.filebuffer == NULL || id.filebuffer_len == 0)) {
        RaiseException(ExceptionIO, "IOOpen", __FILE__, __LINE__);
    }

    /* Create IOHandle */
    io = (IOHandle *) xam_alloc(sizeof(IOHandle));
    if (io == NULL) {
        printf("Could not allocate memory!\n");
        RaiseException(ExceptionUnknown, "IOOpen", __FILE__, __LINE__);
    }
    io->Buffer = NULL;

    if (id.filename != NULL) {
        file = fopen(id.filename, "rb");
        if (file == NULL) {
            return NULL;
        }

        /* Read file in 4k blocks because that's the fastest method to alloc
         * and read blocks */
        while (!feof(file)) {
            n++;
            /* We start with 4k */
            io->Buffer =
                (unsigned char *) xam_realloc(io->Buffer,
                                              sizeof(unsigned char) *
                                              4096 * n);
            io->Length = 4096 * n;

            readBytes =
                fread(io->Buffer + (4096 * (n - 1)),
                      sizeof(unsigned char), 4096, file);
        }

        /* We leave the buffer 4k aligned but set the real size */
        io->Length = io->Length - (4096 - readBytes);
        io->Allocated = true;
        io->Pointer = 0;

        fclose(file);
    } else {
        if (id.filebuffer_len == 0) {
            return NULL;
        }

        io->Length = id.filebuffer_len;
        io->Pointer = 0;
        io->Buffer = (unsigned char *) id.filebuffer;
        io->Allocated = false;
    }

    return io;
}

int IORead(unsigned char *buffer, int count, IOHandle * io)
{
    int readBytes = 0;

    while (IOEnd(io) == false && count > readBytes) {
        buffer[readBytes] = io->Buffer[io->Pointer];
        readBytes++;
        io->Pointer++;
    }

    return readBytes;
}
