//"Счетчик оборотов"
volatile unsigned long pulseCount = 0;
volatile unsigned long lastPulseTime = 0;
unsigned long lastSecond = 0;
bool lastState = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
  
  attachInterrupt(digitalPinToInterrupt(2), countPulse, CHANGE);
  
  Serial.println("RPM Counter Started");
  Serial.println("Time(s) | Pulses | RPM");
  Serial.println("----------------------");
}

void loop() {
}

void countPulse() {
  bool currentState = digitalRead(2);
  if (currentState != lastState) {
    pulseCount++;
    lastState = currentState;
  }
}

ISR(TIMER1_COMPA_vect) {
  static unsigned long seconds = 0;
  seconds++;
  
  float rpm = (pulseCount / 20.0) * 60.0;
  
  Serial.print(seconds);
  Serial.print("      | ");
  Serial.print(pulseCount);
  Serial.print("     | ");
  Serial.println(rpm);
  
  pulseCount = 0;
}

