char receivedChar;

void setup() {
  Serial.begin(9600);
  Serial.println("Digite algo:");
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
    
    // Adicione aqui o código para responder ao caractere recebido, se necessário
  }
}
