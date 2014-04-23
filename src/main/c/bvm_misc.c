/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xam.h>

/* Works only for reading bigendian and saving in littleendian */
unsigned int BufferToInt_LittleEndian(unsigned char buffer[4])
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

/* Works only for reading bigendian and saving in bigendian */
unsigned int BufferToInt_BigEndian(unsigned char buffer[4])
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

/* Works only for reading bigendian (Java) and saving in littleendian */
unsigned short BufferToShort_LittleEndian(unsigned char buffer[2])
{
    register unsigned short var = 0;

    var = buffer[0];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[1];

    return var;
}

/* Works only for reading bigendian (Java) and saving in bigendian */
unsigned short BufferToShort_BigEndian(unsigned char buffer[2])
{
    register unsigned short var = 0;

    var = buffer[1];
    var = var << (sizeof(unsigned char) * 8);
    var = var | buffer[0];

    return var;
}

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
