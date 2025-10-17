#include <Arduino.h>
#include <Servo.h>

Servo esc1;

void setup() {
  esc1.attach(2);  // PWM-capable pin on Teensy 4.1
  esc1.writeMicroseconds(1000); // idle signal
}

void loop() {
  for (int us = 1000; us <= 2000; us += 10) {
    esc1.writeMicroseconds(us);
    delay(20);
  }
  for (int us = 2000; us >= 1000; us -= 10) {
    esc1.writeMicroseconds(us);
    delay(20);
  }
}