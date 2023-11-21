// Declaração das variáveis

int ledPin = 10;
const int DELAY_PERIOD = 500;

void setup() {
  // inicializa o ledPin como uma saída
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin, HIGH);  // coloca o pino do LED em nível alto
  delay(DELAY_PERIOD);                      // espera por 500ms
  digitalWrite(ledPin, LOW);   // coloca o pino do LED em nível baixo
  delay(DELAY_PERIOD);                      // espera por 500ms
}