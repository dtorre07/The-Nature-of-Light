#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;




#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN1            6
#define PIN2            7
#define PIN3            8



// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      2

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);



int potPinR = A0;
int potValueR = 0;
int outputValueR = 0;

int potPinY = A1;
int potValueY = 0;
int outputValueY = 0;

int potPinB = A2;
int potValueB = 0;
int outputValueB = 0;

int pinOneTouch = 0;
int pinTwoTouch = 0;
int pinThreeTouch = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");




  pixels1.begin(); // This initializes the NeoPixel library.
  pixels2.begin(); // This initializes the NeoPixel library.
  pixels3.begin(); // This initializes the NeoPixel library.



  pixels1.setBrightness(250);
  pixels2.setBrightness(250);
  pixels3.setBrightness(250);


  //0-255
  pinMode(potPinR, INPUT);
  pinMode(potPinB, INPUT);
  pinMode(potPinY, INPUT);


}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.


  potValueR = analogRead(potPinR);
  outputValueR = map(potValueR, 0, 1023, 0, 255);

  potValueB = analogRead(potPinB);
  outputValueB = map(potValueB, 0, 1023, 0, 255);

  potValueY = analogRead(potPinY);
  outputValueY = map(potValueY, 0, 1023, 0, 255);



  //Serial.println(potValueR);

  // Get the currently touched pads
  currtouched = cap.touched();

  if ((currtouched & _BV(1)) && !(lasttouched & _BV(1)) ) {
    //Serial.println("1 touched");
    pinOneTouch++;
    Serial.println(pinOneTouch);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(1)) && (lasttouched & _BV(1)) ) {
    Serial.println("1 released");
  }

  if ((currtouched & _BV(4)) && !(lasttouched & _BV(4)) ) {
    // Serial.println("4 touched");
    pinTwoTouch++;
    Serial.println(pinTwoTouch);

    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels2.setPixelColor(i, pixels2.Color(255, 255, 255)); // Moderately bright green color.
      pixels2.setBrightness(250);
      pixels2.show(); // This sends the updated pixel color to the hardware.



    }
  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(4)) && (lasttouched & _BV(4)) ) {
    //Serial.println("4 released");
  }


  if ((currtouched & _BV(7)) && !(lasttouched & _BV(7)) ) {
    //Serial.println("7 touched");
    pinThreeTouch++;
    Serial.println(pinThreeTouch);

    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels3.setPixelColor(i, pixels3.Color(255, 255, 255)); // Moderately bright green color.
      pixels3.setBrightness(250);
      pixels3.show(); // This sends the updated pixel color to the hardware.



    }
  }



  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(7)) && (lasttouched & _BV(7)) ) {
    // Serial.println("7 released");
  }
  // reset our state
  lasttouched = currtouched;


  if ((pinOneTouch % 2) - 0 == 0) {
    Serial.println("White");

    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels1.setPixelColor(i, pixels1.Color(255, 255, 255)); // Moderately bright green color.

      pixels1.show(); // This sends the updated pixel color to the hardware.

    }
  }
  if ((pinOneTouch % 2) - 1 == 0) {
    Serial.println("Red");
    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels1.setPixelColor(i, pixels1.Color(outputValueR, 0, 0)); // Moderately bright green color.

      pixels1.show(); // This sends the updated pixel color to the hardware.
    }
  }


    if ((pinTwoTouch % 2) - 0 == 0) {
    Serial.println("White");

    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels2.setPixelColor(i, pixels2.Color(255, 255, 255)); // Moderately bright green color.
  
      pixels2.show(); // This sends the updated pixel color to the hardware.

    }
  }
  if ((pinTwoTouch % 2) - 1 == 0) {
    Serial.println("Yellow");
    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels2.setPixelColor(i, pixels2.Color(outputValueY, outputValueY, 0)); // Moderately bright green color.
      
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
  }

    if ((pinThreeTouch % 2) - 0 == 0) {
    Serial.println("White");

    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels3.setPixelColor(i, pixels3.Color(255, 255, 255)); // Moderately bright green color.

      pixels3.show(); // This sends the updated pixel color to the hardware.

    }
  }
  if ((pinThreeTouch % 2) - 1 == 0) {
    Serial.println("Blue");
    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels3.setPixelColor(i, pixels3.Color(0, 0, outputValueB)); // Moderately bright green color.
      pixels3.setBrightness(250);
      pixels3.show(); // This sends the updated pixel color to the hardware.
    }
  }

  // comment out this line for detailed data from the sensor!
  return;

  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();

  // put a delay so it isn't overwhelming
  delay(100);



}
