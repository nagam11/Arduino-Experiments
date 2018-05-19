void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  for(int i = 0; i < 4; i++){
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(2000);                      
    digitalWrite(LED_BUILTIN, LOW);    
    delay(500); 
  }
  while(1){}                      
}
