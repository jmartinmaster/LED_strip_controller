//set up analog inputs and have them print

int analogPins[6] = {A0, A1, A2, A3, A4, A5};
int pins[4] = {8, 9, 10, 11};
int pinFV[4] = {random(5, 10), random(5, 10), random(5, 10), random(5, 10)};
int pinDelay[4] = {random(50, 70), random(50, 70), random(50, 70), random(50, 70)};
int pinV[4] = {255, 255, 255, 255};
int mode = 0;
void setup() {
  int x = 6;
  do {
    pinMode(analogPins[x], INPUT);
    x--;
  } while (x > 0);
  int pins[4] = {9, 5, 6, 3};
  x = 4;
  do {
    pinMode(pins[x], INPUT);
    x--;
  } while (x > 0);
  pinMode(8, OUTPUT);
  Serial.begin(19200);
}
void readAnalogDecode(int pin) {
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
  digitalWrite(8, LOW);

  if (pinV[pin] < value) {
    do {
      pinV[pin] = pinV[pin] + pinFV[pin];
      if (pinV[pin] > 255) {
        pinV[pin] = 255;
      }
      Serial.println(analogRead(A5));
      Serial.println(" ");
      Serial.println(analogRead(A4));
      analogWrite(pins[pin], pinV[pin]);
      digitalWrite(8, LOW);
      delay(pinDelay[pin]);
    } while (pinV[pin] < value);
  }
  if (pinV[pin] > value) {
    do {
      pinV[pin] = pinV[pin] - pinFV[pin];
      if (pinV[pin] < 0 ) {
        pinV[pin] = 0;
      }
      digitalWrite(8, LOW);
      analogWrite(pins[pin], pinV[pin]);
      delay(pinDelay[pin]);
    } while (pinV[pin] > value);
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
  readAnalogDecode(A5);

  if (mode == 0) {
    pinFader(1, 255); //no green
    pinFader(2, 255); //no red
    pinFader(1, 0); //green on
    pinFader(3, 255); //no blue
    pinFader(2, 0);   //red on
    pinFader(1, 255); //no green
    pinFader(3, 0);   //blue on
    pinFader(1, 0);   //green on
    readAnalogDecode(A5);
  }
  if (mode == 1) {
    analogWrite(9, 0);
    delay(500);
    analogWrite(9, 255);
    delay(500);
    analogWrite(10, 0);
    delay(500);
    analogWrite(10, 255);
    delay(500);
    analogWrite(11, 0);
    delay(500);
    analogWrite(11, 255);
    delay(500);
    readAnalogDecode(A5);
  }
}
