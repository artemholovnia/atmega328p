#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bit.h"

extern const struct RP segments7_stick_a;
extern const struct RP segments7_stick_b;
extern const struct RP segments7_stick_c;
extern const struct RP segments7_stick_d;
extern const struct RP segments7_stick_e;
extern const struct RP segments7_stick_f;
extern const struct RP segments7_stick_g;

extern const struct RP segment7_segment_0;
extern const struct RP segment7_segment_1;
extern const struct RP segment7_segment_2;
extern const struct RP segment7_segment_3;

const uint8_t segments7_base_anod = 1;
const uint8_t segments7_num_of_segments = 4;

static struct RP {
    uint8_t *registry;
    uint8_t pin;
};

void show_stick(const struct RP *stick) {
    set_n_bit(stick->registry, 1, stick->pin);
    
    uint8_t * port;
    if (stick->registry == &DDRB) port = &PORTB;
    if (stick->registry == &DDRC) port = &PORTC;
    if (stick->registry == &DDRD) port = &PORTD;
    set_n_bit(port, segments7_base_anod == 1, stick->pin);

};

void hide_stick(const struct RP *stick) {
    set_n_bit(stick->registry, 0, stick->pin);

    uint8_t * port;
    if (stick->registry == &DDRB) port = &PORTB;
    if (stick->registry == &DDRC) port = &PORTC;
    if (stick->registry == &DDRD) port = &PORTD;
    set_n_bit(port, 0, stick->pin);
};

void activate_segment(const struct RP *seg) {
    set_n_bit(seg->registry, 1, seg->pin);
    
    uint8_t * port;
    if (seg->registry == &DDRB) port = &PORTB;
    if (seg->registry == &DDRC) port = &PORTC;
    if (seg->registry == &DDRD) port = &PORTD;
    set_n_bit(port, segments7_base_anod == 0, seg->pin);
};

void deactivate_segment(const struct RP *seg) {
    set_n_bit(seg->registry, 0, seg->pin);
    
    uint8_t * port;
    if (seg->registry == &DDRB) port = &PORTB;
    if (seg->registry == &DDRC) port = &PORTC;
    if (seg->registry == &DDRD) port = &PORTD;
    set_n_bit(port, 0, seg->pin);
};

void deactivate_all_segments(){
  deactivate_segment(&segment7_segment_0);
  deactivate_segment(&segment7_segment_1);
  deactivate_segment(&segment7_segment_2);
  deactivate_segment(&segment7_segment_3);
};

void clear_segment() {
    uint8_t i;
    struct RP *sticks[7] = {
      &segments7_stick_a, &segments7_stick_b, &segments7_stick_c, &segments7_stick_d,
      &segments7_stick_e, &segments7_stick_f, &segments7_stick_g
    };
    for (i=0; i<(sizeof(sticks)/sizeof(sticks[0])); i++) {
      struct RP *stick = sticks[i];
      set_n_bit(stick->registry, 0, stick->pin);

      if (segments7_base_anod == 1) {
        uint8_t * port;
        if (stick->registry == &DDRB) port = &PORTB;
        if (stick->registry == &DDRC) port = &PORTC;
        if (stick->registry == &DDRD) port = &PORTD;
        set_n_bit(port, 0, stick->pin);
      }
    }
};

void show_num(uint8_t n, const struct RP *seg) {
  const struct RP *nums[10][7] = {
    {&segments7_stick_a, &segments7_stick_b, &segments7_stick_c, &segments7_stick_d, &segments7_stick_e, &segments7_stick_f},
    {&segments7_stick_b, &segments7_stick_c},
    {&segments7_stick_a, &segments7_stick_b, &segments7_stick_d, &segments7_stick_e, &segments7_stick_g},
    {&segments7_stick_a, &segments7_stick_b, &segments7_stick_c, &segments7_stick_d, &segments7_stick_g},
    {&segments7_stick_b, &segments7_stick_c, &segments7_stick_f, &segments7_stick_g},
    {&segments7_stick_a, &segments7_stick_c, &segments7_stick_d, &segments7_stick_f, &segments7_stick_g},
    {&segments7_stick_a, &segments7_stick_c, &segments7_stick_d, &segments7_stick_e, &segments7_stick_f, &segments7_stick_g},
    {&segments7_stick_a, &segments7_stick_b, &segments7_stick_c},
    {&segments7_stick_a, &segments7_stick_b, &segments7_stick_c, &segments7_stick_d, &segments7_stick_e, &segments7_stick_f, &segments7_stick_g},
    {&segments7_stick_a, &segments7_stick_b, &segments7_stick_c, &segments7_stick_d, &segments7_stick_f, &segments7_stick_g},
  };

  clear_segment();
  deactivate_all_segments();
  activate_segment(seg);

  uint8_t i;
  for (i=0; i<sizeof(nums[n])/sizeof(nums[n][0]); i++) {
    show_stick(nums[n][i]);
  }
};

