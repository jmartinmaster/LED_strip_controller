/*
   **Changelog 0.4**

   **ToDo**
          pinFader(){} Now supports mode 5 Split rainbow
          setup speedStrip for speed select / atrip select

    ** NOTE **
         Version 0.4 should have RGB analog input faders
*/
int analogPins[6] = {A0, A1, A2, A3, A4, A5};
int pins[4][5];
int pins2[4][5];
volatile int mode = 0;
int ssdelay = 0;
int interpin = 2;
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
  x = 4;
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

  pinMode(interpin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interpin), interFunction, LOW);
  Serial.begin(19200);
}

void speedStrip() {
  if (mode == 4 || mode == 5 || mode == 6) {
    if (analogRead(A5) > 268 || analogRead(A5) < 0) {
      ssdelay = 5;
    }
    //Set the mode based on analog read from pin 5
    if (analogRead(A4) > 0 && analogRead(A4) < 20) {
      ssdelay = 20;
    }
    if (analogRead(A4) > 20 && analogRead(A4) < 30) {
      ssdelay = 70;
    }
    if (analogRead(A4) > 30 && analogRead(A4) < 40) {
      ssdelay = 80;
    }
    if (analogRead(A4) > 40 && analogRead(A4) < 60) {
      ssdelay = 100;
    }
    if (analogRead(A4) > 60 && analogRead(A4) < 80) {
      ssdelay = 130;
    }
    if (analogRead(A4) > 80 && analogRead(A4) < 100) {
      ssdelay = 160;
    }
    if (analogRead(A4) > 100 && analogRead(A4) < 120) {
      ssdelay = 200;
    }
    if (analogRead(A4) > 120 && analogRead(A4) < 140) {
      ssdelay = 250;
    }
    if (analogRead(A4) > 140 && analogRead(A4) < 160) {
      ssdelay = 300;
    }
    if (analogRead(A4) > 160 && analogRead(A4) < 190) {
      ssdelay = 350;
    }
    if (analogRead(A4) > 190 && analogRead(A4) < 220) {
      ssdelay = 400;
    }
    if (analogRead(A4) > 220 && analogRead(A4) < 240) {
      ssdelay = 600;
    }
    if (analogRead(A4) > 240 && analogRead(A4) < 268) {
      ssdelay = 800;
    }
    if (analogRead(A4) > 268 && analogRead(A4) < 280) {
      ssdelay = 850;
    }
    if (analogRead(A4) > 280 && analogRead(A4) < 290) {
      ssdelay = 875;
    }
    if (analogRead(A4) > 290 && analogRead(A4) < 300) {
      ssdelay = 900;
    }
    if (mode == 5 || mode == 4 ) {
      int x = 0;
      do {
        ssdelay = ssdelay / 30;
        x++;
      } while (x < 1);
    }

  }
  if (mode == 0 || mode == 1 || mode == 2 || mode == 3 ) {
    if (analogRead(A4) < 125) {
      ssdelay = 1;
    }
    if (analogRead(A4) > 125) {
      ssdelay = 2;
    }
  }
  //Serial.println(ssdelay);
}
void rAD() {
  //analogAverage(pin);
  //catch anything out of bounds for mode select
  if (analogRead(A5) > 300 || analogRead(A5) < 63) {
    mode = 0;
  }
  //Set the mode based on analog read from pin 5
  if (analogRead(A5) > 24 && analogRead(A5) < 70) {
    mode = 0;
  }
  if (analogRead(A5) > 70 && analogRead(A5) < 100) {
    mode = 1;
  }
  //if (analogRead(A5) > 80 && analogRead(A5) < 100) {
  //  mode = 2;
  //}
  //if (analogRead(A5) > 100 && analogRead(A5) < 120) {
  //  mode = 3;
  //}
  if (analogRead(A5) > 100 && analogRead(A5) < 150) {
    mode = 4;
  }
  if (analogRead(A5) > 150 && analogRead(A5) < 190) {
    mode = 5;
  }
  if (analogRead(A5) > 190 && analogRead(A5) < 300) {
    mode = 6;
  }


  //pin A4 for speed/split color selector

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
  // Serial.println(" Average 1 ");
  //Serial.print(average);

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

  //Serial.print(" Average 2 ");
  //Serial.print(average);

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

  //Serial.print(" Average 3 ");
  //Serial.print(average);

  analogWrite(pins[0][1], pins[3][1]);
  analogWrite(pins[0][2], pins[3][2]);
  analogWrite(pins[0][3], pins[3][3]);
  analogWrite(pins2[0][1], pins2[3][1]);
  analogWrite(pins2[0][2], pins2[3][2]);
  analogWrite(pins2[0][3], pins2[3][3]);
}

