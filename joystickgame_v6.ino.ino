/*
  button 1-10 connected to digital pins 10 to 19.
  LEDs in button 1-10 connected to digtial pin 0-9.
  joystick integration.
  button reaction.
  buttonplayer winner, reset game.
  joystickplayer winner, reset game.
  split up light and blink functions into seperate tab: LEDs.ino.
  pin 0 and 1 is deactived when Serial.print is called.
*/

//global variables:
int numberOfButtons = 10;
int matrix[3][4]; //initialize matrix, 3 rows and 4 columns
int row = 0; //initial row
int column = 0;  //initial column
int blinkSpeed=100;
int pauseTime = 205;
int lightPin = 0; //initial light
unsigned long previousMillis = 0;


// the setup function runs once
void setup() {
  //Serial.begin(9600); //setup print to computer screen
  //Joystick pins:
  pinMode (20, INPUT_PULLUP); //up
  pinMode (21, INPUT_PULLUP); //down
  pinMode (22, INPUT_PULLUP); //left
  pinMode (23, INPUT_PULLUP); //right

  //button and LED pins:
  for (int i = 0; i < numberOfButtons; i++) {
    pinMode(i+10, INPUT_PULLUP); //button pins 10-19
    pinMode(i, OUTPUT); // LED pins 0-9
  }
  matrix[row][column] = 1; //activate first position in matrix in upper left corner
  blinkInSequence();
}


// the loop function runs over and over again forever
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > pauseTime) { //when time, run the code below
    previousMillis = currentMillis;
    readFromJoystick();
    turnOnActiveLED();
  }
readButtons();
}


//read signals from buttons
void readButtons() {
  int pushedPin=50; //actual button pins are 10-19
  for (int i = 0; i < numberOfButtons; i++) {
    int buttonSignal = digitalRead(i + 10);
    if (buttonSignal==0) { //button is pushed
      pushedPin = i+10;
    }
    if (pushedPin == lightPin+10) { //buttonplayer wins
      turnAllOn();
      delay(blinkSpeed*10);
      turnAllOff();
      blinkOneLED(0);
      resetGame();
    }
  }
}


//read joystick. In neutral, all values are 1.
void readFromJoystick() {
  int up = digitalRead(20);
  int down = digitalRead(21);
  int left = digitalRead(22);
  int right = digitalRead(23);
  //if joystick acitvated:
  if (up == 0 || down == 0 || right == 0 || left == 0) { //when jouystick is pulled the value= 0. || means OR.
    matrix[row][column] = 0; //remove old position
    // row and column keeps track of position in matrix.
    if (up == 0) { //joystick is pressed up
      row = row + 1; //move one row down
      if (row>2) { row=2; }
    }
    if (down == 0) { //joystick is pressed down
      row = row - 1; //move one row up
      if (row<0) { row=0; }
    }
    if (right == 0) { //joystick is pressed right
      column = column + 1; //move one row to the right
      if (column>3) { column=3; }
    }
    if (left == 0) { //joystick is pressed left
      column = column - 1; //move one row to the left
      if (column<0) { column=0; }
    }
    matrix[row][column] = 1;  //store new position
  }
}


//assign a number to the active field:
void turnOnActiveLED() {
 for (int i = 0; i < 3; i++) { //3 rows
    for (int j = 0; j < 4; j++) { // 4 columns
      if (matrix[i][j]==1) { // if the field is active
        lightPin = j*3+i; //give a unique number to the field
        if (lightPin==9) { //if out of bounce
          lightPin=6;
        } 
        if (lightPin==11) { //if out of bounce
          lightPin=8;
        } 
        if (lightPin==10) { //joystick player is winner.
          turnAllOff();
          lightPin=9;
          blinkOneLED(lightPin);
          turnAllOn();
          delay(blinkSpeed*10);
          turnAllOff();
          lightPin = 0;
          resetGame();
          return;                
        }
        turnAllOff();
        digitalWrite(lightPin, HIGH); //turn on the lightPin
      }
    }
 }
}
  

void resetGame() {
  for (int i = 0; i < 3; i++) { //3 rows
    for (int j = 0; j < 4; j++) { // 4 columns
      matrix[i][j]=0;
      matrix[0][0]=1;
      row=0; // reset position in matrix.
      column=0; //reset position in matrix.
    }
  }
  turnAllOff();
  turnOnActiveLED();
}


