// "Супер-кнопка" 
volatile bool redLedActive = false;
volatile bool blinkBlueRequest = false;
int blueBrightness = 0;
int fadeAmount = 5;
unsigned long redLedStartTime = 0;
int blinkCount = 0;

void setup() {
  pinMode(9, OUTPUT);    // Синий светодиод 
  pinMode(10, OUTPUT);   // Красный светодиод
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(2), activateRedLED, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), requestBlinkBlue, FALLING);
}

void loop() {
  if (redLedActive) {
    digitalWrite(10, HIGH);
    if (millis() - redLedStartTime >= 2000) {
      redLedActive = false;
      digitalWrite(10, LOW);
    }
  } 
  else if (blinkBlueRequest) {
    for (int i = 0; i < 5; i++) {
      analogWrite(9, 255);
      delay(200);
      analogWrite(9, 0);
      delay(200);
    }
    blinkBlueRequest = false;
    blueBrightness = 0; 
  } 
  else {
    analogWrite(9, blueBrightness);
    blueBrightness += fadeAmount;
    
    if (blueBrightness <= 0 || blueBrightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    delay(30);
  }
}

void activateRedLED() {
  redLedActive = true;
  redLedStartTime = millis();
}

void requestBlinkBlue() {
  blinkBlueRequest = true;
}

