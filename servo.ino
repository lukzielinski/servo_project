// To turn it on press the button, to turn it off press and hold the button for 3 seconds.

#include <Servo.h>

#define BUTTON_PIN 7
#define SERVO_PIN 3

Servo myservo;

byte lastButtonState = LOW;
byte ledState = LOW;
int counter = 0;

unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButtonStateChanged = 0;

int ButtonPressCounter(byte buttonState) {            // check if the button was pressed
  buttonState = digitalRead(BUTTON_PIN);
    if(buttonState == HIGH) {
       counter += 1;
  }
  return counter;
}

void ServoPositionChange(byte buttonState) {
  int pos = 80;
  
   for(pos = 80; pos <= 120; pos += 5) {        // goes from 80 degrees to 120 degrees
    myservo.write(pos);                         // tell servo to go to position in variable 'pos'          
    delay(15);                                  // waits 15ms for the servo to reach the position
    ButtonPressCounter(buttonState);            // check if the button wasn't pressed
    if(pos == 95) {                             // delay to mute the string
      delay(1000);
    }
    if(pos == 120) {                            // delay to record sound of the string
    delay(3000);
    }
  }               
  for (pos = 120; pos >= 80; pos -= 5) {        // goes from 120 degrees to 80 degrees
    myservo.write(pos);                         // tell servo to go to position in variable 'pos'
    delay(15);                                  // waits 15ms for the servo to reach the position
    ButtonPressCounter(buttonState);            // check if the button wasn't pressed
    if(pos == 105) {                            // delay to mute the string
      delay(1000);
    }
    if(pos == 80) {                             // delay to record sound of the string
      delay(3000);
    } 
  }
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  myservo.attach(SERVO_PIN);
}
void loop() {
  if (millis() - lastTimeButtonStateChanged > debounceDuration) {     // delay to button reaction

  byte buttonState = digitalRead(BUTTON_PIN);

  if (buttonState != lastButtonState) {                               // condition connected with button turn on/off
    lastTimeButtonStateChanged = millis();
    lastButtonState = buttonState;
    while (buttonState == LOW){
      ServoPositionChange(buttonState);
      
      if (counter > 0){                                               // counter check, if true break the loop
        buttonState = HIGH;
        counter = 0;
        }
      }
    } 
  }
} 


