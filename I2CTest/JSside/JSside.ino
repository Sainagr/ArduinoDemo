#include <Wire.h>
#include <Keypad.h>

#define DEVICE_COUNT 3

#define I2C_ADD 8
#define BLUEBUT_PIN 6

// For Keypad
const byte ROWS = 4; 
const byte COLS = 3; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {7,8,9,10}; 
byte colPins[COLS] = {11,12,13}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


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

  // Blue button pin
  pinMode(BLUEBUT_PIN, INPUT);
  
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  int i2cVal[DEVICE_COUNT];

  // 0 Read Joystick Neutral:8, clockwise:0-7
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

  //1 Read blue button
  if(digitalRead(BLUEBUT_PIN) == LOW) {
    i2cVal[1] = 1;
  } else {
    i2cVal[1] = 0;
  }

  //2 Read Keypad
  int customKey = customKeypad.getKey(); // 48-57:0-9
  i2cVal[2] = 0;
  if (customKey){
    // Serial.println(customKey);
    i2cVal[2] = customKey;
  }
  
  Serial.println(i2cVal[2]);

  for(int i=0; i<DEVICE_COUNT; i++){
    Wire.write(i2cVal[i]);
  }
  
}
