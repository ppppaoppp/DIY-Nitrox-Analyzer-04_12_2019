# Pao's Universal Self-calibrating Nitrox Analyzer ver. 3.1

Here is an Arduino based Nitrox anlyzer I recently made. It uses an Arduino Nano, an ADS1115 ADC, and a 0.96" I2C OLED display. It uses the PSR-11-39-JD O2 sensor from Analytical Industries which is cheap and readily available. This is loosely based on this [one](https://ejlabs.net/arduino-oled-nitrox-analyzer/) But the code was too complex for me, so I decided to write my own simpler code and display the actual sensor reading in mV as a final check (because I am obsessive about knowing what lies under the hood) .

It auto calibrates at startup and has on-demand calibration via a push-button. I decided not to store calibration values after power off as a safety precaution. It has gone through several iterations and ended up with the sensor and sampler built-in but with an external port. It is powered by an 18650 cell which can be charged via a micro USB port. It uses ~25 mA at full draw.

Here I think is the most critical aspect of this project - getting the right parts/components so I put it in the readme file.

Parts list:

|Part|Notes|US price and link|Aus price and link|
|---|---|---|---|
|Arduino Nano or clone||||
|ADS1115 16 Bit ADC||||
|0.96" I2C Monochrome 128 x 64 OLED Display |(ADS 1306  controller clone)|||
|NO Push button switch||||
|Latching power switch||||
|Oxygen sensor (PSR-11-39-JD)||[$80](https://www.divegearexpress.com/specialty-oxygen-sensors)|[$138.60](https://www.divetekoz.com.au/index.php/divetekoz-online-store/product/18-psr-11-39-jd-oxygen-sensor.html)|

Libraries:

* Running Average by Rob Tillaart
* ADS1015
* Adafruit_SSD1306
* Wire (Included in the IDE)

Sampler:

* 1" PVC end cap with drilled center 1.2 mm hole and 4 x 1/8" side holes

---

## Instructions

> This document is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  (See the GNU General Public License for more details: http://www.gnu.org/licenses/)

### Materials

* Oxygen Sensor: [PSR-11-39-JD](https://www.divegearexpress.com/specialty-oxygen-sensors) $80
* Arduino Nano (get the one with unsoldered pins)
* Analog to Digital Converter 16-bit 4-Channel – ADS1115
* 0.96” 128 x 64 I2C OLED Display
* 5v step-up power module w/ lithium battery charging protection board 134n3p – All in one battery protection and 5V boost converter module [e.g.](https://www.makerlab-electronics.com/product/5v-step-up-power-module-lithium-battery-charging-protection-board-usb-134n3p/) or [e.g.](https://www.amazon.com/Onyehn-Lithium-Battery-Protection-Charger/dp/B07D3SQYKJ/ref=sr_1_2?keywords=5V+Step-Up+Power+Module+Lithium+Battery+Charging+Protection+Board+USB+134N3P&qid=1555124286&s=gateway&sr=8-2). There seems to be two versions, one with a holding current of 20 mA and the other with 50-60 mA, get the 20 mA version or bodge a 150 ohm resistor across the output if you got the 60 mA flavor – there is an alternate method that you can use which I will explain later
* 18650 Lithium battery and holder
* Rocker switch SPST or any latching switch you like
* Push-button switch, NO, non-latching
* 3.5 mm mono jack
* 3.5 mm mono plug
* 3.5 mm mono or stereo Male to Male cord
* Hook-up wire (I prefer 24AWG stranded wire w/ silicone insulator)
* Case – any will do but I like this one: [100 x 68 x 50mm IP65 sealed ABS enclosure with clear top](https://www.amazon.com/gp/product/B07FKN8SZG/ref=ox_sc_act_title_1?smid=A1THAZDOWP300U&psc=1) $7.66
* 1 inch PVC pipe cap (unthreaded)

### Assembly

Only five pins will be used on the Arduino Nano:

* A3 – configured as an input w/ the internal pull-up resistor  enabled
* A4 – I2C Data line (SDA)
* A5 – I2C Clock line (SCL)
* 5V – Supplied via the boost converter
* GND - Ground

I stacked the OLED display and ADC using pin headers and just wired the rest point to point.

* A3 is connected to ground via the NO push-button switch and is used for on demand calibration

    I used short lengths of wire with the insulation stripped at the midpoint to connect the Arduino’s 5v and GND pins to the stacked OLED/ADS1115 VDD and GND pins then connected the other end of the wire to the power switch (5V wire) and push-button (GND wire)

    5V from the boost converter is connected to the other side of the power switch while ground from the boost converter is connected to the ground terminal of the NO pus-button switch (connected to the GND pin of the OLED/ADS1115 and the Arduino)

    The sensor connects via a 3.5 mm jack. The outer connector/sleeve/ring is “+” while the tip/signal/central connector is “-“, reversed from the usual convention.

* AO on the ADS115 is connected to the “ring” or ground side of the 3.5 mm mono plug or jack, respectively

* A1 on the ADS115 is connected to the “tip” or “signal” side of the 3.5 mm mono plug or jack, respectively

Alternate power source if you cannot find the low holding current 5V all in one module:
You can use a USB DC-DC 0.9-5V 600mA Boost Converter connected to a 3V (2 x AA) battery [PFM Control DC-DC Converter Step Up Boost Module 600MA USB Charger 0.9V-5V to 5V Power Supply Modul TE110](https://www.makerlab-electronics.com/product/usb-dc-dc-0-9-5v-600ma-boost-converter/) or [this one](https://www.amazon.com/Control-Converter-Module-Charger-0-9V-5V/dp/B01FDD3AYQ/ref=sr_1_2?keywords=USB+DC-DC+0.9-5V+600mA+Boost+Converter&qid=1555124065&s=gateway&sr=8-2). However, this is an “always on” device so the switch will be placed between the battery and boost converter and the converter will be always connected to the circuit.

### Case

Feel free to use any case you want, the only critical thing is if you can fit all the components in. The sensor uses an oddball M16 x 1 mm metric thread, but a 3/8” NPT thread is a good enough fit.
Sampler:
1” PVC pipe cap drilled with 1 1.2 mm hole at the center and four 1/8” inch at the sides, near the base. Just superglue it over the hole you drilled and tapped for the sensor.

Included as a JPEG file is a Fritzing schematic, minus the power switch.

![Fritzing schematic, minus the power switch](<Pao Nitrox Analyzer Schematic.jpg>)

Enjoy! :-D
