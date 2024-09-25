const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);

  Serial.begin(9600);
}

void loop() {
  boolean ex = debounce(buttonPin);
  digitalWrite(ledPin,ex);
  
}



boolean debounce(int pin)
{
  int reading = digitalRead(pin);

  
  if (reading != lastButtonState) {
    
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    if (reading != buttonState) {
      buttonState = reading;

     
      if (buttonState == LOW) {
        ledState = !ledState;
        Serial.println(buttonState);
      }
    }
  }

  
  //digitalWrite(ledPin, ledState);

  
  lastButtonState = reading;

  return ledState;
}
