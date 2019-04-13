/*****************************************************************************
* Pao's universal self-calibrating nitrox analyzer ver 0.4.4 (10 March 2019 21:56 UTC)
*
* License
* -------
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation (version 3 of the License or
*   any later version).
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  (See the
*   GNU General Public License for more details)
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/

//include working libraries
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1015.h>
#include <RunningAverage.h>

//OLED definitions
#define SCREEN_WIDTH 128              // OLED display width, in pixels
#define SCREEN_HEIGHT 64              // OLED display height, in pixels
#define OLED_RESET     1              // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_RESET); //Define OLED display

Adafruit_ADS1115 myADC(0x48); // Define ADC address

#define RA_SIZE 20            //Define running average pool size
RunningAverage RA(RA_SIZE);   //Initialize Running Average

const byte buttonPin = A3;    // Define calibration push button

float currentmv = 0;              //Define ADC reading value
const float multiplier = 0.0625F; //ADC value/bit for gain of 2
const int calCount = 320;         //Calibration samples
const int readDelay = 3;          //ADC read delay between samples
float calValue = 0;               //Calibration value (%/mV)
float percentO2;                  //% O2
byte buttonState;                 //Button state

void setup() {  

	//Serial.begin(9600);       //Start serial port (debugging purposes only)
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   //Start OLED Display
  myADC.setGain(GAIN_TWO);                     //Set ADC gain
  myADC.begin();                               //Start ADC
  pinMode(buttonPin,INPUT_PULLUP);             //Define push button as active low
  
//Startup calibration 
  //display "Calibrating"
   display.clearDisplay();        //CLS
   display.display();             //CLS
   display.setTextColor(WHITE);   //WHITE for monochrome
   display.setTextSize(1);
   display.setCursor(0,0);
   display.println(F("+++++++++++"));
   display.println(F(" START-UP"));
   display.println(F("CALIBRATION"));
   display.println(F("+++++++++++"));
   display.display();
   display.clearDisplay();        //CLS
   
  //Startup calibration
   RA.clear();
   for(int i=0; i<= calCount; i++) 
   {
   float millivolts = 0;
   millivolts = myADC.readADC_Differential_0_1();  //Read differental voltage between ADC pins 0 & 1
   RA.addValue(millivolts);
   delay(readDelay);
   }
  //Compute calValue
   currentmv = RA.getAverage();
   currentmv = currentmv * multiplier;
   calValue = 20.9000/currentmv;
   
   display.display();             //CLS execute
}

void loop() {
//On-demand calibration
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW)
  {
    display.clearDisplay();        //CLS
    display.display();             //CLS
    display.setTextColor(WHITE);   //WHITE for monochrome
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println(F("+++++++++++"));
    display.println(F(" ON-DEMAND"));
    display.println(F("CALIBRATION"));
    display.println(F("+++++++++++"));
    display.display();
    display.clearDisplay();   
    
    for(int i=0; i<= calCount; i++) 
    {
    float millivolts = 0;
    millivolts = myADC.readADC_Differential_0_1();
    RA.addValue(millivolts);
    delay(readDelay);
    }
    currentmv = RA.getAverage();
    currentmv = currentmv * multiplier;
    calValue = 20.900/currentmv;
    
    display.display();
  }
    
  //Running measurement
  RA.clear();
  for(int x=0; x<= RA_SIZE; x++) {
  float millivolts = 0;
  millivolts = myADC.readADC_Differential_0_1();
  RA.addValue(millivolts);
  delay(16);
  //Serial.println(millivolts*multiplier,3);    //mV serial print for debugging
  }

  currentmv = RA.getAverage();
  currentmv = currentmv*multiplier;
  percentO2 = currentmv*calValue;   //Convert mV ADC reading to % O2
  display.clearDisplay();   
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(percentO2,1);
  display.println(" %");
  display.setCursor(0,17);
  display.print(currentmv,2);
  display.println(" mV");
  display.display();
}


  
  
