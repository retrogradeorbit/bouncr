#include "window.h"

float window[SMOOTHING_WINDOW_SIZE];

void window_clear() {
  // initialise data smoothing window to zeros
  for(int n=0; n<SMOOTHING_WINDOW_SIZE; ++n)
    window[n] = 0.0;
}

void window_move_down() {
  for(int n=0; n<SMOOTHING_WINDOW_SIZE-1; ++n)
    window[n] = window[n+1];
}

float window_sum() {
  float sum=0;
  for(int n=0; n<SMOOTHING_WINDOW_SIZE; ++n)
    sum += window[n];
  return sum;
}

float window_average() {
  return window_sum()/SMOOTHING_WINDOW_SIZE;
}

void window_set_end(float data) {
  window[SMOOTHING_WINDOW_SIZE-1] = data;
}
