//
// PWMswitch -- based on Example Knob & Analog, works with Adafruit Trinket V5
//
// rwsenser, 2019/05/21
// version for GIT upload
// 
// Adruino IDE settings:
// board: "Adafruit Trinket (ATiny 85 @ 8mhz)"
// programmer: "USBtinyISP" 
//
/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include "Adafruit_Softservo.h"

const int PWMpin = 0;
const int LEDpin = 1;
const int SWITCHpin = 2;

const int deviceON = 179;
const int deviceOFF = 1;

int val;    // variable to read the value from the analog pin
int pwmData;
Adafruit_SoftServo Servo1;

void setup() {
  // pinMode(PWMpin, OUTPUT); 
  OCR0A = 0xAF;   // any number is OK
  TIMSK |= _BV(OCIE0A);  // Turn on the compare interuppt (below!)
  Servo1.attach(PWMpin);
  Servo1.write(deviceOFF);
  pinMode(SWITCHpin, INPUT_PULLUP);
  pinMode(LEDpin, OUTPUT);
  digitalWrite( LEDpin, LOW);  
}

void loop() {
  val = digitalRead(SWITCHpin);        // high is low angle, low is high angle!
  if (val) { // angle low, dim
    pwmData = deviceOFF;
  } else { // angle high, bright
    pwmData = deviceON;  
  }
  Servo1.write(pwmData);
  analogWrite(LEDpin, pwmData);        // LED maps output line...
  delay(50);                           // waits for the servo to get there
}

// We'll take advantage of the built in millis() timer that goes off
// to keep track of time, and refresh the servo every 20 milliseconds
volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    Servo1.refresh();
  }
}
