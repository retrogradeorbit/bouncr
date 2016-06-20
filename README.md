Resonant Baby Auto Rocker
=========================

I was bouncing my bub in her baby bouncer and thought "there has to be
a better way to keep bub bouncing than to sit here and manually do
it." At first I thought about some mechanical linkage to bounce the
chair, but then later in the shower the idea came to me.

A wire hoop baby bouncer is an underdamped simple harmonic
oscillator. Simple harmonic oscillators have a resonant frequency. As
the force driving the system to osciallate approaches the resonant
frequency, the energy transfer becomes very efficient, and a small
input results in a large bounce.

[Wikipedia](https://en.wikipedia.org/wiki/Harmonic_oscillator#Sinusoidal_driving_force)
[Wolfram Math World](http://mathworld.wolfram.com/UnderdampedSimpleHarmonicMotion.html)

As the frequency of the stimulus goes higher or lower than the
resonant frequency, the applied force actually starts to dampen the
oscillations, rather than increase them.

![Sinusoidal Driving Force](https://upload.wikimedia.org/wikipedia/commons/thumb/7/77/Mplwp_resonance_zeta_envelope.svg/600px-Mplwp_resonance_zeta_envelope.svg.png)

If I could measure the bounce frequency of chair + bub, then I could
drive an oscillator at that frequency and that should make the chair
bounce.

Because it would be driven at the ideal frequency, I shouldn't need to
push against anything. All I would need is a reaction mass attached to
the oscillation mechanism. Every action has an equal and opposite
reaction, so as the mechanism pushed the weight down, the chair would
rise up, and visa versa.

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

Pictures of the prototype

Parts
=====

Todo

Construction
============

Mechanical and circuit build guide

Software
========

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
