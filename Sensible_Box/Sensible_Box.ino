/* Ultrasonic sensor pins */
const int trigPin = 1;
const int echoPin = 2;
/* LED rows pins */
const int led_firstRow = 3;
const int led_secondRow = 5;
const int led_thirdRow = 6;
const int led_forthRow = 9;
const int led_test = 10;
/* Button pins */
const int buttonPin = 4;

int brightness = 0;    // how bright the LED is
int buttonState = 0;   // status of the switch
int buttonLastInput = 0;

/*JOYSTICK*/
const int inX = A0; // analog input for x-axis
const int inY = A1; // analog input for y-axis
const int inPressed = 12; // input for detecting whether the joystick/button is pressed
int xValue = 0; // variable to store x value
int yValue = 0; // variable to store y value
int notPressed = 0; // variable to store the button's state => 1 if not pressed

void setup() {
  pinMode(led, OUTPUT);
  pinMode(led_a, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_c, OUTPUT);
  pinMode(led_d, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  /*JOYSTICK*/
  pinMode(inX, INPUT); // setup x input
  pinMode(inY, INPUT); // setup y input
  pinMode(inPressed, INPUT_PULLUP); // we use a pullup-resistor for the button functionality
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print(distance);
  delay(10);
  // Correlation of brightness (0-255) and distance of (0-10 cm).
  brightness = 255 - 25.5 * distance;

  // check if the button is pressed (non-continuously). LOW: pressed, HIGH: not pressed
  if (buttonState == HIGH && buttonLastInput == 0) {
    Serial.print("OFF");
    brightness = 0;
    startLEDs();
  } else if (buttonState == HIGH && buttonLastInput == 1) {
      delay(30);
      startLEDs();
      delay(30);
  } else if (buttonState == LOW) {
    if (buttonLastInput == 0) {
      Serial.print("TURN ON");
      buttonLastInput = 1;
      delay(30);
      startLEDs();
      delay(30);
     } else {
      Serial.print("TURN OFF");
      buttonLastInput = 0;
      brightness = 0;
      startLEDs();
    }
  }
}

void startLEDs() {
  analogWrite(led_firstRow, brightness);
  analogWrite(led_secondRow, brightness);
  analogWrite(led_thirdRow, brightness);
  analogWrite(led_forthRow, brightness);
  analogWrite(led_test, brightness);
}

