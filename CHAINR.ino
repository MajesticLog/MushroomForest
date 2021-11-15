/*

  Secret Garden
  Chain reaction using a LDR, a Servo motor and LEDs
  Zoe Cuaudron

  ------------------------------

  The LDR detects if the light gets below a certain brightness (is turned off/dark),
  and the yellow LEDs gets turned on. A counter is started, and is reset if the lights are 
  turned back on.

  Once the counter reaches a certain time, the Servo motor activates - this should have then pulled
  a tilt switch, but my pin 9 and my tilt switch stopped working before I recorded the video,
  and subsequently got removed from the project. Once the Servo has turned a certain amount (that would 
  have pulled the tilt switch), the mushroom shell LEDs turn on and fade/pulse.

*/


#include <Servo.h>  // include Servo library

Servo myServo;      // declare Servo
int pos = 0;
int servR = 0;
int brightness = 5;
int cB = 0;            // pin fading brightness
int step = 5;
const int LDR = A0;    // declare LDR
int sensorValue = 0;   // gets LDR value
const int pinA = 6;    // declaring LEDs
const int pinB = 5;
const int pinC = 3;
const int pinD = 9;
const int pinE = 11;

//const int tilt = 2;   // the tilt sensor stopped working in the end so I removed it
//int tiltState = 0;
int shellBA = 5;        // mushroom LEDs brightness
int servStep = 0;

int counter = 0;        // counts loops once the room goes dark

//----------------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  myServo.attach(10);
  Serial.begin(9600);

}

//----------------------------------------------------------

void loop() {
  // put your main code here, to run repeatedly:

  sensorValue = analogRead(LDR);
  brightness = map(sensorValue, 0, 900, 255, 5);  // check perceived brightness
  cB = constrain(brightness, 10, 255);  // makes sure the brighness stays within the range

  if (brightness <= 100) { // if the room gets darker than that value

    delay(100);
    cB++;
    analogWrite(pinB, cB);
    analogWrite(pinA, cB);
    counter++;
    //     Serial.println(counter);

  }
  else { // reset

    analogWrite(pinB, 0);
    analogWrite(pinA, 0);
    analogWrite(pinC, 0);
    analogWrite(pinD, 0);
    analogWrite(pinE, 0);
    counter = 0;
    servR = 0;
  }


  delay(100);

  if (counter >= 300) {  // obce the room has been dark long enough for counter to reach 300
    delay(100);
    servStep++;
    servR += servStep;
    if (servR >= 180 || servR <= 0) {
      servStep = -servStep;
    }

    pos = constrain(servR, 0, 180);
    myServo.write(pos);
    Serial.println(servR);

    if (pos >= 10) {

      analogWrite(pinC, shellBA);
      analogWrite(pinD, shellBA);
      analogWrite(pinE, shellBA);
      shellBA += step;

      if (shellBA >= 130 || shellBA <= 5) {  // shells never fully bright or dark
        step = -step;
      }

    }

    else {
      analogWrite(pinC, 0);
      analogWrite(pinD, 0);
      analogWrite(pinE, 0);

    }
  }


}
