/*
 *  XAM Xerxys Artificial Machine
 *  Copyright (C) 2005-2012 Christian Lins <christian@lins.me>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _XAM_LINK_H_
#define _XAM_LINK_H_

#include "xam_class.h"
#include "xam_process.h"

struct LINKFLAGS
{
  unsigned int AbortInvoke : 1; /* Abort the Invoke, e.g. because of a internal handled constructor. */
  unsigned int IsNative    : 1; /* Invoked method is natively handled by the VM. */
};

struct METHOD* dlink(struct VMTHREAD*, unsigned short, struct LINKFLAGS*);
struct METHOD* find_method_name(struct VMCLASS*, const char*);

#endif
