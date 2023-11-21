char receivedChar;

void setup() {
  Serial.begin(9600);
  Serial.println("Digite algo:");
}

void loop() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read(); // Lê o caractere da porta serial
    Serial.print("Caractere recebido: ");
    Serial.println(receivedChar);
    
    // Adicione aqui o código para responder ao caractere recebido, se necessário
  }
}
