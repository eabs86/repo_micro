int ledPin = 10; // LED conectado ao pino digital 10
int buttonPin = 2; // Botão conectado ao pino digital 2

void setup() {
  pinMode(ledPin, OUTPUT); // Inicializa o pino do LED como saída
  pinMode(buttonPin, INPUT); // Inicializa o pino do botão como entrada
  Serial.begin(9600);
}

void loop() {
  Serial.print("Nivel logico do botao:"); // imprime na serial uma frase
  Serial.println(digitalRead(buttonPin)); // imprime o status do botão + nova linha
  // Verifica se o botão está pressionado (o pino fica HIGH se pressionado)
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin, HIGH); // Aciona o LED
  } else {
    digitalWrite(ledPin, LOW); // Desliga o LED
  }
}




