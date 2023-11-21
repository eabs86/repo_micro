const int buttonPin = 2;  // O pino do botão conectado ao pino de interrupção digital 2
const int ledPin = 13;    // O pino do LED conectado ao pino digital 13

volatile bool ledState = false;  // Estado do LED, controlado pela interrupção

void setup() {
  pinMode(ledPin, OUTPUT);       // Configura o pino do LED como saída
  pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up interno

  // Configura a interrupção para o pino do botão, para acionar na borda de descida
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggleLed, FALLING);
}

void loop() {
  // O loop principal não faz nada neste exemplo
}

void toggleLed() {
  ledState = !ledState;    // Alterna o estado do LED
  digitalWrite(ledPin, ledState); // Atualiza o estado do LED
}
