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
#include <bvm_error.h>

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
