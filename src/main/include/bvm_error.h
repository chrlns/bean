/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_ERROR_H_
#define _XAM_ERROR_H_

#include "xam.h"

enum ExceptionType
{
  ExceptionUnknown,
  ExceptionIO,
  ExceptionOutOfMemory,
  ExceptionNoSuchMethod,
  ExceptionStackOverflow,
  ExceptionStackUnderflow
};

#endif

bool RaiseException(enum ExceptionType exceptionType, const char* method, const char* file, int line);
