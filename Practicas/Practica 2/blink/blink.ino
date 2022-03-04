void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= i; j++ ) {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(100);                        // frecuencia de parpadeo a 100ms
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(100);                        // frecuencia de parpadeo a 100ms
    }
    delay(1000); // espera 1 segundo para la siguiente secuencia 1..5
  }
}
