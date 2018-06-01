// author: @MarlaNa
// project: @GestureLamp

/* CONSTANTS */
// Pins for LEDs
#define PIN_RED 9
#define PIN_GREEN 10
#define PIN_BLUE 11
// Pins for the ultrasonic sensor
#define PIN_TRIG 7
#define PIN_ECHO 2
// Delay time between loop iterations.
#define DELAY_TIME 50
// Maximum Brightness of LEDs.
#define MAX_BRIGHT 255
// Constants for normal mode.
#define NORMAL_RED 128
#define NORMAL_GREEN 128
#define NORMAL_BLUE 128
//---------------------------------------------------------------------//

/* MODES */
// Lamp Modes that can be changed by the user.
enum mode {
  off,
  normal,
  ambient,
  fading,
  blinking,
  disco
};
// LED colors
enum led {
  red,
  green,
  blue,
};
//---------------------------------------------------------------------//
/* AMBIENT MODE VARIABLES */
// The initial values of each color for ambient mode.
int ambient_red = 0;
int ambient_green = 170;
int ambient_blue = 170;
// Indicates whether a color is incrementing (1) or decrementing (0).
int incR = 1;
int incG = 1;
int incB = 0;
// Initial values for fading mode.
int fadeAmount = 5;
//---------------------------------------------------------------------//

/* FADING & DISCO MODE VARIABLES */
// Variable to track the LEDs brightness
int brightness = 0;
led disco_CurrentLED = red;
//---------------------------------------------------------------------//

/* GLOBAL VARIABLES */
// Array for changing lamp modes.
mode allModes[] = {normal, ambient, fading, blinking, disco};
// Counter for rotating through different LED modes.
int i = 0;
// Current (universal) LED mode.
mode ledMode = normal;
//---------------------------------------------------------------------//

void setup() {
  Serial.begin(9600);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  normalTransition();
}

void loop() {
  long duration, distance;
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(1000);
  digitalWrite(PIN_TRIG, LOW);
  duration = pulseIn(PIN_ECHO, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println(distance);

  if (distance > 0 && distance < 11) {
    ledMode = allModes[i % 5];
    switch (ledMode) {
      case ambient:
        Serial.write("ambient ");
        delay(1000);        
        ambientTransition();
        i++;
        delay(1000);
        break;
      case fading:
        Serial.write("fade ");
        delay(1000);
        fadeTransition();
        i++;
        delay(1000);
        break;
      case blinking:
        Serial.write("blinking ");
        delay(1000);
        blinkTransition();
        i++;
        delay(1000);
        break;
      default:
        ledMode = normal;
        i++;
        delay(1000);
        break;
    }
  } else {
    switch (ledMode) {
      case ambient:
        Serial.write("ambient ");
        ambientTransition();
        break;
      case fading:
        Serial.write("fade ");
        fadeTransition();
        break;
      case blinking:
        Serial.write("blinking ");
        blinkTransition();
        break;
      default:
        ledMode = normal;
        break;
    }
  }
  delay(DELAY_TIME);
}

/* TRANSITION MODES */
void normalTransition() {
  setColor(NORMAL_RED, NORMAL_GREEN, NORMAL_BLUE);
}

void ambientTransition() {
  if (ambient_red >= MAX_BRIGHT)
    incR = 0;
  else if (ambient_red <= 0)
    incR = 1;
  if (ambient_green >= MAX_BRIGHT)
    incG = 0;
  else if (ambient_green <= 0)
    incG = 1;
  if (ambient_blue >= MAX_BRIGHT)
    incB = 0;
  else if (ambient_blue <= 0)
    incB = 1;

  if (incR)
    ambient_red++;
  else
    ambient_red--;
  if (incG)
    ambient_green++;
  else
    ambient_green--;
  if (incB)
    ambient_blue++;
  else
    ambient_blue--;
  setColor(ambient_red, ambient_green, ambient_blue);
}

void blinkTransition() {
  setColor(MAX_BRIGHT,MAX_BRIGHT,MAX_BRIGHT);
  delay(500);
  reset();
  delay(500);
}

void fadeTransition() {
  setColor(brightness, brightness, brightness);
  // change the brightness for next time
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= MAX_BRIGHT) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

void discoTransition(){
  switch(disco_CurrentLED) {
    case red:
      setColor(MAX_BRIGHT, 0, 0);
      disco_CurrentLED = green;
    case: green:
      setColor(0, MAX_BRIGHT, 0);
      disco_CurrentLED = blue;
    case blue:
      setColor(0, 0, MAX_BRIGHT);
      disco_CurrentLED = red;
  }
}

// Sets the output voltage on the LED pins.
void setColor(int red,int green, int blue) {
  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
}

// Reset the brightness of all LEDs.
void reset() {
  analogWrite(PIN_RED, 0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE, 0);
}
