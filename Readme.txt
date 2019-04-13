Here is an Arduino based Nitrox anlyzer I recently made. It uses an Arduino Nano, an ADS1115 ADC, and a 0.96" I2C OLED display. It uses the PSR-11-39-JD O2 sensor from Analytical Industries which is vheap and readily available. This is loosely based on this one: https://ejlabs.net/arduino-oled-nitrox-analyzer/ But the code was too complex for me, so I decided to write my own simpler code and display the actual sensor reading in mV as a final check (because I am obsessive about knowing what lies under the hood) .

It auto calibrates at startup and has on-demand calibration via a push-button. I decided not to store calibration values after power off as a safety precaution. It has gone through several iterations and ended up with the sensor and sampler built-in but with an external port. It is powered by an 18650 cell which can be charged via a micro USB port. It uses ~25 mA at full draw.

Here I think is the most critical aspect of this project - getting the right parts/components so I put it in the readme file.

Parts list:
Arduino Nano or clone
ADS1115 16 Bit ADC
0.96" I2C Monochrome 128 x 64 OLED Display (ADS 1306 controller clone)
NO Push button switch
Latching power switch
Oxygen sensor (PSR-11-39-JD)

Libraries 
Running Average by Rob Tillaart
ADS1015
Adafruit_SSD1306
Wire (Included in the IDE)

Sampler:
1" PVC end cap with drilled center 1.2 mm hole and 4 x 1/8" side holes
