//print matrix function:
void printMatrix() {
  for (int i = 0; i < 3; i++) { //3 rows
    for (int j = 0; j < 4; j++) { // 4 columns
      Serial.print(matrix[i][j]);
      Serial.print(" ");
    }
    Serial.println(" "); //new line after each row
  }
  Serial.println(" ");
}


void turnAllOff() {
  for (int i=0; i<numberOfButtons; i++) {
    digitalWrite (i, LOW); // turns each LED off.
  }
}

void turnAllOn(){
  for (int i=0; i<numberOfButtons; i++) {
    digitalWrite (i, HIGH); // turns each LED on.
  }
}

void blinkAllOnce() {
  for (int i=0; i<numberOfButtons; i++) {
  digitalWrite(i, HIGH);  // turns each LED on.
  }
  delay(blinkSpeed);
  for (int i=0; i<numberOfButtons; i++) { 
  digitalWrite(i, LOW); // turns each LED off.
  }
}

void blinkAllTenTimes() {
  for (int i=0; i<numberOfButtons; i++) {
    blinkAllOnce();
    }
  }

void blinkInSequence() {
  for (int i=0; i<numberOfButtons; i++) {
  digitalWrite(i, HIGH); // turns each LED on.
  delay(blinkSpeed);
  digitalWrite(i, LOW); // turns each LED off.
  }
}

void blinkInSequenceTenTimes() {
  for (int i=0; i<10; i++) {
    blinkInSequence();
    }
  }

void blinkOneLED(int LEDPin) {
  for (int i=0; i<10; i++) {
  digitalWrite(LEDPin, HIGH); // turns one LED on.
  delay(blinkSpeed);
  digitalWrite(LEDPin, LOW); // turns one LED off.
  delay(blinkSpeed);
  }
}

