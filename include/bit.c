#include <stdint.h>

void set_n_bit(uint8_t *bits, int bit, int n){
   *bits = (*bits & ~(1<<n)) | (bit<<n);
};