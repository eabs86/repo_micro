void setup() {
  Serial.begin(9600); // Inicializa a porta serial com a taxa de transmissão de 9600 bps
}

void loop() {
  Serial.println("Hello, World!"); // Envia a mensagem "Hello, World!" pela porta serial
  delay(1000); // Espera por 1 segundo
}
