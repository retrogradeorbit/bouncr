// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Stepper.h>

#include "window.h"
#include "daccel.h"

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif


void measure_setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  Serial.begin(9600);
  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");

  lis.setRange(LIS3DH_RANGE_8_G);   // 2, 4, 8 or 16 G!

  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");

  window_clear();
  daccel_clear();
}



void print_data_point(int n) {
  for(int i=0; i<n; i++)
    Serial.print(" ");
  Serial.println("-=+O0O+=-");
}

// we hand measured this at 5.55
// TODO: create a mode that measures this for us
#define STILL 6.5 //bit of dead area

void measure_loop() {
  static unsigned long last_time=0;
  static unsigned long now=0;
  static int count=0;

  sensors_event_t event;
  lis.getEvent(&event);

  window_move_down();
  window_set_end(event.acceleration.z);

  float amt = window_average()-STILL;
  if(amt>0.0) {
    daccel_move_down();
    daccel_set_end(amt);
    if(daccel_reversed_direction()) {
      count++;
      Serial.print(count);
      Serial.print(" ");
      now=millis();
      double seconds = double(now-last_time)/1000.;
      Serial.print(1.0/seconds);
      Serial.println(" Hz");
      last_time=now;
    }
  }
  else
    daccel_clear();

  delay(15);
}

int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);

void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // this line is for Leonardo's, it delays the serial interface
  // until the terminal window is opened
  // while (!Serial);

  Serial.begin(9600);
  motor.setSpeed(50);
}

#define DELAY 250


void move(int n, int d) {
  unsigned long now= millis();
  motor.step(n);
  Serial.println(millis()-now);
  delay(d-(millis()-now));
}

// float freq=1.92;
float freq=2.2;
float del=500./freq;

void loop()
{
  /* if (Serial.available()) */
  /* { */
  /*   int steps = Serial.parseInt(); */
  /*   motor.step(steps); */
  /* } */
  Serial.println(del);
  move(90, int(del));
  move(-90, int(del));
}
