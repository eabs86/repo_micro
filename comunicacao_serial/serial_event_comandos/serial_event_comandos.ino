char receivedChar;

const int ledPin1 = 2; // Pino para o primeiro LED
const int ledPin2 = 3; // Pino para o segundo LED

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.println("Digite '1' para ligar o LED 1 ou '2' para ligar o LED 2:");
}

void loop() {
  // O código principal continua executando normalmente
  
  // Você pode adicionar aqui qualquer lógica adicional que precisa ser executada repetidamente
}

void serialEvent() {
  while (Serial.available()) {
    receivedChar = Serial.read(); // Lê o caractere da porta serial
    Serial.print("Caractere recebido: ");
    Serial.println(receivedChar);
    
    // Implementa a lógica de comando com base no caractere recebido
    if (receivedChar == '1') {
      digitalWrite(ledPin1, HIGH); // Liga o LED 1
      Serial.println("LED 1 ligado.");
    } else if (receivedChar == '2') {
      digitalWrite(ledPin2, HIGH); // Liga o LED 2
      Serial.println("LED 2 ligado.");
    } else {
      Serial.println("Comando desconhecido.");
    }
  }
}
