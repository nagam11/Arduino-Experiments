const int buttonPin = 2;    
const int ledPin =  13;     

int buttonState = 0;        

void setup() {
  pinMode(ledPin, OUTPUT);
  // Enable built-in pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // check if the button is pressed. LOW: pressed, HIGH: pressed
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
