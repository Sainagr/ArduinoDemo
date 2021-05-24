// look at this diagram

int c[6] = {8, 0, 1, 2, 3, 4};
int r[8] = {8, 6, 7, 9, 10, 11, 12, 13};
bool p[7][5] = {
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1}
};

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<6; i++) {
    pinMode(c[i], OUTPUT);
  }
  for(int i=0; i<8; i++) {
    pinMode(r[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // LED Matrix
  
  for(int i=0; i<7; i++) {
    digitalWrite(r[i+1],HIGH);
    for(int j=0; j<5; j++) {
      if(p[i][j]) {
        digitalWrite(c[j+1],LOW);
      }
    }
    delay(1);
    for(int i=0; i<6; i++) {
      digitalWrite(c[i], HIGH);
    }
    for(int i=0; i<8; i++) {
      digitalWrite(r[i], LOW);
    }
  }
//    digitalWrite(c[1],LOW);
//    digitalWrite(r[1],HIGH);
//    delay(20);
}
