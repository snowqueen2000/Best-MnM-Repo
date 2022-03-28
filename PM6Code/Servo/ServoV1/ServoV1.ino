#include <Servo.h>

Servo servoW; // Servo attatched to white wire
Servo servoG; // Servo attatched to grey wire

int pos = 0; 

void setup() {
  //Serial.begin(9600);
  servoW.attach(10); // white wire to digital pin 10
  servoG.attach(9); // grey wire to digital pin 9
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoW.write(pos); // tell servo to go to position in variable 'pos'
    servoG.write(pos);
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servoW.write(pos);              // tell servo to go to position in variable 'pos'
    servoG.write(pos);
    delay(5);                       // waits 15ms for the servo to reach the position
  }
}
