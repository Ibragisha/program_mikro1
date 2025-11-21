//"Таймер-миллисекундомер"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

volatile unsigned long milliseconds = 0;
volatile bool timerRunning = false;
volatile bool resetRequest = false;

void setup() {
  lcd.begin(16, 2);
  pinMode(2, INPUT_PULLUP);
  
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
 
  OCR1A = 249;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
  
  attachInterrupt(digitalPinToInterrupt(2), controlTimer, FALLING);
  
  lcd.print("Timer: 00:00:000");
}

void loop() {
  if (resetRequest) {
    milliseconds = 0;
    resetRequest = false;
  }
  
  displayTime();
  delay(50);
}

void displayTime() {
  unsigned long totalMs = milliseconds;
  unsigned long minutes = totalMs / 60000;
  unsigned long seconds = (totalMs % 60000) / 1000;
  unsigned long ms = totalMs % 1000;
  
  lcd.setCursor(7, 0);
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
  lcd.print(":");
  if (ms < 100) lcd.print("0");
  if (ms < 10) lcd.print("0");
  lcd.print(ms);
}

void controlTimer() {
  static unsigned long lastPress = 0;
  if (millis() - lastPress > 200) { // Антидребезг
    if (!timerRunning) {
      timerRunning = true;
    } else {
      timerRunning = false;
      resetRequest = true;
    }
    lastPress = millis();
  }
}

ISR(TIMER1_COMPA_vect) {
  if (timerRunning) {
    milliseconds++;
  }
}

