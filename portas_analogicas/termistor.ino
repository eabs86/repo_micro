int termistorPin = A0; // Pino do termistor
float valorTermistor;
float temperatura;

void setup() {
  Serial.begin(9600);
}

void loop() {
  valorTermistor = analogRead(termistorPin);
  temperatura = valorTermistor * 0.48828125; // Conversão para graus Celsius
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");
  delay(1000);
}
