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

#if defined(USE_SLANG)
#   include <slang.h>
#elif defined(USE_NCURSES)
#   include <curses.h>
#elif defined(USE_CONIO)
#   include <conio.h>
#else
#   error "no graphics library detected"
#endif

#include <string.h>
#include <stdlib.h>

#include "ee.h"

static int ee_color = 0;
#if defined(USE_CONIO)
static enum COLORS dos_colors[] = {
    0,
    BLACK,
    GREEN,
    YELLOW,
    WHITE,
    RED,
    DARKGRAY,
    LIGHTGRAY,
    BLUE,
    CYAN,
    MAGENTA
};
#endif

void ee_set_color(int color)
{
    ee_color = color;
#if defined(USE_SLANG)
    SLsmg_set_color(color);
#elif defined(USE_NCURSES)
    attrset(COLOR_PAIR(color));
#elif defined(USE_CONIO)
    if(color >= 1 && color <= 10)
        textcolor(dos_colors[color]);
#endif
}

int ee_get_color(void)
{
    return ee_color;
}

extern char *_screen_buffer;

void ee_putchar(int x, int y, char c)
{
#if defined(USE_SLANG)
    SLsmg_gotorc(y,x);
    SLsmg_write_char(c);
#elif defined(USE_NCURSES)
    move(y,x);
    addch(c);
#elif defined(USE_CONIO)
    if(x<0 || x>=ee_get_width() || y<0 || y>=ee_get_height())
        return;
    _screen_buffer[2 * (x + y * ee_get_width())] = c;
    _screen_buffer[2 * (x + y * ee_get_width()) + 1] = dos_colors[ee_color];
//    gotoxy(x+1,y+1);
//    putch(c);
#endif
}

void ee_putstr(int x, int y, char *s)
{
    if(y<0 || y>=ee_get_height())
        return;
#if defined(USE_SLANG)
    SLsmg_gotorc(y,x);
    SLsmg_write_string(s);
#elif defined(USE_NCURSES)
    move(y,x);
    addstr(s);
#elif defined(USE_CONIO)
    char *buf = _screen_buffer + 2 * (x + y * ee_get_width());
    while(*s)
    {
        *buf++ = *s++;
        *buf++ = dos_colors[ee_color];
    }
//    gotoxy(x+1,y+1);
//    cputs(s);
#endif
}

void ee_clear(void)
{
    /* We could use SLsmg_cls() etc., but drawing empty lines is much faster */
    int x = ee_get_width(), y = ee_get_height();
    char *empty_line = malloc((x + 1) * sizeof(char));

    memset(empty_line, ' ', x);
    empty_line[x] = '\0';

    while(y--)
    {
        ee_putstr(0, y, empty_line);
    }

    free(empty_line);
}

