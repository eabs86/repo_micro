int ldrPin = A0; // Pino conectado ao LDR
int ledPin = 9;  // Pino PWM do LED
int valorLdr;    // Para armazenar a leitura do LDR

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  valorLdr = analogRead(ldrPin);         // Lê o valor do LDR
  int brilhoLed = map(valorLdr, 0, 1023, 255, 0); // Mapeia o valor para brilho do LED
  analogWrite(ledPin, brilhoLed);        // Ajusta o brilho do LED
  
  // Opcional: Imprimir o valor no Serial Monitor
  Serial.print("Intensidade LDR: ");
  Serial.print(valorLdr);
  Serial.print(", Brilho LED: ");
  Serial.println(brilhoLed);
  
  delay(100); // Pequeno atraso para estabilidade
}
