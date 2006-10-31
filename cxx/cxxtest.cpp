/*
 *  cpptest       libcaca++ rendering test
 *  Copyright (c) 2006 Jean-Yves Lamoureux <jylam@lnxscene.org>
 *                All Rights Reserved
 *
 *  $Id$
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the Do What The Fuck You Want To
 *  Public License, Version 2, as published by Sam Hocevar. See
 *  http://sam.zoy.org/wtfpl/COPYING for more details.
 */

#include "config.h"

#include <iostream>

#include <cucul++.h>
#include <caca++.h>

using namespace std;


static char const *pig[]= {
    "                                   ",
    "                             _     ",
    "    _._ _..._ .-',     _.._(`))    ",
    "   '-. `     '  /-._.-'    ',/     ",
    "      )         \\            '.    ",
    "     / _    _    |             \\   ",
    "    |  a    a    /              |  ",
    "    \\   .-.                     ;  " ,
    "     '-('' ).-'       ,'       ;   ",
    "        '-;           |      .'    ",
    "           \\           \\    /      ",
    "           | 7  .__  _.-\\   \\      ",
    "           | |  |  ``/  /`  /      ",
    "      jgs /,_|  |   /,_/   /       ",
    "             /,_/      '`-'        ",
    "                                   ",
 NULL
};

int main(int argc, char *argv[])
{
    Cucul *qq;
    Caca  *kk;
    Event ev;

    int x = 0, y = 0, ix = 1, iy = 1;



    try {
        qq = new Cucul();
    }
    catch (int e) {
        cerr << "Error while initializing cucul (" << e << ")" << endl;
        return -1;
    }

    try {
        kk = new Caca(qq);
    }
    catch(int e) {
        cerr << "Error while attaching cucul to caca (" << e << ")" << endl;
        return -1;
    }

    kk->setDisplayTime(20000);

    while(!kk->getEvent(ev.CACA_EVENT_KEY_PRESS, &ev, 0)) {

        /* Draw pig */
        qq->setColor(CUCUL_LIGHTMAGENTA, CUCUL_BLACK);

        for(int i = 0; pig[i]; i++)
            qq->putStr(x, y+i, (char*)pig[i]);

        /* printf works */
        qq->setColor(CUCUL_LIGHTBLUE, CUCUL_BLACK);
        qq->Printf(30,15, "Powered by libcaca %s", VERSION);

        /* Blit */
        kk->Display();

        x+=ix;
        y+=iy;

        if(x>=(qq->getWidth()-35)  || x<0 )
            ix=-ix;
        if(y>=(qq->getHeight()-15)   || y<0 )
            iy=-iy;


    }


    delete kk;
    delete qq;

    return 0;
}
