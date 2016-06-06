#include "daccel.h"

float daccel[DACCEL_WINDOW_SIZE];

void daccel_clear() {
  // initialise data smoothing daccel to zeros
  for(int n=0; n<DACCEL_WINDOW_SIZE; ++n)
    daccel[n] = 0.0;
}

void daccel_move_down() {
  for(int n=0; n<DACCEL_WINDOW_SIZE-1; ++n)
    daccel[n] = daccel[n+1];
}

void daccel_set_end(float data) {
  daccel[DACCEL_WINDOW_SIZE-1] = data;
}

bool daccel_reversed_direction() {
  return (daccel[0] < daccel[1]) && (daccel[2] < daccel[1]);
}

float daccel_max() {
  return daccel[1];
}
