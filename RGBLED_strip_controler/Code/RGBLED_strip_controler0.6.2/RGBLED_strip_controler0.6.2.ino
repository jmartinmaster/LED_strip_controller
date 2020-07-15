//Read from these pins to set speed, brightness,mode and/or color
int analogPins[6] = {A0, A1, A2, A3, A4, A5};
//Pin value holder
/*
 * ***break down of pins[4][5] and pins2[4][5]
   pins[0][0-2] = pin numbers
   pins[1][0-3] = pin fade value (effects the speed that pins fade
   pins[2][*] is being replaced by ssdelay. previously held random delay value for pins/ changed how fast pins would fade
   pins[3][0-3] = pin levels. These hold the initial pin value at first so everything would turn on when first started.
*/
int pins[4][5];
int pins2[4][5];
//holds what mode is set and helps change behavior of the code when running a specific "mode"
volatile int mode = 0;
//used to change speed
int ssdelay = 0;
//interupt pin. interupt might be used to turn controller "off" of "on"
int interpin = 2;
//Pin controling the fountain's power
int fountinpin = 13;
void setup() {
  //assign pin numbers
  pins[0][1] = 10;
  pins[0][2] = 11;
  pins[0][3] = 9;
  pins2[0][1] = 3;
  pins2[0][2] = 5;
  pins2[0][3] = 6;
  int x = 6;
  do {
    //set input pins so we can set mode, color, etc...
    pinMode(analogPins[x], INPUT);
    x--;
  } while (x > 0);
  x = 4;
  do {
    //asign pin mode (input or output)
    //for the LED lights setting input then wrighting to the pins makes them "block" power. This causes the lights to "fade"
    pinMode(pins[0][x], INPUT);
    pinMode(pins2[0][x], INPUT);
    x--;
  } while (x > 0);
  x = 4;
  do {
    //asign random fade value to make it have some variety every time the controler is started
    // might be removed in later versions or set to a constant
    pins[1][x] = random(1, 5);
    pins2[1][x] = random(1, 5);
    x--;
  } while (x > 0);
  x = 4;
  do {
    //delay time between operations. Changes speed of fading.
    //will be removed in later versions, replacing wiht ssdelay
    pins[2][x] = random(50, 75);
    pins2[2][x] = random(50, 75);
    x--;
  } while (x > 0);
  x = 4;
  do {
    // originally set values to turn everything on when code first started.
    //small possability of removing this and leaving a note that 255 is max PWM output
    //
    pins[3][x] = 255;
    pins2[3][x] = 255;
    x--;
  } while (x > 0);
  //raise value of input for mode
  pinMode(interpin, INPUT_PULLUP);
  //attach interpin to interupt so signals will stop the current function and run interupt code
  attachInterrupt(digitalPinToInterrupt(interpin), interFunction, LOW);
  //optional. used for debugging the controler so I know what values to assighn. Same applies to Serial.print methods.
  Serial.begin(19200);
}

void speedStrip() {
  //set the delay based on analog input from A4
  //Do not use the analog input for the delay. delay will not be stable and cannot reach slower speeds.

  //if in mode 4,5,6 use A4 to set delay that is faster when out of bounds
  if (mode == 4 || mode == 5 || mode == 6) {
    //if A4 returns an out of bounds value(not planned) then speed up everything to get next read from input
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

    //when in mode 4 or 5 speed things up so it looks better
    if (mode == 5 || mode == 4 ) {
      int x = 0;
      do {
        //change the 30 to speed up(higher value or slow down(lower value) the fading speed
        ssdelay = ssdelay / 30;
        x++;
      } while (x < 1);
    }

  }
  //when in mode 0,1,2,3 use A4 to change whitch LED strip is controlled
  if (mode == 0 || mode == 1 || mode == 2 || mode == 3 ) {
    if (analogRead(A4) < 125) {
      ssdelay = 1;
    }
    if (analogRead(A4) > 125) {
      ssdelay = 2;
    }
  }
}
void rAD() {
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
  /*modes are unused
    if (analogRead(A5) > 80 && analogRead(A5) < 100) {
     mode = 2;
    }
    if (analogRead(A5) > 100 && analogRead(A5) < 120) {
    mode = 3;
    }
  */
  if (analogRead(A5) > 100 && analogRead(A5) < 150) {
    mode = 4;
  }
  if (analogRead(A5) > 150 && analogRead(A5) < 190) {
    mode = 5;
  }
  if (analogRead(A5) > 190 && analogRead(A5) < 300) {
    mode = 6;
  }
}

//holds a single color for both strips
void rGBSolid(int cycleNumber) {
  //sets values to max value so everything has a base starting point
  //cycle number is used once per call to set everything to be the same
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


  analogWrite(pins[0][1], pins[3][1]);
  analogWrite(pins[0][2], pins[3][2]);
  analogWrite(pins[0][3], pins[3][3]);
  analogWrite(pins2[0][1], pins2[3][1]);
  analogWrite(pins2[0][2], pins2[3][2]);
  analogWrite(pins2[0][3], pins2[3][3]);
}

