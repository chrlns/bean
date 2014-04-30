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

void do_I2S(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tI2S\n");
#endif
}

void do_I2L(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tI2L\n");
#endif
}

void do_I2C(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tI2C\n");
#endif
}

void do_I2B(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tI2B\n");
#endif
}

void do_I2D(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tI2D\n");
#endif
}

void do_I2F(struct VMTHREAD *thread)
{
#ifdef DEBUG
    printf("\tI2F\n");
#endif
}
