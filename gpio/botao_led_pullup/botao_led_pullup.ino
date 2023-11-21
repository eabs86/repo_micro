int ledPin = 10; // LED conectado ao pino digital 10
int buttonPin = 2; // Botão conectado ao pino digital 2

void setup() {
  pinMode(ledPin, OUTPUT); // Inicializa o pino do LED como saída
  pinMode(buttonPin, INPUT_PULLUP); // Ativa a resistência de pull-up interna
}

void loop() {
  // Verifica se o botão está pressionado (o pino fica LOW se pressionado)
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(ledPin, HIGH); // Aciona o LED
  } else {
    digitalWrite(ledPin, LOW); // Desliga o LED
  }
}
