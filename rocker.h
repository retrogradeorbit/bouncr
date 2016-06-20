#ifndef _ROCKER_H_
#define _ROCKER_H_

#include "Arduino.h"
#include <Stepper.h>

// apply the motor delta for one step
void rocker_delta();
void rocker_set_delta(int8_t d);
void rocker_init();

// state machine step
void rocker_step(Stepper motor, uint8_t intensity, uint8_t dutycycle, float frequency);
void rock(Stepper motor, uint8_t intensity);

#endif
