#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define NEOPIX_PIN 11
#define STRIPSIZE 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, NEOPIX_PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  strip.begin();
  strip.setBrightness(10);
}

void loop() {
  Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8

  int c;
  while (Wire.available()) { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }

  // Neopixel Strip
  strip.clear();
  switch(c) {
    case 0: 
      strip.setPixelColor(0, 255,0,0);
      break;
    case 1: 
      strip.setPixelColor(1, 255,0,0);
      strip.setPixelColor(2, 255,0,0);
      break;
    case 2: 
      strip.setPixelColor(3, 255,0,0);
      break; 
    case 3: 
      strip.setPixelColor(4, 255,0,0);
      strip.setPixelColor(5, 255,0,0);
      break; 
    case 4: 
      strip.setPixelColor(6, 255,0,0);
      break;
    case 5: 
      strip.setPixelColor(7, 255,0,0);
      strip.setPixelColor(8, 255,0,0);
      break;
    case 6: 
      strip.setPixelColor(9, 255,0,0);
      break;
    case 7: 
      strip.setPixelColor(10, 255,0,0);
      strip.setPixelColor(11, 255,0,0);
      break;
    default:
      strip.clear();
  }
  strip.show();

  delay(100);
}
