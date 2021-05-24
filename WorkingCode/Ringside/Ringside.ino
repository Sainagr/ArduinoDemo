#include <Adafruit_NeoPixel.h>
#include <HT16K33.h>
#include <Wire.h>

// Pix Ring
#define NEOPIX_PIN 12
#define STRIPSIZE 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, NEOPIX_PIN, NEO_GRBW + NEO_KHZ800);

// 7-Segment display
HT16K33 seg(0x70);
int numDis = 0;

// DC Motors
#define L298N_IN1 3
#define L298N_IN2 4
#define L298N_IN3 7
#define L298N_IN4 8
#define L298N_ENA 5
#define L298N_ENB 6

// Blue BUtton
bool pressed = false;
int b = 0;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  // Pix Ring
  strip.begin();
  strip.setBrightness(10);
  // Motor
  pinMode(L298N_IN1, OUTPUT);
  pinMode(L298N_IN2, OUTPUT);
  pinMode(L298N_IN3, OUTPUT);
  pinMode(L298N_IN4, OUTPUT);
  pinMode(L298N_ENA, OUTPUT);
  pinMode(L298N_ENA, OUTPUT);
  // 7-seg
  seg.begin();
  Wire.setClock(100000);
  seg.displayOn();
  seg.brightness(4);
  seg.displayClear();
  seg.blink(0);
  seg.setDigits(4);
  // Led Matrix
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


  // 1 Dc motor
  if(c[1]) {
    pressed = true;
    b = 255;
  } else {
    pressed = false;
    b = 0;
  }

  // 0 Neopixel Strip
  strip.clear();
  for(int i=0;i<12;i++) {
        strip.setPixelColor(i, 0 ,0,b);
      } 
  switch(c[0]) {
    case 0: 
      strip.setPixelColor(0, 255,0,b);
      break;
    case 1: 
      strip.setPixelColor(1, 255,0,b);
      strip.setPixelColor(2, 255,0,b);
      break;
    case 2: 
      strip.setPixelColor(3, 255,0,b);
      break; 
    case 3: 
      strip.setPixelColor(4, 255,0,b);
      strip.setPixelColor(5, 255,0,b);
      break; 
    case 4: 
      strip.setPixelColor(6, 255,0,b);
      break;
    case 5: 
      strip.setPixelColor(7, 255,0,b);
      strip.setPixelColor(8, 255,0,b);
      break;
    case 6: 
      strip.setPixelColor(9, 255,0,b);
      break;
    case 7: 
      strip.setPixelColor(10, 255,0,b);
      strip.setPixelColor(11, 255,0,b);
      break;
    default:
//      for(int i=0;i<12;i++) {
//        strip.setPixelColor(i, 0 ,0,b);
//      } 
      break;    
  }
  strip.show();

  // 2 7-seg
  c[2]-=48;
  if(c[2]>=0){
    if(numDis>=1000){
      numDis = (numDis%1000)*10+c[2];
    } else {
      numDis = numDis*10+c[2];
    }   
    // Serial.println(numDis);
  }
  seg.displayInt(numDis);

  // DC Motors
  int dcPower = numDis/50 + 55;
  analogWrite(L298N_ENA, dcPower); // don't go under 50
  analogWrite(L298N_ENB, dcPower);
  switch(c[0]) {
    case 0: 
      digitalWrite(L298N_IN1, HIGH);
      digitalWrite(L298N_IN2, LOW);
      digitalWrite(L298N_IN3, LOW);
      digitalWrite(L298N_IN4, LOW);
      break;
    case 1: 
      digitalWrite(L298N_IN1, HIGH);
      digitalWrite(L298N_IN2, LOW);
      digitalWrite(L298N_IN3, LOW);
      digitalWrite(L298N_IN4, HIGH);
      break;
    case 2: 
      digitalWrite(L298N_IN1, LOW);
      digitalWrite(L298N_IN2, LOW);
      digitalWrite(L298N_IN3, LOW);
      digitalWrite(L298N_IN4, HIGH);
      break; 
    case 3: 
      digitalWrite(L298N_IN1, LOW);
      digitalWrite(L298N_IN2, HIGH);
      digitalWrite(L298N_IN3, LOW);
      digitalWrite(L298N_IN4, HIGH);
      break; 
    case 4: 
      digitalWrite(L298N_IN1, LOW);
      digitalWrite(L298N_IN2, HIGH);
      digitalWrite(L298N_IN3, LOW);
      digitalWrite(L298N_IN4, LOW);
      break;
    case 5: 
      digitalWrite(L298N_IN1, LOW);
      digitalWrite(L298N_IN2, HIGH);
      digitalWrite(L298N_IN3, HIGH);
      digitalWrite(L298N_IN4, LOW);
      break;
    case 6: 
      digitalWrite(L298N_IN1, LOW);
      digitalWrite(L298N_IN2, LOW);
      digitalWrite(L298N_IN3, HIGH);
      digitalWrite(L298N_IN4, LOW);
      break;
    case 7: 
      digitalWrite(L298N_IN1, HIGH);
      digitalWrite(L298N_IN2, LOW);
      digitalWrite(L298N_IN3, HIGH);
      digitalWrite(L298N_IN4, LOW);
      break;
    default:
      digitalWrite(L298N_IN1, LOW);
      digitalWrite(L298N_IN2, LOW);
      digitalWrite(L298N_IN3, LOW);
      digitalWrite(L298N_IN4, LOW);
  }
  
  delay(100);

}
