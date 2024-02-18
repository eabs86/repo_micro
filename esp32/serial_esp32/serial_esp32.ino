
#define LED 4

char ligar_led = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    ligar_led = Serial.read();
    if (ligar_led == 'l' || ligar_led == 'L') {
      digitalWrite(LED, HIGH);
    }
    else if (ligar_led == 'd' || ligar_led == 'D') {
      digitalWrite(LED, LOW);
    }
    else {
      Serial.println("Comando inválido: Digite l ou L para ligar o LED, e d ou D para desligar o LED");
    }
  }
}
