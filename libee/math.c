/*
 *   libee         ASCII-Art library
 *   Copyright (c) 2002, 2003 Sam Hocevar <sam@zoy.org>
 *                 All Rights Reserved
 *
 *   $Id$
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "config.h"

#include <stdlib.h>

#include "ee.h"
#include "ee_internals.h"

int ee_rand(int min, int max)
{
    return min + (int)((1.0*(max-min+1)) * rand() / (RAND_MAX+1.0));
}

unsigned int ee_sqrt(unsigned int a)
{
    if(a == 0)
        return 0;

    if(a < 1000000000)
    {
        unsigned int x = a < 10 ? 1
                       : a < 1000 ? 10
                       : a < 100000 ? 100
                       : a < 10000000 ? 1000
                       : 10000;

        /* Newton's method. Three iterations would be more than enough. */
        x = (x * x + a) / x / 2;
        x = (x * x + a) / x / 2;
        x = (x * x + a) / x / 2;
        x = (x * x + a) / x / 2;

        return x;
    }

    return 2 * ee_sqrt(a / 4);
}

