/*
   **Changelog 0.3**

   **ToDo**
          Setup a catch method
          Setup analogAverage(aA(){})
          Setup additional analog input for delays/speed control

    ** NOTE **
         Version 0.4 should have RGB analog input faders
         Mode selector set to change. New hardwear inbound
*/
int analogPins[6] = {A0, A1, A2, A3, A4, A5};
int pins[4][5];
int pins2[4][5];
int mode = 0;
void setup() {
  pins[0][1] = 10;
  pins[0][2] = 11;
  pins[0][3] = 9;
  pins2[0][1] = 3;
  pins2[0][2] = 5;
  pins2[0][3] = 6;
  int x = 6;
  do {
    pinMode(analogPins[x], INPUT);
    x--;
  } while (x > 0);
  x = 5;
  do {
    pinMode(pins[0][x], INPUT);
    pinMode(pins2[0][x], INPUT);
    x--;
  } while (x > 0);
  x = 4;
  do {
    pins[1][x] = random(1, 5);
    pins2[1][x] = random(1, 5);
    x--;
  } while (x > 0);
  x = 4;
  do {
    pins[2][x] = random(50, 75);
    pins2[2][x] = random(50, 75);
    x--;
  } while (x > 0);
  x = 4;
  do {
    pins[3][x] = 255;
    pins2[3][x] = 255;
    x--;
  } while (x > 0);
  Serial.begin(19200);
}


void rAD() {
  //analogAverage(pin);
  //catch anything out of bounds for mode select
  if (analogRead(A5) > 622 || analogRead(A5) < 63) {
    mode = 0;
  }
  //Set the mode based on analog read from pin 5
  if (analogRead(A5) > 63 && analogRead(A5) < 70) {
    mode = 0;
  }
  if (analogRead(A5) > 70 && analogRead(A5) < 80) {
    mode = 1;
  }
  if (analogRead(A5) > 80 && analogRead(A5) < 100) {
    mode = 2;
  }
  if (analogRead(A5) > 100 && analogRead(A5) < 120) {
    mode = 3;
  }
  if (analogRead(A5) > 120 && analogRead(A5) < 150) {
    mode = 4;
  }
  if (analogRead(A5) > 150 && analogRead(A5) < 190) {
    mode = 5;
  }
  if (analogRead(A5) > 190 && analogRead(A5) < 280) {
    mode = 6;
  }
}

//holds a single color for both strips
void rGBSolid(int cycleNumber) {
  if (cycleNumber == 0) {
    int x = 4;
    do {
      pins[3][x] = 255;
      pins2[3][x] = 255;
      x--;
    } while (x > 0);
  }
  int x = 50;
  int average = 0;
  do {
    average = average + analogRead(A0);
    x--;
  } while (x > 0);
  average = average / 50;
  if (average > 255) {
    average = 255;
  }
  if (average < 0) {
    average = 0;
  }
  pins[3][1] = average;
  pins2[3][1] = average;
  Serial.println(" Average 1 ");
  Serial.print(average);

  x = 50;
  average = 0;
  do {
    average = average + analogRead(A1);
    x--;
  } while (x > 0);
  average = average / 50;
  if (average > 255) {
    average = 255;
  }
  if (average < 0) {
    average = 0;
  }
  pins[3][2] = average;
  pins2[3][2] = average;

  Serial.print(" Average 2 ");
  Serial.print(average);

  x = 50;
  average = 0;
  do {
    average = average + analogRead(A2);
    x--;
  } while (x > 0);
  average = average / 50;
  if (average > 255) {
    average = 255;
  }
  if (average < 0) {
    average = 0;
  }
  pins[3][3] = average;
  pins2[3][3] = average;

  Serial.print(" Average 3 ");
  Serial.print(average);

  analogWrite(pins[0][1], pins[3][1]);
  analogWrite(pins[0][2], pins[3][2]);
  analogWrite(pins[0][3], pins[3][3]);
  analogWrite(pins2[0][1], pins[3][1]);
  analogWrite(pins2[0][2], pins[3][2]);
  analogWrite(pins2[0][3], pins[3][3]);
}

