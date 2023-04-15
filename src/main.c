/*
avrdude -F -V -c arduino -p atmega328p -P  /dev/cu.usbserial-0001 -b 57600 -U flash:w:build/main.hex
*/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "7segments.h"
#include <util/delay.h>

#define F_CPU 1000000UL // 1 MHz

const struct RP segments7_stick_a = {&DDRB, PB2};
const struct RP segments7_stick_b = {&DDRB, PB3};
const struct RP segments7_stick_c = {&DDRD, PD6};
const struct RP segments7_stick_d = {&DDRB, PB0};
const struct RP segments7_stick_e = {&DDRD, PD7};
const struct RP segments7_stick_f = {&DDRB, PB4};
const struct RP segments7_stick_g = {&DDRD, PD5};

const struct RP segment7_segment_0 = {&DDRC, PC2};
const struct RP segment7_segment_1 = {&DDRB, PB5};
const struct RP segment7_segment_2 = {&DDRC, PC0};
const struct RP segment7_segment_3 = {&DDRC, PC1};

int main() {
    
   deactivate_segment(&segment7_segment_0);
   deactivate_segment(&segment7_segment_1);
   deactivate_segment(&segment7_segment_2);
   deactivate_segment(&segment7_segment_3);

   while (1) {
    show_num(0, &segment7_segment_0);
    show_num(1, &segment7_segment_1);
    show_num(2, &segment7_segment_2);
    show_num(3, &segment7_segment_3);
   }

    return 0;
}