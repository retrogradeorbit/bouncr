#include "display.h"

#include <Adafruit_RGBLCDShield.h>

static const char *menu_items[] = {
  "duty-cycle ",
  "frequency ",
  "intensity "
};

extern Adafruit_RGBLCDShield lcd;

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
