#ifndef _DACCEL_H_
#define _DACCEL_H_

#define DACCEL_WINDOW_SIZE 3

void daccel_clear();
void daccel_move_down();
void daccel_set_end(float data);
bool daccel_reversed_direction();
float daccel_max();

#endif
