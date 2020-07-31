/*
   Changelog 0.2
   pins[], pinFV[], pinV[], pinDelay[] moved
   to pins[][];
   changed readAnalogDecode() to rAD();
   altered the rainbow (mode 0) if(){} statement;
*/
int analogPins[6] = {A0, A1, A2, A3, A4, A5};
int pins[4][4];
int mode = 0;
void setup() {
  pins[0][0] = 8;
  pins[0][1] = 10;
  pins[0][2] = 11;
  pins[0][3] = 9;
  int x = 6;
  do {
    pinMode(analogPins[x], INPUT);
    x--;
  } while (x > 0);
  x = 4;
  do {
    pinMode(pins[0][x], INPUT);
    x--;
  } while (x > 0);
  x = 4;
  do {
    pins[1][x] = random(5, 10);
    x--;
  } while (x > 0);
  x = 4;
  do {
    pins[2][x] = random(50, 75);
    x--;
  } while (x > 0);
  x = 4;
  do {
    pins[3][x] = 255;
    x--;
  } while (x > 0);
  pinMode(8, OUTPUT);
  analogWrite(8, 255);
  Serial.begin(19200);
}
void rAD() {
  //analogAverage(pin);
  //elseIf statements to set what mode to use
  //catch anything out of bounds for mode select
  if (analogRead(A5) > 800 || analogRead(A5) < 0) {
    mode = 0;
  }
  if (analogRead(A5) > 4 && analogRead(A5) < 8) {
    mode = 0;
  }
  if (analogRead(A5) > 8 && analogRead(A5) < 15) {
    mode = 1;
  }
  if (analogRead(A5) > 15 && analogRead(A5) < 20) {
    mode = 2;
  }
  if (analogRead(A5) > 20 && analogRead(A5) < 26) {
    mode = 3;
  }
  if (analogRead(A5) > 26 && analogRead(A5) < 47) {
    mode = 4;
  }
  if (analogRead(A5) > 47 && analogRead(A5) < 185) {
    mode = 5;
  }
  if (analogRead(A5) > 185 && analogRead(A5) < 345) {
    mode = 6;
  }
}

void pinFader(int pin, int value) {

  if (pins[3][pin] < value) {
    do {
      pins[3][pin] = pins[3][pin] + pins[1][pin];
      if (pins[3][pin] > 255) {
        pins[3][pin] = 255;
      }
      Serial.println(analogRead(A5));
      Serial.println(" ");
      Serial.println(analogRead(A4));
      analogWrite(pins[0][pin], pins[3][pin]);
      delay(pins[2][pin]);
    } while (pins[3][pin] < value);
  }
  if (pins[3][pin] > value) {
    do {
      pins[3][pin] = pins[3][pin] - pins[1][pin];
      if (pins[3][pin] < 0 ) {
        pins[3][pin] = 0;
      }
      analogWrite(pins[0][pin], pins[3][pin]);
      delay(pins[2][pin]);
    } while (pins[3][pin] > value);
  }
}
void loop() {
  Serial.println(" " );
  Serial.print(analogRead(A0));
  Serial.print(" " );
  Serial.print(analogRead(A1));
  Serial.print(" " );
  Serial.print(analogRead(A2));
  Serial.print(" " );
  Serial.print(analogRead(A3));
  Serial.print(" " );
  Serial.print(analogRead(A4));
  Serial.print(" " );
  Serial.print(analogRead(A5));
  Serial.print(" " );
  Serial.print(mode);
  rAD();

  if (mode == 0) {
    pinFader(1, 0); //Red
    pinFader(2, 0); //green
    pinFader(3, 255);  //blue
    pinFader(3, 0);  //blue
    pinFader(1, 255); //red
    pinFader(2, 255); //green
    pinFader(2, 0); //green
    pinFader(1, 0); //red
    pinFader(3, 255);  //blue
    pinFader(2, 255); //red
    pinFader(3, 0);  //blue

    rAD();
  }
  if (mode == 1) {
    analogWrite(11, 0);
    delay(250);
    analogWrite(10, 0);
    delay(250);
    analogWrite(11, 255);
    delay(250);
    analogWrite(9, 0);
    delay(250);
    analogWrite(10, 255);
    delay(250);
    analogWrite(11, 0);
    delay(250);
    analogWrite(9, 255);
    rAD();
  }
}
