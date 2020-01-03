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

#ifndef _LINKER_H_
#define _LINKER_H_

#include <class.h>
#include <thread.h>

struct LINKFLAGS
{
  unsigned int AbortInvoke : 1; /* Abort the Invoke, e.g. because of a internal handled constructor. */
  unsigned int IsNative    : 1; /* Invoked method is natively handled by the VM. */
};

Method* dlink(Thread*, unsigned short, struct LINKFLAGS*);
Method* find_method_name(Class*, const char*);

Class* Classloader_forName(char* qualifiedName);

#endif
