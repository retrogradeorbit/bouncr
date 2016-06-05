BOARD_TAG    = leonardo
MONITOR_PORT = /dev/ttyACM0
ARDUINO_LIBS = Wire Adafruit_LIS3DH Adafruit_Sensor SPI

include ../Arduino-Makefile/Arduino.mk

flash:
	python leo-kicker.py $(MONITOR_PORT)
	make upload

console:
	screen $(MONITOR_PORT)
