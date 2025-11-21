//"Режим энергосбережения"
#include <avr/sleep.h>
#include <avr/power.h>

const int motionSensorPin = 2;
const int ledPin = 13;
volatile bool motionDetected = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(motionSensorPin, INPUT);
  digitalWrite(ledPin, LOW);
  
  attachInterrupt(digitalPinToInterrupt(motionSensorPin), motionISR, RISING);
  
  Serial.begin(9600);
  Serial.println("System starting... Entering sleep mode");
}

void loop() {
  if (motionDetected) {
    wakeUpAction();
    motionDetected = false;
  }
  
  enterSleepMode();
}

void motionISR() {
  motionDetected = true;
}

void enterSleepMode() {
  Serial.println("Entering sleep mode...");
  delay(100); 
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  power_adc_disable();
  power_spi_disable();
  power_timer0_disable();
  power_timer1_disable();
  power_timer2_disable();
  power_twi_disable();
  
  sleep_mode();
  
  sleep_disable();
  power_all_enable();
  
  Serial.println("Woke up!");
}

void wakeUpAction() {
  Serial.println("Motion detected! Turning on LED for 10 seconds");
  digitalWrite(ledPin, HIGH);
  delay(10000); // 10 секунд
  digitalWrite(ledPin, LOW);
  Serial.println("LED turned off");
}

