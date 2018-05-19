int led = 9;          
int brightness = 0;    
int fadeAmount = 5;    

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  
  for(int i = 0; i < 3; i++) {
    analogWrite(led, brightness);
    brightness = brightness + fadeAmount;
  
    // reverse direction
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    // dimming effect
    delay(30);
  }
}
