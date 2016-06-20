#include "rocker.h"

int8_t delta = 0;
unsigned long next_rock = 0;
int8_t last_intensity = 0;

// apply the motor delta for one step
void rocker_delta(Stepper motor)
{
  int8_t dir = delta<0?-1:delta>0?1:0;

  switch(dir) {
  case -1:
    //Serial.println("step");
    motor.step(delta);
    delta=0;
    break;

  case 1:
    //Serial.println("step-1");
    motor.step(-delta);
    delta=0;
    break;
  }
}

void rocker_set_delta(int8_t d)
{
  Serial.println(String("set delta:") + String(d));
  delta = d;
}

void rocker_init()
{
  next_rock = millis();
}

// state machine step
void rocker_step(Stepper motor, uint8_t intensity, uint8_t dutycycle, float frequency)
{
  unsigned long now = millis();

  //Serial.println(String(now) + ", " + String(next_rock));

  if(now>next_rock)
    {
      rock(motor, intensity);
      unsigned long time_delta = int(500./frequency);
      while(next_rock<now)
	next_rock = next_rock + time_delta * (unsigned long)dutycycle;

    }

  //rocker_delta(motor);
}

void rock(Stepper motor, uint8_t intensity)
{
  if(last_intensity<0) {
    last_intensity = intensity;
  } else {
    last_intensity = -intensity;
  }

  motor.step(last_intensity);
}
