// "Антидребезг"
volatile bool ledState = false;
volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), toggleLED, FALLING);
}

void loop() {
  
}

void toggleLED() {
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTime > debounceDelay) {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
    lastInterruptTime = currentTime;
  }
}