//Fade pins to preset value (Rainbow effect)
void pinFaderM5(int pin, int value) {
  if (pin == 1 || pin == 2 || pin == 3) {
    if (pins[3][pin] < value) {
      do {
        pins[3][pin] = pins[3][pin] + pins[1][pin];
        // Serial.print(" Pin 1 increase " );
        // Serial.println(pin);
        if (pins[3][pin] > 255) {
          pins[3][pin] = 255;
        }
        analogWrite(pins[0][pin], pins[3][pin]);
        speedStrip();
        delay(ssdelay);
      } while (pins[3][pin] < value);
    }
    if (pins[3][pin] > value) {
      do {
        pins[3][pin] = pins[3][pin] - pins[1][pin];
        // Serial.print(" Pin 1 decrease " );
        // Serial.println(pin);
        if (pins[3][pin] < 0 ) {
          pins[3][pin] = 0;
        }
        analogWrite(pins[0][pin], pins[3][pin]);
        speedStrip();
        delay(ssdelay);
      } while (pins[3][pin] > value);
    }
    // Serial.println(pin);
    // Serial.println(" Stuck ");
    if (pin == 4) {
      pin = 1;
    }
  } if (pin == 5) {
    pin = 2;
  }
  if (pin == 6) {
    pin = 3;
  }
  // Serial.println(pin);
  do {
    pins2[3][pin] = pins2[3][pin] + pins2[1][pin];
    // Serial.print(" Pin 1 " );
    // Serial.println(pin);
    if (pins2[3][pin] > 255) {
      pins2[3][pin] = 255;
    }
    analogWrite(pins2[0][pin], pins2[3][pin]);
    speedStrip();
    delay(ssdelay);
  } while (pins2[3][pin] < value);
  if (pins2[3][pin] > value) {
    do {
      pins2[3][pin] = pins2[3][pin] - pins2[1][pin];
      // Serial.print(" Pin 2 " );
      //Serial.println(pin);
      if (pins2[3][pin] < 0 ) {
        pins2[3][pin] = 0;
      }
      analogWrite(pins2[0][pin], pins2[3][pin]);
      speedStrip();
      delay(ssdelay);
    } while (pins2[3][pin] > value);
  }

  //Serial.println(" Out ");
}
void pinFader(int pin, int value) {
  if (pins[3][pin] < value) {
    do {
      pins[3][pin] = pins[3][pin] + pins[1][pin];
      // Serial.println(" Pin 1 increase " );
      if (pins[3][pin] > 255) {
        pins[3][pin] = 255;
      }
      analogWrite(pins[0][pin], pins[3][pin]);
      speedStrip();
      delay(ssdelay);
    } while (pins[3][pin] < value);
  }
  if (pins[3][pin] > value) {
    do {
      pins[3][pin] = pins[3][pin] - pins[1][pin];
      // Serial.println(" Pin 1 decrease " );
      if (pins[3][pin] < 0 ) {
        pins[3][pin] = 0;
      }
      analogWrite(pins[0][pin], pins[3][pin]);
      speedStrip();
      delay(ssdelay);
    } while (pins[3][pin] > value);
  }
  do {
    pins2[3][pin] = pins2[3][pin] + pins2[1][pin];
    //Serial.println(" Pin 2 increase " );
    if (pins2[3][pin] > 255) {
      pins2[3][pin] = 255;
    }
    analogWrite(pins2[0][pin], pins2[3][pin]);
    speedStrip();
    delay(ssdelay);
  } while (pins2[3][pin] < value);
  if (pins2[3][pin] > value) {
    do {
      pins2[3][pin] = pins2[3][pin] - pins2[1][pin];
      // Serial.println(" Pin 2 decrease " );
      if (pins2[3][pin] < 0 ) {
        pins2[3][pin] = 0;
      }
      analogWrite(pins2[0][pin], pins2[3][pin]);

      speedStrip();
      delay(ssdelay);
    } while (pins2[3][pin] > value);
  }
}

