#define BOUNCE_PIN 2
#define LED_PIN LED_BUILTIN
#include <Bounce2.h>

// instancia o objeto Bounce
Bounce bounce = Bounce();
int ledState = LOW;

void setup() {

  bounce.attach( BOUNCE_PIN ,  INPUT_PULLUP ); 
  // DEBOUNCE INTERVAL IN MILLISECONDS
  bounce.interval(5); // interval in ms 
  pinMode(LED_PIN, OUTPUT); // LED SETUP
  digitalWrite(LED_PIN, ledState);
  Serial.begin(9600);
}

void loop() {
  // Update the Bounce instance (YOU MUST DO THIS EVERY LOOP)
  bounce.update();
  // <Bounce>.changed() RETURNS true IF THE STATE CHANGED (FROM HIGH TO LOW OR LOW TO HIGH)
  if ( bounce.changed() ) {
    // THE STATE OF THE INPUT CHANGED // GET THE STATE
    int debouncedInput = bounce.read();
    Serial.print("Nivel logico do botao:"); // imprime na serial uma frase
    Serial.println(digitalRead(debouncedInput)); // imprime o status do botão + nova linha
    // IF THE CHANGED VALUE IS LOW
    if ( debouncedInput == LOW ) {
      ledState = !ledState; // SET ledState TO THE OPPOSITE OF ledState
      digitalWrite(LED_PIN,ledState); // WRITE THE NEW ledState
    }
  }
}