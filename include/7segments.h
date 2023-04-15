#include <stdint.h>

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

const uint8_t segments7_base_anod;
const uint8_t segments7_num_of_segments;

struct RP {uint8_t *registry; uint8_t pin;};

// INTERFACES
void show_stick(const struct RP *stick);
void hide_stick(const struct RP *stick);
void activate_segment(const struct RP *seg);
void deactivate_segment(const struct RP *seg);
void deactivate_all_segments();
void clear_segment();
void show_num(uint8_t n, const struct RP *seg);
