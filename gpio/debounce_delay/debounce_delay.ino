int inputPin = 10;
int ledPin = 13;
int ledValue = LOW;
const int DELAY_DEBOUNCE = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(inputPin,INPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(inputPin,HIGH);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Nivel logico do botao:"); // imprime na serial uma frase
  Serial.println(digitalRead(inputPin)); // imprime o status do botão + nova linha
  if (digitalRead(inputPin)==LOW){
    ledValue = !ledValue;
    digitalWrite(ledPin,ledValue);
    delay(DELAY_DEBOUNCE);
  }

}
