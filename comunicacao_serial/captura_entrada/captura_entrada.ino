void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char incomingChar = Serial.read(); // Lê o caractere da porta serial
    Serial.print("Recebido: ");
    Serial.println(incomingChar); // Imprime o caractere recebido
  }
}
