int potPin = A0; // Pino do potenciômetro
int ledPin = 9;  // Pino PWM do LED
int valorPot;    // Para armazenar a leitura do potenciômetro

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  valorPot = analogRead(potPin);         // Lê o valor do potenciômetro
  analogWrite(ledPin, valorPot / 4);     // Escreve no LED (0-1023) -> (0-255)
  delay(10);
}
