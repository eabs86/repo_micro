#include <Bounce2.h>

#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 3

#define LED_PIN1 10
#define LED_PIN2 11

// Instantiate Bounce objects
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 

// State variables for LEDs
bool previousStateLED1 = LOW;
bool previousStateLED2 = LOW;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Setup the first button with an internal pull-up
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance
  debouncer1.attach(BUTTON_PIN_1);
  debouncer1.interval(5); // interval in ms
  
  // Setup the second button with an internal pull-up
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance
  debouncer2.attach(BUTTON_PIN_2);
  debouncer2.interval(5); // interval in ms

  // Setup the LEDs
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}

void loop() {
  // Update the Bounce instances
  debouncer1.update();
  debouncer2.update();

  // Get the updated value
  int value1 = debouncer1.read();
  int value2 = debouncer2.read();

  // Control and print status of LED1
  if (value1 == LOW) {
    digitalWrite(LED_PIN1, HIGH);
    if (previousStateLED1 != HIGH) {
      Serial.println("LED 1 is ON");
      previousStateLED1 = HIGH;
    }
  } else {
    digitalWrite(LED_PIN1, LOW);
    if (previousStateLED1 != LOW) {
      Serial.println("LED 1 is OFF");
      previousStateLED1 = LOW;
    }
  }

  // Control and print status of LED2
  if (value2 == LOW) {
    digitalWrite(LED_PIN2, HIGH);
    if (previousStateLED2 != HIGH) {
      Serial.println("LED 2 is ON");
      previousStateLED2 = HIGH;
    }
  } else {
    digitalWrite(LED_PIN2, LOW);
    if (previousStateLED2 != LOW) {
      Serial.println("LED 2 is OFF");
      previousStateLED2 = LOW;
    }
  }
}
