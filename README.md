Resonant Baby Auto Rocker
=========================

I was bouncing my bub in her baby bouncer and thought "there has to be
a better way to keep bub bouncing than to sit here and manually do
it." At first I thought about some mechanical linkage to bounce the
chair, but then later in the shower the idea came to me.

A wire hoop baby bouncer is an underdamped simple harmonic
oscillator. Simple harmonic oscillators have a resonant frequency. As
the force driving the system to oscillation approaches the resonant
frequency, the energy transfer becomes very efficient, and a small
input results in a large bounce.

[Wikipedia](https://en.wikipedia.org/wiki/Harmonic_oscillator#Sinusoidal_driving_force)
[Wolfram Math World](http://mathworld.wolfram.com/UnderdampedSimpleHarmonicMotion.html)

As the frequency of the stimulus goes higher or lower than the
resonant frequency, the applied force actually starts to dampen the
oscillations, rather than increase them.

![Sinusoidal Driving Force](https://upload.wikimedia.org/wikipedia/commons/thumb/7/77/Mplwp_resonance_zeta_envelope.svg/600px-Mplwp_resonance_zeta_envelope.svg.png)

If I could measure the resonant frequency of the chair + bub aggregate,
then I could drive an oscillator at that frequency and that should
make the chair bounce.

To measure the resonant frequency I would need an accelerometer. And
then I could drive oscillations with some kind of electromagnetic
transducer.

Because it would be driven at the ideal frequency, I shouldn't need to
push against anything fixed. All I would need is a reaction mass
attached to the oscillation mechanism and free to move. Every action
has an equal and opposite reaction, so as the mechanism pushed the
weight down, the chair would rise up, and visa versa.

The oscillation of the reaction mass could be driven by a stepper
motor or a solenoid. I decided to go down the stepper motor route for
a finer level of control, but on a later version I may try a solenoid
to bounce a counter weight.

I had a quick browse of patents for automatic baby bouncers and I
could not see this idea of a resonant counterweight method described
anywhere. As such I am hereby releasing this invention into the public
domain for anyone to use. The underlying idea and the invention are
public domain.  The software to control the unit is released under the
GPL v3 license.

Pictures
========

Pictures of the prototype.

Parts
=====

 - Arduino Leonardo
 - LIS3DH Triple-Axis Accelerometer
 - 16x2 LCD + Keypad Kit
 - NEMA-17 Stepper Motor
 - TB6612 1.2A Dual H-Bridge
 - Large bullclip
 - Cable Ties
 - Pair of mini locking pliers (aka multigrips)
 - 12V Switch Mode DC power supply

You can but the Arduino straight from arduino themselves or you local
hobby supply store. Most of the other parts as well as bread boards
and wiring I got from Adafruit. The following are links to the parts I
purchased for my unit:

 - [Adafruit TB6612 1.2A DC/Stepper Motor Driver Breakout Board](https://www.adafruit.com/products/2448)
 - [Adafruit Blue&White 16x2 LCD+Keypad Kit for Raspberry Pi](https://www.adafruit.com/products/1115)
 - [Stepper motor - NEMA-17 size - 200 steps/rev, 12V 350mA](https://www.adafruit.com/products/324)
 - [Adafruit LIS3DH Triple-Axis Accelerometer (+-2g/4g/8g/16g)](https://www.adafruit.com/products/2809)
 - [12 VDC 1000mA regulated switching power adapter - UL listed](https://www.adafruit.com/products/798)

Construction
============

Mechanical and circuit build guide to come.

Software
========

Clone this project as a sibling directory to Arduino-Makefile. You can clone Arduino-Makefile from here: https://github.com/sudar/Arduino-Makefile

At this point you should have two directories side by side. `bouncr` and `Arduino-Makefile`. Change directory into `bouncr` and issue the build commands.

To build the firmware image go:

```
make ARDUINO_LIB_PATH=./libraries
```

To flash the arduino with the firmware:

```
make flash ARDUINO_LIB_PATH=./libraries
```

To connect to the debug port over usb:

```
make console ARDUINO_LIB_PATH=./libraries
```

Operation
=========

The `select` button changes the mode between measure and osciallate.

Measure
-------

Put the unit in this mode and with the child in the chair, gentle
bounce the chair naturally with your hand. As each bounce occurs the
unit will display the frequency on the display. Make note of that
frequency.

Oscillate
---------

Switch the unit to oscillate and navigate the menus with the up and
down arrow keys. Use the left and right keys to change the highlighted
value.

### Frequency ###

Set the frequency of oscillation here.

### Intensity ###

Apon startup, intensity is set to 0 and the unit does not
oscillate. Use this setting to gradually increase intensity until the
bouncing matches the baby's desires. Value ranges from 0 to 50.

### Duty Cycle ###

Select the duty cycle for the oscillation. Values are `100%`,
`50%`, `33%` and `25%`.

Bugs
----

Numerous bugs are still present because this is highly beta still.

Also soon to be fixed:

 * Duty cycle calculation is wrong
 * Unit doesn't remember it's settings on poweroff
 * Measure mode has to be switched on in firmware
