//
// Bouncer Resonant Autorocker
//

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Stepper.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

#include "window.h"
#include "daccel.h"
#include "rocker.h"
#include "display.h"
#include "pins.h"

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
Stepper motor(STEPPER_MOTOR_STEPS_PER_REV,
	      STEPPER_MOTOR_PIN1,
	      STEPPER_MOTOR_PIN2,
	      STEPPER_MOTOR_PIN3,
	      STEPPER_MOTOR_PIN4);

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

void setup() {
  // Debugging output
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("  Baby Bouncer  ");
  lcd.setCursor(0,1);
  lcd.print("  version 0.1   ");
  lcd.setBacklight(1);

  motor.setSpeed(60);

  delay(3000);
}

#define MODE_TEXT_MEASURE   "measure  "
#define MODE_TEXT_OSCILLATE "oscillate"
#define MODE_TEXT_UNKNOWN   "unknown! "

#define MODE_MEASURE 0
#define MODE_OSCILLATE 1

void display_mode(uint8_t mode) {
  lcd.setCursor(6,0);
  lcd.print(mode==MODE_MEASURE?
	    MODE_TEXT_MEASURE:mode==MODE_OSCILLATE?
	    MODE_TEXT_OSCILLATE:MODE_TEXT_UNKNOWN);
}




uint8_t intensity = 0;
uint8_t dutycycle = 1;
float frequency = 1.81;


uint8_t mode=0;
uint8_t menu_item=0;

void initial_menu_value()
{
    switch(menu_item) {

    case MENU_ITEM_DUTYCYCLE:
      display_dutycycle(dutycycle, 5);
      break;

    case MENU_ITEM_FREQUENCY:
      display_frequency(frequency, 4);
      lcd.print("Hz");
      break;

    case MENU_ITEM_INTENSITY:
      display_intensity(intensity, 6);
      break;

    }
}

void loop() {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("mode:");
  display_mode(mode);
  display_menu(menu_item);
  initial_menu_value();

  uint8_t buttons = 0;

  rocker_init();

  while(true) {
    buttons = lcd.readButtons();
    rocker_step(motor, intensity, dutycycle, frequency);

    if(buttons & BUTTON_SELECT) {
      mode = 1-mode;
      display_mode(mode);

      while(buttons & BUTTON_SELECT) {
	buttons = lcd.readButtons();
      }
    }

    if(buttons & BUTTON_UP) {
      menu_item = menu_item==0 ? 0 : menu_item - 1;
      display_menu(menu_item);

      initial_menu_value();

      while(buttons & BUTTON_UP) {
	buttons = lcd.readButtons();
      }
    }

    if(buttons & BUTTON_DOWN) {
      menu_item = menu_item==MENU_ITEM_COUNT ? MENU_ITEM_COUNT : menu_item + 1;
      display_menu(menu_item);

      initial_menu_value();

      while(buttons & BUTTON_DOWN) {
	buttons = lcd.readButtons();
      }
    }

    if(buttons & BUTTON_LEFT) {

      switch(menu_item) {
      case MENU_ITEM_DUTYCYCLE:
	dutycycle = min(4, dutycycle+1);
	display_dutycycle(dutycycle, 4);
	break;

      case MENU_ITEM_INTENSITY:
	intensity = max(0, intensity-1);
	display_intensity(intensity, 2);
	break;

      case MENU_ITEM_FREQUENCY:
	frequency = max(0, frequency-0.01);
	display_frequency(frequency, 4);
	break;
      }

      uint8_t c=16;
      while(buttons & BUTTON_LEFT && c--) {
	buttons = lcd.readButtons();
      }
    }

    if(buttons & BUTTON_RIGHT) {

      switch(menu_item) {
      case MENU_ITEM_DUTYCYCLE:
	dutycycle = max(1, dutycycle-1);
	display_dutycycle(dutycycle, 4);
	break;

      case MENU_ITEM_INTENSITY:
	intensity = min(50, intensity+1);
	display_intensity(intensity, 2);
	break;

      case MENU_ITEM_FREQUENCY:
	frequency = min(10, frequency+0.01);
	display_frequency(frequency, 4);
	break;
      }

      uint8_t c=16;
      while(buttons & BUTTON_RIGHT && c--) {
	buttons = lcd.readButtons();
      }
    }
  }
}
