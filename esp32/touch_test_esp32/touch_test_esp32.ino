
#define touch_pin 4
#define led_pin   5
#define limiar    25

int touch_value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  pinMode(led_pin, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<100;i++){
    touch_value = touch_value + touchRead(touch_pin);
  }
  touch_value = touch_value/100;
  Serial.print(touch_value);
  if (touch_value<limiar){
    digitalWrite(led_pin, HIGH);
    Serial.println("LED Ligado");
  }
    else{
      digitalWrite(led_pin, LOW);
      Serial.println("LED Desligado");
    }
    delay(500);
}
