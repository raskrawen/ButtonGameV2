int interval = 200; //pause mellem blink

// setup køres een gang:
void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP); //button pin
  pinMode(2, OUTPUT); // LED pin
}

// loop gentages uendeligt:
void loop() {
  for (int i = 0; i < 5; i++) { // gentag 5 gange
    digitalWrite(0, HIGH); // tænd LED
    delay(interval);  // vent
    digitalWrite(0, LOW); // sluk LED
    delay(interval);  // vent
  }
  delay(1000);  //Vent 1 sekunder

  int x = digitalRead(8); // mål pin 8 (knappen)
  Serial.println(x);  // print resultat af måling
}




