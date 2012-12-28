/*
 *  libcaca       Colour ASCII-Art library
 *  Copyright (c) 2006 Sam Hocevar <sam@hocevar.net>
 *                2009 Jean-Yves Lamoureux <jylam@lnxscene.org>
 *                All Rights Reserved
 *
 *  This library is free software. It comes without any warranty, to
 *  the extent permitted by applicable law. You can redistribute it
 *  and/or modify it under the terms of the Do What the Fuck You Want
 *  to Public License, Version 2, as published by Sam Hocevar. See
 *  http://www.wtfpl.net/ for more details.
 */

#include "kernel.h"
#include "klibc.h"
#include "timer.h"

u32 ticks = 0;

void timer_phase(int hz)
{
    unsigned int divisor = 1193180 / hz;   /* Calculate our divisor */
    /*
      0x43 is the Mode/Command register

     From http://wiki.osdev.org/Programmable_Interval_Timer#Read_Back_Status_Byte :
     Bits         Usage
     6 and 7      Select channel :
                  0 0 = Channel 0
                  0 1 = Channel 1
                  1 0 = Channel 2
                  1 1 = Read-back command (8254 only)
     4 and 5      Access mode :
                  0 0 = Latch count value command
                  0 1 = Access mode: lobyte only
                  1 0 = Access mode: hibyte only
                  1 1 = Access mode: lobyte/hibyte
     1 to 3       Operating mode :
                  0 0 0 = Mode 0 (interrupt on terminal count)
                  0 0 1 = Mode 1 (hardware re-triggerable one-shot)
                  0 1 0 = Mode 2 (rate generator)
                  0 1 1 = Mode 3 (square wave generator)
                  1 0 0 = Mode 4 (software triggered strobe)
                  1 0 1 = Mode 5 (hardware triggered strobe)
                  1 1 0 = Mode 2 (rate generator, same as 010b)
                  1 1 1 = Mode 3 (square wave generator, same as 011b)
     0            BCD/Binary mode: 0 = 16-bit binary, 1 = four-digit BCD

     */
    unsigned short command = 0b00110110;
    outb(0x43, command);
    outb(0x40, divisor & 0xFF);            /* Set low byte of divisor */
    outb(0x40, divisor >> 8);              /* Set high byte of divisor */
}
