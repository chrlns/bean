/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "include/xam.h"
#include "include/xam_error.h"

const char *ExceptionText[] = {
    "Unknown",
    "IO",
    "OutOfMemory",
    "NoSuchMethod",
    "StackOverflow",
    "StackUnderflow"
};

bool RaiseException(enum ExceptionType exceptionType, const char *method,
                    const char *file, int line)
{
    printf("\n%sException has occurred in method %s:%s:%d!\n",
           ExceptionText[exceptionType], method, file, line);

    /* Exit this Process */
    exit((int) exceptionType);

    return false;
}