//Fade pins to preset value (Rainbow effect)
void pinFader(int pin, int value) {
  if (mode == 5) {
    if (pin == 1 || pin == 2 || pin == 3) {
      if (pins[3][pin] < value) {
        do {
          pins[3][pin] = pins[3][pin] + pins[1][pin];
          Serial.println(" Pin 1 increase " );
          if (pins[3][pin] > 255) {
            pins[3][pin] = 255;
          }
          analogWrite(pins[0][pin], pins[3][pin]);
          delay(pins[2][pin]);
        } while (pins[3][pin] < value);
      }
      if (pins[3][pin] > value) {
        do {
          pins[3][pin] = pins[3][pin] - pins[1][pin];
          Serial.println(" Pin 1 decrease " );
          if (pins[3][pin] < 0 ) {
            pins[3][pin] = 0;
          }
          analogWrite(pins[0][pin], pins[3][pin]);
          delay(pins[2][pin]);
        } while (pins[3][pin] > value);
      }
      if (pin == 4) {
        pin = 1;
      }
    } if (pin == 5) {
      pin = 2;
    }
    if (pin == 6) {
      pin = 3;
    }
    do {
      pins2[3][pin] = pins2[3][pin] + pins2[1][pin];
      Serial.println(" Pin 2 increase " );
      if (pins2[3][pin] > 255) {
        pins2[3][pin] = 255;
      }
      analogWrite(pins2[0][pin], pins[3][pin]);
      delay(pins2[2][pin]);
    } while (pins2[3][pin] < value);
    if (pins2[3][pin] > value) {
      do {
        pins2[3][pin] = pins2[3][pin] - pins2[1][pin];
        Serial.println(" Pin 2 decrease " );
        if (pins2[3][pin] < 0 ) {
          pins2[3][pin] = 0;
        }
        analogWrite(pins2[0][pin], pins2[3][pin]);
        delay(pins2[2][pin]);
      } while (pins2[3][pin] > value);
    }
  }

  if (mode = ! 5) {
    if (pins[3][pin] < value) {
      do {
        pins[3][pin] = pins[3][pin] + pins[1][pin];
        Serial.println(" Pin 1 increase " );
        if (pins[3][pin] > 255) {
          pins[3][pin] = 255;
        }
        analogWrite(pins[0][pin], pins[3][pin]);
        delay(pins[2][pin]);
      } while (pins[3][pin] < value);
    }
    if (pins[3][pin] > value) {
      do {
        pins[3][pin] = pins[3][pin] - pins[1][pin];
        Serial.println(" Pin 1 decrease " );
        if (pins[3][pin] < 0 ) {
          pins[3][pin] = 0;
        }
        analogWrite(pins[0][pin], pins[3][pin]);
        delay(pins[2][pin]);
      } while (pins[3][pin] > value);
    }
    do {
      pins2[3][pin] = pins2[3][pin] + pins2[1][pin];
      Serial.println(" Pin 2 increase " );
      if (pins2[3][pin] > 255) {
        pins2[3][pin] = 255;
      }
      analogWrite(pins2[0][pin], pins[3][pin]);
      delay(pins2[2][pin]);
    } while (pins2[3][pin] < value);
    if (pins2[3][pin] > value) {
      do {
        pins2[3][pin] = pins2[3][pin] - pins2[1][pin];
        Serial.println(" Pin 2 decrease " );
        if (pins2[3][pin] < 0 ) {
          pins2[3][pin] = 0;
        }
        analogWrite(pins2[0][pin], pins2[3][pin]);
        delay(pins2[2][pin]);
      } while (pins2[3][pin] > value);
    }
  }
}

//can change both(linked) LED strip colors given a selector
void rGBSolidSeperate(int cycleNumber) {
  if (cycleNumber == 0) {
    int x = 4;
    do {

      pins[3][x] = 255;
      pins2[3][x] = 255;
      x--;
    } while (x > 0);
  }
  int x = 50;
  int average = 0;
  do {
    average = average + analogRead(A0);
    x--;
  } while (x > 0);
  average = average / 50;
  if (average > 255) {
    average = 255;
  }
  if (average < 0) {
    average = 0;
  }
  pins[3][1] = average;
  pins2[3][1] = average;
  Serial.println(" Average 1 ");
  Serial.print(average);

  x = 50;
  average = 0;
  do {
    average = average + analogRead(A1);
    x--;
  } while (x > 0);
  average = average / 50;
  if (average > 255) {
    average = 255;
  }
  if (average < 0) {
    average = 0;
  }
  pins[3][2] = average;
  pins2[3][2] = average;

  Serial.print(" Average 2 ");
  Serial.print(average);

  x = 50;
  average = 0;
  do {
    average = average + analogRead(A2);
    x--;
  } while (x > 0);
  average = average / 50;
  if (average > 255) {
    average = 255;
  }
  if (average < 0) {
    average = 0;
  }
  pins[3][3] = average;
  pins2[3][3] = average;

  Serial.print(" Average 3 ");
  Serial.print(average);

  analogWrite(pins[0][1], pins[3][1]);
  analogWrite(pins[0][2], pins[3][2]);
  analogWrite(pins[0][3], pins[3][3]);
  analogWrite(pins2[0][1], pins[3][1]);
  analogWrite(pins2[0][2], pins[3][2]);
  analogWrite(pins2[0][3], pins[3][3]);
}

//Main loop to chose mode behavor
void loop() {

  Serial.println(" ");
  Serial.print(" A0 " );
  Serial.print(analogRead(A0));
  Serial.print(" A1 " );
  Serial.print(analogRead(A1));
  Serial.print(" A2 " );
  Serial.print(analogRead(A2));
  Serial.print(" A3 " );
  Serial.print(analogRead(A3));
  Serial.print(" A4 " );
  Serial.print(analogRead(A4));
  Serial.print(" A5 " );
  Serial.print(analogRead(A5));
  Serial.print(" mode " );
  Serial.print( mode);
  rAD();

  if (mode == 0) {

  }
  if (mode == 1) {

  }
  if (mode == 2) {

  }
  if (mode == 3) {

  }

  if (mode == 4) {
    //rainbow effect moved to 4
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

  if (mode == 5) {
    pinFader(1, 0); //Red
    pinFader(4, 255); //Red
    pinFader(2, 0); //green
    pinFader(5, 255); //green
    pinFader(3, 255);  //blue
    pinFader(6, 0);  //blue
    pinFader(3, 0);  //blue
    pinFader(6, 255);  //blue
    pinFader(1, 255); //red
    pinFader(4, 0); //red
    pinFader(2, 255); //green
    pinFader(5, 0); //green
    pinFader(2, 0); //green
    pinFader(5, 255); //green
    pinFader(1, 0); //red
    pinFader(4, 255); //red
    pinFader(3, 255);  //blue
    pinFader(6, 0);  //blue
    pinFader(2, 255); //red
    pinFader(5, 0); //red
    pinFader(3, 0);  //blue
    pinFader(6, 255);  //blue
  }


  if (mode == 6) {
    //Hard rainbow moved to 6
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
