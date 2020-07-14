/*
 * No longer end goal
 * please see RGBLED_stripcontrolerX.x
 */

int pins[4] = {9, 5, 6, 3};
int pfade[4] = {10, 15, 15, 15};
int pdelay[4] = {10, 20, 20, 20};
int pvalue[4] = {0, 255, 255, 255};
int analogPins[6] = {A0, A1, A2, A3, A4, A5};
int analogvalue[6];
int mode = 0;
int analogScore[6] = {0, 0, 0, 0, 0, 0};
int analogAveragev[6] = {0, 0, 0, 0, 0, 0};
/*
   NOTICE
   When setting values in pvalue always remember to catch pvalue[0]
   so as to not write a number to digital(not PWM) output
*/

void setup() {
  //turn everything on
  int x = 6;
  do {
    pinMode(analogPins[x], INPUT);
    x--;
  } while (x > 0);
  x = 4;
  do {
    pinMode(pins[x], OUTPUT);
    x--;
  } while (x > 0);
  x = 4;
  do {
    analogWrite(pins[x], pvalue[x]);
    x--;
  } while (x > 0);
  x = 6;
  do {
    analogvalue[x] = analogRead(x);
  } while (x > 0);

  x = 6;
  do {
    analogvalue[x] = analogRead(x);
  } while (x > 0);
  Serial.begin(19200);
}
void readAnalogDecode(int pin) {
  analogAverage(pin);
  //elseIf statements to set what mode to use
  //catch anything out of bounds for mode select
  if (analogAveragev[5] > 800 || analogAveragev < 0) {
    mode = 0;
  }
  if (analogAveragev[5] > 4 && analogAveragev[5] < 10) {
    mode = 0;
  }
  if (analogAveragev[5] > 10 && analogAveragev[5] < 15) {
    mode = 1;
  }
  if (analogAveragev[5] > 200 && analogAveragev[5] < 300) {
    mode = 2;
  }
  if (analogAveragev[5] > 300 && analogAveragev[5] < 400) {
    mode = 3;
  }
  if (analogAveragev[5] > 400 && analogAveragev[5] < 500) {
    mode = 4;
  }
  if (analogAveragev[5] > 500 && analogAveragev[5] < 600) {
    mode = 5;
  }
  if (analogAveragev[5] > 700 && analogAveragev[5] < 800) {
    mode = 6;
  }
}
void cob() {
  int x = 4;
  do {
    if (pvalue[x] > 255) {
      pvalue[x] = 255;
    }
    if (pvalue[x] < 0) {
      pvalue[x] = 0;
    }
    x--;
  } while ( x > 0 );
}

void analogAverage(int pin) {
  //average score over 50 values
  int x = 50;
  do {
    analogScore[pin] = analogScore[pin] + analogRead(analogPins[pin]);
    x--;
  } while (x > 0);
  analogScore[pin] = analogScore[pin] / 50;
}

void pinfader(int pin) {
  if (mode == 3) {
    if (pvalue[pin] > analogvalue[pin]) {
      do {
        pvalue[pin] = pvalue[pin] - pfade[pin];
        cob();
        pinSet();
      } while (pvalue[pin] > analogvalue[pin]);
    }
    if (pvalue[pin] < analogvalue[pin]) {
      do {
        pvalue[pin] = pvalue[pin] + pfade[pin];
        cob();
        pinSet();
      } while (pvalue[pin] < analogvalue[pin]);
    }
  }
  else {
    if (pvalue[pin] > analogvalue[pin]) {
      do {
        pvalue[pin] = pvalue[pin] - pfade[pin];
        cob();
        pinSet();
      } while (pvalue[pin] > 0);
    }

    if (pvalue[pin] < analogvalue[pin]) {
      do {
        pvalue[pin] = pvalue[pin] + pfade[pin];
        cob();
        pinSet();
      } while (pvalue[pin] > 0);
    }

  }
}
void pinSet() {
  int x = 4;
  do {
    analogWrite(pins[x], pvalue[x]);
    delay(pdelay[x]);
    printAnalog();
    x--;
  } while ( x > 0);
}
void printAnalog() {
  int x = 6;
  do {
    Serial.println(" " + analogPins[x]);
    x--;
  } while (x > 0);
}
void loop() {
  delay(30);
  Serial.println(" " );
  Serial.print(analogRead(A0));
  Serial.println(" " );
  Serial.print(analogRead(A1));
  Serial.println(" " );
  Serial.print(analogRead(A2));
  Serial.println(" " );
  Serial.print(analogRead(A3));
  Serial.println(" " );
  Serial.print(analogRead(A4));
  Serial.println(" " );
  Serial.print(analogRead(A5));
  //mode 0 solid
  /*
    if (mode == 0) {
      int x = 6;
      do {
        readAnalogDecode(x);
        pinSet();
        x--;
      } while (x > 0);
    }
    //mode 1 pulse/fade
    //one color fade on off
    if (mode == 1) {
      int x = 6;
      do {
        readAnalogDecode(x);
        pinfader(0);
        x--;
      } while (x > 0);
    }
    //mode 2 rainbow solid
    //hard color shifting
    if (mode == 2) {
      int x = 6;
      do {
        readAnalogDecode(x);
        pinSet();
        x--;
      } while (x > 0);
    }
    //mode 3 rainbow fade
    //soft color shifting
    if (mode == 3) {
      int x = 6;
      do {
        readAnalogDecode(x);
        pinSet();
        x--;
      } while (x > 0);
    }
    //mode 4 rainbow pulse
    // pulse on one color off on another color
    if (mode == 4) {
      int x = 6;
      do {
        readAnalogDecode(x);
        pinSet();
        x--;
      } while (x > 0);
    }
    //mode 5 unkown
    if (mode == 5) {
      int x = 6;
      do {
        readAnalogDecode(x);
        pinSet();
        x--;
      } while (x > 0);
    }
    //mode 6 blink one color
    if (mode == 6) {
      int x = 6;
      do {
        readAnalogDecode(x);
        pinSet();
        x--;
      } while (x > 0);
    }
  */
}