//can change both(linked) LED strip colors given a selector
void rGBSolidSeperateOne(int stripSelect) {

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
  speedStrip();
  pins[3][3] = average;
  analogWrite(pins[0][1], pins[3][1]);
  analogWrite(pins[0][2], pins[3][2]);
  analogWrite(pins[0][3], pins[3][3]);
}
void rGBSolidSeperateTwo(int stripSelect) {

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
  pins2[3][1] = average;

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
  pins2[3][2] = average;

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
  speedStrip();
  pins2[3][3] = average;
}
void interFunction() {
  if (mode = ! 7) {
    mode = 7;
    
  }
  if (mode == 7) {
    rAD();
  }
  Serial.println(" Interupt ");
  Serial.print(digitalRead(A2));
  analogWrite(11, 255);
  analogWrite(3, 255);
  analogWrite(10, 255);
  analogWrite(5, 255);
  analogWrite(9, 255);
  analogWrite(6, 255);
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
  Serial.print( " ssdelay ");
  Serial.print(ssdelay);
  Serial.print(" mode " );
  Serial.print( mode);
  Serial.print(" interpin ");
  Serial.println(digitalRead(interpin));
  rAD();
  if (mode == 7) {
    delay(2000);
  }

  if (mode == 0) {
    rGBSolid(0);
  }
  if (mode == 1) {
    speedStrip();
    if (ssdelay == 1) {
      rGBSolidSeperateOne(ssdelay);
    }
    if (ssdelay == 2) {
      rGBSolidSeperateTwo(ssdelay);
    }

    analogWrite(pins2[0][1], pins2[3][1]);
    analogWrite(pins2[0][2], pins2[3][2]);
    analogWrite(pins2[0][3], pins2[3][3]);
  }
  if (mode == 2) {

  }
  if (mode == 3) {

  }

  if (mode == 4) {
    //rainbow effect
    pinFader(1, 0); //Red
    speedStrip();
    pinFader(2, 0); //green
    speedStrip();
    pinFader(3, 255);  //blue
    speedStrip();
    pinFader(3, 0);  //blue
    speedStrip();
    pinFader(1, 255); //red
    speedStrip();
    pinFader(2, 255); //green
    speedStrip();
    pinFader(2, 0); //green
    speedStrip();
    pinFader(1, 0); //red
    speedStrip();
    pinFader(3, 255);  //blue
    speedStrip();
    pinFader(2, 255); //red
    speedStrip();
    pinFader(3, 0);  //blue
    speedStrip();
    rAD();
  }

  if (mode == 5) {
    pinFaderM5(1, 0); //Red
    speedStrip();
    pinFaderM5(4, 255); //Red
    speedStrip();
    pinFaderM5(2, 0); //green
    speedStrip();
    pinFaderM5(5, 255); //green
    speedStrip();
    pinFaderM5(3, 255);  //blue
    speedStrip();
    pinFaderM5(6, 0);  //blue
    speedStrip();
    pinFaderM5(3, 0);  //blue
    speedStrip();
    pinFaderM5(6, 255);  //blue
    speedStrip();
    pinFaderM5(1, 255); //red
    speedStrip();
    pinFaderM5(4, 0); //red
    speedStrip();
    pinFaderM5(2, 255); //green
    speedStrip();
    pinFaderM5(5, 0); //green
    speedStrip();
    pinFaderM5(2, 0); //green
    speedStrip();
    pinFaderM5(5, 255); //green
    speedStrip();
    pinFaderM5(1, 0); //red
    speedStrip();
    pinFaderM5(4, 255); //red
    speedStrip();
    pinFaderM5(3, 255);  //blue
    speedStrip();
    pinFaderM5(6, 0);  //blue
    speedStrip();
    pinFaderM5(2, 255); //red
    speedStrip();
    pinFaderM5(5, 0); //red
    speedStrip();
    pinFaderM5(3, 0);  //blue
    speedStrip();
    pinFaderM5(6, 255);  //blue
    speedStrip();

    rAD();
  }


  if (mode == 6) {
    //Hard rainbow
    analogWrite(11, 0);
    analogWrite(3, 0);
    speedStrip();
    delay(ssdelay);
    analogWrite(10, 0);
    analogWrite(5, 0);
    speedStrip();
    delay(ssdelay);
    analogWrite(11, 255);
    analogWrite(3, 255);
    speedStrip();
    delay(ssdelay);
    analogWrite(9, 0);
    analogWrite(6, 0);
    speedStrip();
    delay(ssdelay);
    analogWrite(10, 255);
    analogWrite(5, 255);
    speedStrip();
    delay(ssdelay);
    analogWrite(11, 0);
    analogWrite(3, 0);
    speedStrip();
    delay(ssdelay);
    analogWrite(9, 255);
    analogWrite(6, 255);
    speedStrip();
    rAD();
  }

}
