// Delay time: sets the time in milliseconds between loop iterations.
#define DELAY_TIME 50
// Maximum Brightness: the maximum level the pins will reach.
#define MAX_BRIGHT 255
// The pins which each color value is output to.
#define PIN_RED 9
#define PIN_GREEN 10
#define PIN_BLUE 11
// Pin for the photoresistor
#define PIN_PHOTORESISTOR A0

// Lamp Modes that can be changed by the user.
enum mode {
  off,
  ambient,
  fading,
  blinking,
  disco
};

// The initial values of each color.
  int red = 0;
  int green = 170;
  int blue = 170;

// Indicates whether a color is incrementing (1) or decrementing (0).
int incR = 1;
int incG = 1;
int incB = 0; 

// LED brightness
int brightness = 0; 
// Steps to fade the led 
int fadeAmount = 5;
mode allModes[] = {ambient, fading, blinking, disco};
// Rotate through different LED modes.
int i = 0;
mode ledMode;

void ambientTransition() {
  if (red >= MAX_BRIGHT)
    incR = 0;
  else if (red <= 0)
    incR = 1;
  if (green >= MAX_BRIGHT)
    incG = 0;
  else if (green <= 0)
    incG = 1;
  if (blue >= MAX_BRIGHT)
    incB = 0;
  else if (blue <= 0)
    incB = 1;
  
  if (incR)
    red++;
  else
    red--;
  if(incG)
    green++;
  else
    green--;
  if(incB)
    blue++;
  else
    blue--;

  setColor();
}

void blinkTransition() {
  for(int i = 0; i < 4; i++){
    red = 255;
    green = 255;
    blue = 255;
    setColor();
    delay(2000); 

    red = 0;
    green = 0;
    blue = 0;
    setColor();
    delay(500);
  }
}

void fadeTransition() {
  red = brightness;
  green = brightness;
  blue = brightness;
  setColor();
   // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

// Reset the brightness of all LEDs.
void reset() {
  analogWrite(PIN_RED, 0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE, 0);
}

// Sets the output voltage on the LED pins.
void setColor() {
  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_PHOTORESISTOR, INPUT);
  ledMode = off;
  reset();
}

void loop() {
  int pRValue = analogRead(PIN_PHOTORESISTOR);
  Serial.println(analogRead(pRValue));
  if (pRValue < 25) {
    Serial.println(analogRead(pRValue));
    ledMode = allModes[i%3];
    switch (ledMode) {
      case ambient: 
        Serial.write("ambient ");         
        ambientTransition();
        i++;
        delay(2000);
        break;
      case fading:
        Serial.write("fade ");
        fadeTransition();        
        i++;
        delay(2000);
        break;
      case blinking:
        Serial.write("blinking ");
        blinkTransition();        
        i++;
        delay(2000);
        break;
      default: 
        ledMode = off;
        reset();
        i++;
        delay(3000);
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
        ledMode = off;
        reset();       
        break;
    }
  }
  delay(DELAY_TIME);
}
