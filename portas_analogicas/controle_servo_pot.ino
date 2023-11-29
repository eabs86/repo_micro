#include <Servo.h>

Servo meuServo;
int potPin = A0;
int valorPot;
int angulo;

void setup() {
  meuServo.attach(9);
}

void loop() {
  valorPot = analogRead(potPin);
  angulo = map(valorPot, 0, 1023, 0, 180); // Mapeia para o ângulo do servo
  meuServo.write(angulo);                   // Move o servo
  delay(15);
}
