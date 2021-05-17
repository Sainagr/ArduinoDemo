#include <Adafruit_NeoPixel.h>

#define PIN 11
#define STRIPSIZE 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRBW + NEO_KHZ800);

int jsPins[] = {2,3,4,5};
bool jsReadings[4];

void setup() {
  strip.begin();
  strip.setBrightness(10);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
  
  // Joystick pins
  for(int i=0; i<4; i++) {
    pinMode(jsPins[i], INPUT);
  }

  Serial.begin(9600);
}

void read4WayJs() {
  // Wiring: ground, pins[0], pins[1], pin[2], pin[3]
  // digitalRead == LOW -> direction triggered 
  for(int i=0; i<4; i++) {
    jsReadings[i] = digitalRead(jsPins[i]) == LOW;
  }
}


void loop() {
  read4WayJs();
  strip.clear();
  
  if(jsReadings[2]&&!jsReadings[1]) {
    if(jsReadings[0]) {
      strip.setPixelColor(1, 255,0,0);
      strip.setPixelColor(2, 255,0,0);
    } else{
      strip.setPixelColor(0, 255,0,0);
    }   
  } else if(jsReadings[0]) {
    if(jsReadings[3]) {
      strip.setPixelColor(4, 255,0,0);
      strip.setPixelColor(5, 255,0,0);
    } else{
      strip.setPixelColor(3, 255,0,0);
    }   
  } else if(jsReadings[3]) {
    if(jsReadings[1]) {
      strip.setPixelColor(7, 255,0,0);
      strip.setPixelColor(8, 255,0,0);
    } else{
      strip.setPixelColor(6, 255,0,0);
    }   
  } else if(jsReadings[1]) {
    if(jsReadings[2]) {
      strip.setPixelColor(10, 255,0,0);
      strip.setPixelColor(11, 255,0,0);
    } else{
      strip.setPixelColor(9, 255,0,0);
    }   
  }
  strip.show();
  
  for(int i=0; i<4; i++) {
    if(jsReadings[i]) {
      Serial.print(i);
    }     
  }
  Serial.println(); 
  delay(100);
}
