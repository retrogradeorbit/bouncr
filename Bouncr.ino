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

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11

// Used for hardware & software SPI
#define LIS3DH_CS 10

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

void print_data_point(int n) {
  for(int i=0; i<n; i++)
    Serial.print(" ");
  Serial.println("-=+O0O+=-");
}

// we hand measured this at 5.55
// TODO: create a mode that measures this for us
#define STILL 6.5 //bit of dead area

int in1Pin = 4;
int in2Pin = 5;
int in3Pin = 6;
int in4Pin = 7;

Stepper motor(200, in1Pin, in2Pin, in3Pin, in4Pin);

#define DELAY 500

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  //int time = millis();
  lcd.print("  Baby Bouncer  ");
  lcd.setCursor(0,1);
  lcd.print("  version 0.1   ");
  /* time = millis() - time; */
  /* Serial.print("Took "); Serial.print(time); Serial.println(" ms"); */
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

static const char *menu_items[] = {
  "duty-cycle ",
  "frequency ",
  "intensity ",
  "back-off  "
};

#define MENU_ITEM_COUNT 2

#define MENU_ITEM_DUTYCYCLE 0
#define MENU_ITEM_FREQUENCY 1
#define MENU_ITEM_INTENSITY 2
#define MENU_ITEM_BACKOFF   3

uint8_t intensity = 0;
uint8_t dutycycle = 1;
float frequency = 1.81;

void display_menu(uint8_t num)
{
  lcd.setCursor(0,1);
  lcd.print(menu_items[num]);
}

void display_value(uint8_t x, uint8_t width, const char *str)
{
  lcd.setCursor(x,1);
  lcd.print(str);
  for(int i=0; i<width-(uint8_t)String(str).length(); i++)
    lcd.print(" ");
}

void display_intensity(uint8_t intensity, uint8_t width)
{
  String str(intensity);
  display_value(10, width, str.c_str());
}

void display_frequency(float freq, uint8_t width)
{
  String decimal = String(int(freq*100.) % 100);
  String str(String(int(freq)) + (decimal.length()==1?".0":".") + decimal);

  display_value(10, width, str.c_str());
}

void display_dutycycle(uint8_t delay, uint8_t width)
{
  display_value(11, width,
		delay==1?"100%":
		delay==2?"50%":
		delay==3?"33%":
		"25%");
}



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

    case MENU_ITEM_BACKOFF:
      //display_value(10, 6, "None");
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
