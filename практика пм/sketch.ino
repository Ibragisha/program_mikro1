const int ledCount = 7;
int leds[ledCount] = {2, 3, 4, 5, 6, 7, 8};
int sensorPin = A0;
int lightLevel = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(sensorPin, INPUT);
}

void loop() {
  lightLevel = analogRead(sensorPin);
  Serial.println(lightLevel);

  if (lightLevel < 400) {          
    fromEdgesToCenter(520);     
  } else if (lightLevel < 700) {   
    centerToEdges(100);         
  } else {                         
    symmetricBlink(500);        
  }
}

// от краев к цетру 
void fromEdgesToCenter(int delayTime) {
  int mid = ledCount / 2;
  for (int i = 0; i <= mid; i++) {
    digitalWrite(leds[i], HIGH);
    digitalWrite(leds[ledCount - 1 - i], HIGH);
    delay(delayTime);
    digitalWrite(leds[i], LOW);
    digitalWrite(leds[ledCount - 1 - i], LOW);
  }
}

// из центра к краям 
void centerToEdges(int delayTime) {
  int mid = ledCount / 2;
  for (int i = mid; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    digitalWrite(leds[ledCount - 1 - i], HIGH);
    delay(delayTime);
    digitalWrite(leds[i], LOW);
    digitalWrite(leds[ledCount - 1 - i], LOW);
  }
}

// симметричное 
void symmetricBlink(int delayTime) {
  for (int i = 0; i <= ledCount / 2; i++) {
    digitalWrite(leds[i], HIGH);
    digitalWrite(leds[ledCount - 1 - i], HIGH);
  }
  delay(delayTime);
  for (int i = 0; i <= ledCount / 2; i++) {
    digitalWrite(leds[i], LOW);
    digitalWrite(leds[ledCount - 1 - i], LOW);
  }
  delay(delayTime);
}
