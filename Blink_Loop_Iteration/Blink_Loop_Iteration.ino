// The higher the number, the slower the timing.
int timer = 200;           

void setup() {
  for (int thisPin = 3; thisPin < 8; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}

void loop() {
  //run the programm 3 times only
  for (int rounds = 0; rounds < 3; rounds++) {
     // loop from lowest to highest
    for (int thisPin = 3; thisPin < 8; thisPin++) {
      blink(thisPin);
      blink(thisPin);
    }
  
    // loop from highest to lowest
    for (int thisPin = 7; thisPin >= 3; thisPin--) {
      blink(thisPin);
      blink(thisPin);
    }
  }
  //stop loop
  while(1);
}

void blink(int thisPin) {
  digitalWrite(thisPin, HIGH);
  delay(timer);
  digitalWrite(thisPin, LOW);
  delay(timer);
}

