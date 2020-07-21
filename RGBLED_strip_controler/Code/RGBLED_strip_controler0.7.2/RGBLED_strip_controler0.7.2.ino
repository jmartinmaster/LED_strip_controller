//Read from these pins to set speed, brightness,mode and/or color
int analogPins[6] = {A0, A1, A2, A3, A4, A5};
//****this controler only has 4 pointometers****
//****there are two buttons attached to pin D12 and interupt pin D2****
/*
  ***break down of pins[4][5] and houseLights[4][5]
  **MAX VALUE IS 255**
   pins[0][0] = an empty void, used to not change anything when calling some functions(0,0)
   pins[0][1-3] = pin numbers
   pins[1][1-3] = pin fade value (effects the speed that pins fade
   pins[2][*] is being replaced by ssdelay. previously held random delay value for pins/ changed how fast pins would fade
   pins[3][1-3] = pin levels. These hold the initial pin value at first so everything would turn on when first started.
*/
int pins[4][5];
//The bi-directional LED string uses 255 as ON unless all set to 255 then 0 is on
int houseLights[4][5];
//holds what mode is set and helps change behavior of the code when running a specific "mode"
volatile int mode = 0;
//used to change speed
int ssdelay = 0;
//interupt pin. interupt might be used to turn controller "off" or "on"
int interpin = 2;
//Change to interupt funtions to assighn 1 or 0 when differant combination of pins reads as 1 and check for if main loop has ran
volatile int buttonPress = 0;
volatile int buttonPress2 = 0;
//Pin controling the fountain's power
int fountinpin = 13;
//Variable to track houseLights
int housePhase = 0;
void setup() {
  //assign pin numbers
  pins[0][1] = 9;
  pins[0][2] = 10;
  pins[0][3] = 11;
  houseLights[0][1] = 3;
  houseLights[0][2] = 5;
  houseLights[0][3] = 6;
  int x = 6;
  do {
    //set input pins so we can set mode, color, etc...
    pinMode(analogPins[x], INPUT);
    x--;
  }
  while (x > 0);
  x = 4;
  do {
    //asign pin mode (input or output)
    //for the LED lights setting input then wrighting to the pins makes them "block" power. This causes the lights to "fade"
    pinMode(pins[0][x], INPUT);
    pinMode(houseLights[0][x], INPUT);
    x--;
  }
  while (x > 0);
  x = 4;
  do {
    //asign random fade value to make it have some variety every time the controler is started
    // might be removed in later versions or set to a constant
    pins[1][x] = random(1, 5);
    houseLights[1][x] = random(1, 5);
    x--;
  }
  while (x > 0);
  x = 4;
  do {
    //delay time between operations. Changes speed of fading.
    //will be removed in later versions, replacing wiht ssdelay
    pins[2][x] = random(50, 75);
    houseLights[2][x] = random(50, 75);
    x--;
  }
  while (x > 0);
  x = 4;
  //raise value of input for mode
  pinMode(interpin, INPUT);
  //attach interpin to interupt so signals will stop the current function and run interupt code
  attachInterrupt(digitalPinToInterrupt(interpin), interFunction, CHANGE);
  //second button setup, used with pin 2 to activate interupt
  pinMode(12, INPUT);
  //optional. used for debugging the controler so I know what values to assighn. Same applies to Serial.print methods.
  Serial.begin(115200);
}
void speedStrip() {
  //set the delay based on analog input from A4
  //Do not use the analog input for the delay. delay will not be stable and cannot reach slower speeds.
  //if in mode 4,5,6 use A4 to set delay that is faster when out of bounds
  if (mode == 4 || mode == 5 || mode == 6) {
    //if A4 returns an out of bounds value(not planned) then speed up everything to get next read from input
    if (analogRead(analogPins[4]) > 349 || analogRead(analogPins[4]) < 0) {
      ssdelay = 5;
    }
    //Set the mode based on analog read from pin 5
    if (analogRead(analogPins[4]) > 0 && analogRead(analogPins[4]) < 20) {
      ssdelay = 20;
    }
    if (analogRead(analogPins[4]) > 20 && analogRead(analogPins[4]) < 30) {
      ssdelay = 70;
    }
    if (analogRead(analogPins[4]) > 30 && analogRead(analogPins[4]) < 40) {
      ssdelay = 80;
    }
    if (analogRead(analogPins[4]) > 40 && analogRead(analogPins[4]) < 60) {
      ssdelay = 100;
    }
    if (analogRead(analogPins[4]) > 60 && analogRead(analogPins[4]) < 80) {
      ssdelay = 130;
    }
    if (analogRead(analogPins[4]) > 80 && analogRead(analogPins[4]) < 100) {
      ssdelay = 160;
    }
    if (analogRead(analogPins[4]) > 100 && analogRead(analogPins[4]) < 120) {
      ssdelay = 200;
    }
    if (analogRead(analogPins[4]) > 120 && analogRead(analogPins[4]) < 140) {
      ssdelay = 250;
    }
    if (analogRead(analogPins[4]) > 140 && analogRead(analogPins[4]) < 160) {
      ssdelay = 300;
    }
    if (analogRead(analogPins[4]) > 160 && analogRead(analogPins[4]) < 190) {
      ssdelay = 350;
    }
    if (analogRead(analogPins[4]) > 190 && analogRead(analogPins[4]) < 220) {
      ssdelay = 400;
    }
    if (analogRead(analogPins[4]) > 220 && analogRead(analogPins[4]) < 240) {
      ssdelay = 600;
    }
    if (analogRead(analogPins[4]) > 240 && analogRead(analogPins[4]) < 268) {
      ssdelay = 800;
    }
    if (analogRead(analogPins[4]) > 268 && analogRead(analogPins[4]) < 280) {
      ssdelay = 850;
    }
    if (analogRead(analogPins[4]) > 280 && analogRead(analogPins[4]) < 290) {
      ssdelay = 875;
    }
    if (analogRead(analogPins[4]) > 290 && analogRead(analogPins[4]) < 348) {
      ssdelay = 900;
    }
    //when in mode 4 or 5 speed things up so it looks better
    if (mode == 5 || mode == 4 ) {
      int x = 0;
      do {
        //change the 30 to speed up(higher value or slow down(lower value) the fading speed
        ssdelay = ssdelay / 20;
        x++;
      }
      while (x < 1);
    }
  }
  //when in mode 0,1,2,3 use A4 to change whitch LED strip is controlled
  if (mode == 0 || mode == 1 || mode == 2 || mode == 3 ) {
    if (analogRead(analogPins[4]) < 125) {
      ssdelay = 1;
    }
    if (analogRead(analogPins[4]) > 125) {
      ssdelay = 2;
    }
  }
}
void rAD() {
  //catch anything out of bounds for mode select
  if (analogRead(analogPins[5]) > 361 || analogRead(analogPins[5]) < 63) {
    mode = 0;
  }
  //Set the mode based on analog read from pin 5
  if (analogRead(analogPins[5]) > 24 && analogRead(analogPins[5]) < 70) {
    mode = 0;
  }
  if (analogRead(analogPins[5]) > 71 && analogRead(analogPins[5]) < 99) {
    mode = 1;
  }
  /*modes are unused
    if (analogRead(analogPins[5]) > 80 && analogRead(analogPins[5]) < 100) {
     mode = 2;}
    if (analogRead(analogPins[5]) > 100 && analogRead(analogPins[5]) < 120) {
    mode = 3;}
  */
  if (analogRead(analogPins[5]) > 100 && analogRead(analogPins[5]) < 174) {
    mode = 4;
  }
  /*
    if (analogRead(analogPins[5]) > 150 && analogRead(analogPins[5]) < 190) {
    mode = 5;
    }
  */
  if (analogRead(analogPins[5]) > 175 && analogRead(analogPins[5]) < 360) {
    mode = 6;
  }
}
//used to change the house lights without input
void aHouseLighting() {
  switch (housePhase) {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      //all off
      analogWrite(3,0);
      analogWrite(5,0);
      analogWrite(6,0);
      break;
  }
}
void houseLighting( int pin, int value) {
  /*used to control the lights in the houses
    The lights are bi-directional so there are three outputs
    Having one line on will activate the other half the lights
    house lights are on pins 3,5,6
    equivalant to pins2[0][1-3]
  */
  if (houseLights[3][pin] < value) {
    do {
      houseLights[3][pin] = houseLights[3][pin] + houseLights[1][pin];
      if (houseLights[3][pin] > 255) {
        houseLights[3][pin] = 255;
      }
      analogWrite(houseLights[0][pin], houseLights[3][pin]);
      speedStrip();
      delay(ssdelay);
    }
    while (houseLights[3][pin] < value);
  }
  if (houseLights[3][pin] > value) {
    do {
      houseLights[3][pin] = houseLights[3][pin] - houseLights[1][pin];
      if (houseLights[3][pin] < 0 ) {
        houseLights[3][pin] = 0;
      }
      analogWrite(houseLights[0][pin], houseLights[3][pin]);
      speedStrip();
      delay(ssdelay);
    }
    while (houseLights[3][pin] > value);
  }
  /*
    The nex if statements watch for invalid pin settings
    If two are at full value the remaining one is turned off.
  */
  if (houseLights[3][0] > 254 && houseLights[3][1] > 254) {
    houseLights[3][2] = 0;
    analogWrite(houseLights[0][2], houseLights[3][2]);
  }
  if (houseLights[3][1] > 254 && houseLights[3][2] > 254) {
    houseLights[3][0] = 0;
    analogWrite(houseLights[0][0], houseLights[3][0]);
  }
  if (houseLights[3][0] > 254 && houseLights[3][2] > 254) {
    houseLights[3][1] = 0;
    analogWrite(houseLights[0][1], houseLights[3][1]);
  }
}
//Controls the TIP120 connected to the fountain. value is on or off.
void fountain() {
  if (digitalRead(fountinpin) == 1) {
    analogWrite(fountinpin, 0);
  }
  if (digitalRead(fountinpin) == 0) {
    analogWrite(fountinpin, 255);
  }
}
//holds a single color for both strips
void rGBSolid(int cycleNumber) {
  aHouseLighting();
  //sets values to max value so everything has a base starting point
  //cycle number is used once per call to set everything to be the same
  if (cycleNumber == 0) {
    int x = 4;
    do {
      pins[3][x] = 255;
      x--;
    }
    while (x > 0);
  }
  int x = 50;
  int average = 0;
  do {
    average = average + analogRead(analogPins[0]);
    x--;
  }
  while (x > 0);
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
    average = average + analogRead(analogPins[1]);
    x--;
  }
  while (x > 0);
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
    average = average + analogRead(analogPins[2]);
    x--;
  }
  while (x > 0);
  average = average / 50;
  if (average > 255) {
    average = 255;
  }
  if (average < 0) {
    average = 0;
  }
  pins[3][3] = average;
  analogWrite(pins[0][1], pins[3][1]);
  analogWrite(pins[0][2], pins[3][2]);
  analogWrite(pins[0][3], pins[3][3]);
}
//used to fade the pins smoothly instead of a "hard" switch
//when calling pinfader if house lights or LED strip is to remain the same call with 0,0,#,# to not change anything
void pinFader(int pin, int value, int houseLine, int value2) {
  if (pins[3][pin] > value && houseLights[3][houseLine] < value2) {
    do {
      pins[3][pin] = pins[3][pin] - pins[1][pin];
      houseLights[3][houseLine] = houseLights[3][houseLine] + houseLights[1][houseLine];
      //catch if above 255 (full PWM signal)
      if (pins[3][pin] < 0) {
        pins[3][pin] = 0;
      }
      if (houseLights[3][houseLine] > 255) {
        houseLights[3][houseLine] = 255;
      }
      analogWrite(pins[0][pin], pins[3][pin]);
      analogWrite(houseLights[0][houseLine], houseLights[3][houseLine]);
      speedStrip();
      delay(ssdelay);
    }
    while (pins[3][pin] > value || houseLights[3][houseLine] < value);
  }
  if (pins[3][pin] < value && houseLights[3][houseLine] > value2) {
    do {
      pins[3][pin] = pins[3][pin] + pins[1][pin];
      houseLights[3][houseLine] = houseLights[3][houseLine] - houseLights[1][houseLine];
      //catch if above 255 (full PWM signal)
      if (pins[3][pin] > 255) {
        pins[3][pin] = 255;
      }
      if (houseLights[3][houseLine] < 0) {
        houseLights[3][houseLine] = 0;
      }
      analogWrite(pins[0][pin], pins[3][pin]);
      analogWrite(houseLights[0][houseLine], houseLights[3][houseLine]);
      speedStrip();
      delay(ssdelay);
    }
    while (pins[3][pin] < value || houseLights[3][houseLine] > value);
  }
  if (pins[3][pin] < value && houseLights[3][houseLine] < value2) {
    do {
      pins[3][pin] = pins[3][pin] + pins[1][pin];
      houseLights[3][houseLine] = houseLights[3][houseLine] + houseLights[1][houseLine];
      //catch if above 255 (full PWM signal)
      if (pins[3][pin] > 255) {
        pins[3][pin] = 255;
      }
      if (houseLights[3][houseLine] > 255) {
        houseLights[3][houseLine] = 255;
      }
      analogWrite(pins[0][pin], pins[3][pin]);
      analogWrite(houseLights[0][houseLine], houseLights[3][houseLine]);
      speedStrip();
      delay(ssdelay);
    }
    while (pins[3][pin] < value || houseLights[3][houseLine] < value);
  }
  if (pins[3][pin] > value && houseLights[3][houseLine] > value2) {
    do {
      pins[3][pin] = pins[3][pin] - pins[1][pin];
      houseLights[3][houseLine] = houseLights[3][houseLine] - houseLights[1][houseLine];
      //catch if above 255 (full PWM signal)
      if (pins[3][pin] < 0) {
        pins[3][pin] = 0;
      }
      if (houseLights[3][houseLine] < 0) {
        houseLights[3][houseLine] = 0;
      }
      analogWrite(pins[0][pin], pins[3][pin]);
      analogWrite(houseLights[0][houseLine], houseLights[3][houseLine]);
      speedStrip();
      delay(ssdelay);
    }
    while (pins[3][pin] < value || houseLights[3][houseLine] < value);
  }
}
//this is the interupt function called by D2 when signal is received
void interFunction() {
  //check to make sure button two was NOT pressed
  if (digitalRead(12) == 0 && buttonPress2 == 0) {
    buttonPress = 1;
  }
  //check to see if button 2 HAS been pressed
  if (digitalRead(12) == 1 && buttonPress == 0) {
    buttonPress2 = 1;
    Serial.println(digitalRead(12));
  }
  Serial.println("interupt");
  Serial.println("button pressed");
}
//Main loop to chose mode behavor
//speedStrip is called often to set the speed at any given point
void loop() {
  if (mode != 7) {
    rAD();
  }
  if (buttonPress == 1 && buttonPress2 == 0) {
    fountain();
    Serial.println("Toggleing fountain");
    buttonPress = 0;
  }
  if (buttonPress2 == 1 && buttonPress == 0) {
    int x = 100;
    do {
      Serial.println("Turning everything off");
      buttonPress2 = 0;
      if (mode != 7) {
        mode = 7;
        break;
      }
      if (mode == 7) {
        mode = 0;
        break;
      }
      x--;
    } while (x > 0);
  }
  //Diagnostic data for checking values on pins A0-A5
  Serial.println(" ");
  Serial.print(" A0 " );
  Serial.print(analogRead(analogPins[0]));
  Serial.print(" A1 " );
  Serial.print(analogRead(analogPins[1]));
  Serial.print(" A2 " );
  Serial.print(analogRead(analogPins[2]));
  Serial.print(" A3 " );
  Serial.print(analogRead(analogPins[3]));
  Serial.print(" A4 " );
  Serial.print(analogRead(analogPins[4]));
  Serial.print(" A5 " );
  Serial.print(analogRead(analogPins[5]));
  Serial.print( " ssdelay ");
  Serial.print(ssdelay);
  Serial.print(" mode " );
  Serial.print( mode);
  Serial.print(" interpin ");
  Serial.println(digitalRead(interpin));
  //House lights need to be called in every mode.
  //House lights should "ping" from one side to the other.
  //call for mode selection
  switch (mode) {
    //case 0 sets both strips to one selectable color
    case 0:
      rGBSolid(0);
      rAD();
      break;
    //will be changed for Christmas setup with a fountain and only one LED strip
    case 1:
      speedStrip();
      if (ssdelay == 1) {}
      if (ssdelay == 2) {}
      //pins did not set value when this was in function above. put it here to fix
      analogWrite(houseLights[0][1], houseLights[3][1]);
      analogWrite(houseLights[0][2], houseLights[3][2]);
      analogWrite(houseLights[0][3], houseLights[3][3]);
      rAD();
      break;
    //case two and three are not used yet
    case 2:
      rAD();
      break;
    case 3:
      rAD();
      break;
    case 4:
      //rainbow effect
      pinFader(1, 0, 3, 255); //Red
      pinFader(2, 0, 3, 0); //green
      pinFader(3, 255, 2, 255);  //blue
      pinFader(3, 0, 1, 255);  //blue
      pinFader(1, 255, 2, 0); //red
      pinFader(2, 255, 1, 0); //green
      pinFader(2, 0, 3, 255); //green
      pinFader(1, 0, 3, 0); //red
      pinFader(3, 255, 1, 255);  //blue
      pinFader(2, 255, 1, 0); //red
      pinFader(3, 0, 2, 255);  //blue
      pinFader(0, 0, 2, 0);  //blue
      rAD();
      break;
    case 5:
      rAD();
      break;
    case 6:
      //Hard rainbow and flash
      //3,5,6 are house lights(LED string). all on makes all off
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
      break;
    case 7:
      break;
    default:
      rAD();
      break;
  }
}
