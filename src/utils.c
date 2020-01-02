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

#include <vm.h>

#define __BYTE_ORDER_LITTLE_ENDIAN__

#ifdef __BYTE_ORDER_LITTLE_ENDIAN__
/* Works only for reading bigendian and saving in littleendian */
unsigned int BufferToInt(unsigned char buffer[4])
{
    register unsigned int var = 0;

    var = buffer[0];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[1];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[2];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[3];

    return var;
}
#endif

#ifdef __BYTE_ORDER_BIG_ENDIAN__
/* Works only for reading bigendian and saving in bigendian */
unsigned int BufferToInt(unsigned char buffer[4])
{
    register unsigned int var = 0;

    var = buffer[3];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[2];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[1];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[0];

    return var;
}
#endif

#ifdef __BYTE_ORDER_LITTLE_ENDIAN__
/* Works only for reading bigendian (Java) and saving in littleendian */
unsigned short BufferToShort(unsigned char buffer[2])
{
    register unsigned short var = 0;

    var = buffer[0];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[1];

    return var;
}
#endif

#ifdef __BYTE_ORDER_ORDER_BIG_ENDIAN__
/* Works only for reading bigendian (Java) and saving in bigendian */
unsigned short BufferToShort(unsigned char buffer[2])
{
    register unsigned short var = 0;

    var = buffer[1];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[0];

    return var;
}
#endif

/*
 * Creates a complete system path using a classname (without extension) and the
 * classlib path.
 */
char *compose_path(char *className, char *basePath)
{
    int n, pathLength;
    char *completePath;

    assert(className != NULL);
    assert(basePath != NULL);

    /* Don't forget the \0 and '/' */
    pathLength =
        strlen(basePath) + strlen(className) + strlen(".class") + 2;
    completePath = (char *) malloc(sizeof(char) * pathLength);

    /* Clear the buffer, otherwise strcat does not work */
    for (n = 0; n < pathLength; n++) {
        completePath[n] = 0;
    }

    strcat(completePath, basePath);
    strcat(completePath, "/");
    strcat(completePath, className);
    strcat(completePath, ".class");

    completePath[pathLength - 1] = 0;

#ifdef WIN32
    for (n = 0; n < pathLength; n++)
        if (completePath[n] == '/') {
            completePath[n] = '\\';
        }
#endif

#ifdef DEBUG
    printf("Combined Path: %s\n", completePath);
#endif

    return completePath;
}
