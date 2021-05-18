#include <Wire.h>

#define I2C_ADD 8
// 0: joystick

// Wiring: ground, pins[0], pins[1], pin[2], pin[3]
int jsPins[] = {2,3,4,5};


void setup() {
  Serial.begin(9600);
  
  Wire.begin(I2C_ADD);
  Wire.onRequest(requestEvent); // register event

  // Joystick pins
  for(int i=0; i<4; i++) {
    pinMode(jsPins[i], INPUT);
  }
  
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  int i2cVal[1];

  // Read Joystick Neutral:8, clockwise:0-7
  i2cVal[0] = 8;
  bool jsReadings[4];
  for(int i=0; i<4; i++) {
    jsReadings[i] = digitalRead(jsPins[i]) == LOW;
  }

   if(jsReadings[2]&&!jsReadings[1]) {
    if(jsReadings[0]) {
      i2cVal[0] = 1;
    } else{
      i2cVal[0] = 0;
    }   
  } else if(jsReadings[0]) {
    if(jsReadings[3]) {
      i2cVal[0] = 3;
    } else{
      i2cVal[0] = 2;
    }   
  } else if(jsReadings[3]) {
    if(jsReadings[1]) {
      i2cVal[0] = 5;
    } else{
      i2cVal[0] = 4;
    }   
  } else if(jsReadings[1]) {
    if(jsReadings[2]) {
      i2cVal[0] = 7;
    } else{
      i2cVal[0] = 6;
    }   
  }

  //Serial.println(i2cVal[0]);
  Wire.write(i2cVal[0]);
}
