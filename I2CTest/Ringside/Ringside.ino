#include <Adafruit_NeoPixel.h>
#include <HT16K33.h>
#include <Wire.h>

// Pix Ring
#define NEOPIX_PIN 11
#define STRIPSIZE 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, NEOPIX_PIN, NEO_GRBW + NEO_KHZ800);

// 7-Segment display
HT16K33 seg(0x70);
int numDis = 0;

#define DCMOTOR_PIN 10

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  // Pix Ring
  strip.begin();
  strip.setBrightness(10);
  // Motor placeholder
  pinMode(DCMOTOR_PIN, OUTPUT);
  // 7-seg
  seg.begin();
  Wire.setClock(100000);
  seg.displayOn();
  seg.brightness(2);
  seg.displayClear();
  seg.blink(0);
  seg.setDigits(4);
}

void loop() {
  Wire.requestFrom(8, 3);    // request 6 bytes from slave device #8

  int c[3]; // DEVICE_COUNT
  int i = 0;
  while (Wire.available()) { // slave may send less than requested
    c[i] = Wire.read(); // receive a byte as character
    //Serial.print(c[i]); 
    //Serial.print(' ');
    i++;
  }
  //Serial.println();

  // 0 Neopixel Strip
  strip.clear();
  switch(c[0]) {
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

  // 1 Dc motor
  if(c[1]) {
    digitalWrite(DCMOTOR_PIN, HIGH);
  } else {
    digitalWrite(DCMOTOR_PIN, LOW);
  }

  // 2 7-seg
  c[2]-=48;
  if(c[2]>=0){
    if(numDis>=1000){
      numDis = (numDis%1000)*10+c[2];
    } else {
      numDis = numDis*10+c[2];
    }   
    Serial.println(numDis);
  }
  seg.displayInt(numDis);
  
  delay(100);
}
