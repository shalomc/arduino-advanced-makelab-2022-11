const int ledPin = 13;          // choose the pin for the LED
const int inputPin = 2;         // choose the input pin (for a pushbutton)

int button_value = 0;                    // variable for reading the pin status
boolean is_turned_on = false;

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT_PULLUP);     // declare pushbutton as input
}

void loop() {
  button_value = digitalRead(inputPin);  // read input value
  delay(5); // allow button to stabilize
  // We initialized the input pin with INPUT_PULLUP
  // therefore LOW means pressed, HIGH means not pressed.
  if (button_value == LOW ) {            // check if the input is HIGH
    is_turned_on = !is_turned_on; // flip button
    digitalWrite(ledPin, is_turned_on);
    // loop while button pressed
    while (digitalRead(inputPin) == LOW) {
      delay(1);
    }
  }
  else {
    ;
    // This is a placeholder for things to do when the button is NOT pressed
  }

}