//Fade pins to preset value (Rainbow effect)
//there are two methods for this as the code was not working when only one method was used with an if() statement
void pinFaderM5(int pin, int value) {
  if (pin == 1 || pin == 2 || pin == 3) {
    if (pins[3][pin] < value) {
      do {
        pins[3][pin] = pins[3][pin] + pins[1][pin];
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
        if (pins[3][pin] < 0 ) {
          pins[3][pin] = 0;
        }
        analogWrite(pins[0][pin], pins[3][pin]);
        speedStrip();
        delay(ssdelay);
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
      if (pins2[3][pin] < 0 ) {
        pins2[3][pin] = 0;
      }
      analogWrite(pins2[0][pin], pins2[3][pin]);
      speedStrip();
      delay(ssdelay);
    } while (pins2[3][pin] > value);
  }

}
//used to fade the pins smoothly instead of a "hard" switch
//Rainbow
void pinFader(int pin, int value) {
  if (pins[3][pin] < value) {
    do {
      pins[3][pin] = pins[3][pin] + pins[1][pin];
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
//method has been devided for each strip to to code not working when one method was used with an if() statement
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

//this is the interupt function called by D2 when signal is received
void interFunction() {
  if (mode = ! 7) {
    mode = 7;

  }
  if (mode == 7) {
    rAD();
  }
  //report an interupt and turn off the lights
  Serial.println(" Interupt ");
  Serial.print(digitalRead(A2));
  analogWrite(11, 255);
  analogWrite(3, 255);
  analogWrite(10, 255);
  analogWrite(5, 255);
  analogWrite(9, 255);
  analogWrite(6, 255);
}

void houseLights( int pin, int value) {
  /*used to control the lights in the houses
    The lights are bi-directional so there are three outputs
    Having one line on will activate the other half the lights

    house lights are on pins 3,5,6
    equivalant to pins2[0][0-2]

  */

  if (pins2[3][pin] < value) {
    do {
      pins2[3][pin] = pins2[3][pin] + pins2[1][pin];
      if (pins2[3][pin] > 255) {
        pins2[3][pin] = 255;
      }
      analogWrite(pins2[0][pin], pins2[3][pin]);
      speedStrip();
      delay(ssdelay);
    } while (pins2[3][pin] < value);
  }
  if (pins2[3][pin] > value) {
    do {
      pins2[3][pin] = pins2[3][pin] - pins2[1][pin];
      if (pins2[3][pin] < 0 ) {
        pins2[3][pin] = 0;
      }
      analogWrite(pins2[0][pin], pins2[3][pin]);
      speedStrip();
      delay(ssdelay);
    } while (pins2[3][pin] > value);
  }

  /*
    The nex if statements watch for invalid pin settings
    If two are at full value the remaining one is turned off.
  */
  if (pins2[3][0] > 254 && pins2[3][1] > 254) {
    pins2[3][2] = 0;
    analogWrite(pins2[0][2], pions2[3][2]);
  }
  if (pins2[3][1] > 254 && pins2[3][2] > 254) {
    pins2[3][0] = 0;
    analogWrite(pins2[0][0], pions2[3][0]);
  }
  if (pins2[3][0] > 254 && pins2[3][2] > 254) {
    pins2[3][1] = 0;
    analogWrite(pins2[0][1], pions2[3][1]);
  }

}

//Controls the TIP120 connected to the fountain. value is on or off.
void fountain() {
  if (digitalRead(fountinpin) == 1) {
    digitalWrite(fountinpin, LOW);
  }
  if (digitalRead(fountinpin) == 0) {
    digitalWrite(fountinpin, HIGH);
  }

}
//Main loop to chose mode behavor
//speedStrip is called often to set the speed at any given point
void loop() {
  //Diagnostic data for checking values on pins A0-A5
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

  //House lights need to be called in every mode.
  //House lights should "ping" from one side to the other.


  //call for mode selection
  rAD();
  if (mode == 7) {
    delay(2000);
  }
  //mode 0 sets both strips to one selectable color
  if (mode == 0) {
    rGBSolid(0);
  }
  // allows both strips to be a differant color
  //will be changed for Christmas setup with a fpuntain and only one LED strip
  if (mode == 1) {
    speedStrip();
    if (ssdelay == 1) {
      rGBSolidSeperateOne(ssdelay);
    }
    if (ssdelay == 2) {
      rGBSolidSeperateTwo(ssdelay);
    }

    //pins did not set value when this was in function above. put it here to fix
    analogWrite(pins2[0][1], pins2[3][1]);
    analogWrite(pins2[0][2], pins2[3][2]);
    analogWrite(pins2[0][3], pins2[3][3]);
  }
  //modes two and three are not used yet
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
    //Dual rainbow.
    //Both LED strips are using the rainbow mode but are differant colors
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
