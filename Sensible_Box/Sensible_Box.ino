/* Ultrasonic sensor pins */
const int trigPin = 7;
const int echoPin = 2;
/* LED rows pins */
const int led_firstRow = 9;
const int led_secondRow = 10;
const int led_thirdRow = 11;
const int led_forthRow = 12;
const int led_fifthRow = 13;
/* Button pins */
const int buttonPin = 4;
/* Control variables*/
int brightness = 0;    // how bright the LED is
int buttonState = 0;   // status of the switch
int buttonLastInput = 0;  // implement non continuous clicking
int behavioralMode = 0; // 0: Introvert, 1: Extrovert

/*JOYSTICK*/
const int inX = A0; // analog input for x-axis
const int inY = A1; // analog input for y-axis
const int inPressed = 12; // input for detecting whether the joystick/button is pressed
int xValue = 0; // variable to store x value
int yValue = 0; // variable to store y value
int notPressed = 0; // variable to store the button's state => 1 if not pressed

void setup() {
  Serial.begin(9600);
  pinMode(led_firstRow, OUTPUT);
  pinMode(led_secondRow, OUTPUT);
  pinMode(led_thirdRow, OUTPUT);
  pinMode(led_forthRow, OUTPUT);
  pinMode(led_fifthRow, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  /*JOYSTICK*/
  pinMode(inX, INPUT); // setup x input
  pinMode(inY, INPUT); // setup y input
  pinMode(inPressed, INPUT_PULLUP); // we use a pullup-resistor for the button functionality
}

void loop() {
  buttonState = digitalRead(buttonPin);
  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  // Correlation of brightness (0-255) and distance of (0-10 cm).
  brightness = (distance <= 10) ? 255 - 25.5 * distance : 0;
  startLEDs();  
  delay(50);
  

  // check if the button is pressed (non-continuously). LOW: pressed, HIGH: not pressed
  /*if (buttonState == HIGH && buttonLastInput == 0) {
    Serial.println(" OFF ");
    brightness = 0;
    startLEDs();
  } else if (buttonState == HIGH && buttonLastInput == 1) {
      Serial.println(" Do nothing ");
      startLEDs();
      delay(10);
  } else if (buttonState == LOW) {
    if (buttonLastInput == 0) {
      Serial.println(" TURN ON ");
      buttonLastInput = 1;
      startLEDs();
      delay(10);
     } else {
      Serial.println(" TURN OFF ");
      buttonLastInput = 0;
      brightness = 0;
      startLEDs();
      delay(10);
    }
  }*/
}

void startLEDs() {
  analogWrite(led_firstRow, brightness);
  analogWrite(led_secondRow, brightness);
  analogWrite(led_thirdRow, brightness);
  analogWrite(led_forthRow, brightness);
  analogWrite(led_fifthRow, brightness);
}


