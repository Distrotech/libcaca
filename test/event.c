/*
 *  event         event lister for libcaca
 *  Copyright (c) 2004 Sam Hocevar <sam@zoy.org>
 *                All Rights Reserved
 *
 *  $Id$
 *
 *  This program is free software. It comes without any warranty, to
 *  the extent permitted by applicable law. You can redistribute it
 *  and/or modify it under the terms of the Do What The Fuck You Want
 *  To Public License, Version 2, as published by Sam Hocevar. See
 *  http://sam.zoy.org/wtfpl/COPYING for more details.
 */

#include "config.h"
#include "common.h"
#if !defined(__KERNEL__)
#   include <stdio.h>
#   include <string.h>
#   include <stdlib.h>
#endif

#include "cucul.h"
#include "caca.h"

static cucul_canvas_t *cv;
static caca_display_t *dp;

static void print_event(int, int, caca_event_t *);

int main(int argc, char **argv)
{
    caca_event_t *events;
    int i, h, quit;

    cv = cucul_create_canvas(80, 24);
    if(cv == NULL)
    {
        printf("Failed to create canvas\n");
        return 1;
    }

    dp = caca_create_display(cv);
    if(dp == NULL)
    {
        printf("Failed to create display\n");
        return 1;
    }

    h = cucul_get_canvas_height(cv) - 1;

    cucul_set_color_ansi(cv, CUCUL_WHITE, CUCUL_BLUE);
    cucul_draw_line(cv, 0, 0, cucul_get_canvas_width(cv) - 1, 0, ' ');

    cucul_draw_line(cv, 0, h, cucul_get_canvas_width(cv) - 1, h, ' ');
    cucul_put_str(cv, 0, h, "type \"quit\" to exit");

    caca_refresh_display(dp);

    events = malloc(h * sizeof(caca_event_t));
    memset(events, 0, h * sizeof(caca_event_t));

    for(quit = 0; quit < 4; )
    {
        caca_event_t ev;
        static char const * quit_string[] = { "", "q", "qu", "qui", "quit" };
        int ret = caca_get_event(dp, CACA_EVENT_ANY, &ev, -1);

        if(!ret)
            continue;

        do
        {
            /* "quit" quits */
            if(ev.type & CACA_EVENT_KEY_PRESS)
            {
                int key = ev.data.key.ch;
                if((key == 'q' && quit == 0) || (key == 'u' && quit == 1)
                    || (key == 'i' && quit == 2) || (key == 't' && quit == 3))
                    quit++;
                else if(key == 'q')
                    quit = 1;
                else
                    quit = 0;
            }

            memmove(events + 1, events, (h - 1) * sizeof(caca_event_t));
            events[0] = ev;

            ret = caca_get_event(dp, CACA_EVENT_ANY, &ev, 0);
        }
        while(ret);

        cucul_set_color_ansi(cv, CUCUL_LIGHTGRAY, CUCUL_BLACK);
        cucul_clear_canvas(cv);

        /* Print current event */
        cucul_set_color_ansi(cv, CUCUL_WHITE, CUCUL_BLUE);
        cucul_draw_line(cv, 0, 0, cucul_get_canvas_width(cv) - 1, 0, ' ');
        print_event(0, 0, events);

        cucul_draw_line(cv, 0, h, cucul_get_canvas_width(cv) - 1, h, ' ');
        cucul_printf(cv, 0, h, "type \"quit\" to exit: %s", quit_string[quit]);

        /* Print previous events */
        cucul_set_color_ansi(cv, CUCUL_WHITE, CUCUL_BLACK);
        for(i = 1; i < h && events[i].type; i++)
            print_event(0, i, events + i);

        caca_refresh_display(dp);
    }

    /* Clean up */
    caca_free_display(dp);
    cucul_free_canvas(cv);

    return 0;
}

static void print_event(int x, int y, caca_event_t *ev)
{
    int character;

    switch(ev->type)
    {
    case CACA_EVENT_NONE:
        cucul_printf(cv, x, y, "CACA_EVENT_NONE");
        break;
    case CACA_EVENT_KEY_PRESS:
        character = ev->data.key.ch;
        cucul_printf(cv, x, y, "CACA_EVENT_KEY_PRESS 0x%02x (%c)", character,
                     (character > 0x1f && character < 0x80) ? character : '?');
        break;
    case CACA_EVENT_KEY_RELEASE:
        character = ev->data.key.ch;
        cucul_printf(cv, x, y, "CACA_EVENT_KEY_RELEASE 0x%02x (%c)", character,
                     (character > 0x1f && character < 0x80) ? character : '?');
        break;
    case CACA_EVENT_MOUSE_MOTION:
        cucul_printf(cv, x, y, "CACA_EVENT_MOUSE_MOTION %u %u",
                     ev->data.mouse.x, ev->data.mouse.y);
        break;
    case CACA_EVENT_MOUSE_PRESS:
        cucul_printf(cv, x, y, "CACA_EVENT_MOUSE_PRESS %u",
                     ev->data.mouse.button);
        break;
    case CACA_EVENT_MOUSE_RELEASE:
        cucul_printf(cv, x, y, "CACA_EVENT_MOUSE_RELEASE %u",
                     ev->data.mouse.button);
        break;
    case CACA_EVENT_RESIZE:
        cucul_printf(cv, x, y, "CACA_EVENT_RESIZE %u %u",
                     ev->data.resize.w, ev->data.resize.h);
        break;
    case CACA_EVENT_QUIT:
        cucul_printf(cv, x, y, "CACA_EVENT_QUIT");
        break;
    default:
        cucul_printf(cv, x, y, "CACA_EVENT_UNKNOWN");
    }
}

