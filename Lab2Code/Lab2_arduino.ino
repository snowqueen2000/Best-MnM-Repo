#include "DualVNH5019MotorShield.h"
DualVNH5019MotorShield md;

const int Apin = 0; // Analog input pin for motor voltage
const int Dpin = 7; // GDigital input pin from DAQ
const int LEDpin = 13; // Digital output pin for LED

void setup() {
  Serial.begin(9600); // Initialize serial monitor
  pinMode(Dpin,INPUT); // Set Dpin as input
  pinMode(LEDpin,OUTPUT); // Set LEDpin as output
  md.init(); // Initialize motor controller
}

void loop() { 
  int button = digitalRead(Dpin);// Read DAQ digital state
  int Mval = analogRead(Apin); // Motor voltage 0-1023
  int M = 0;
  
  if(button) { //if true
    digitalWrite(LEDpin,HIGH); // then light the LED
    M = map(Mval,0,1024,-400,400); // motor control value
  }
  else{ //if false
    digitalWrite(LEDpin,LOW); // then turn off LED
    M = 0; // then don't power motor
  }
  //md.setM1Speed(M); // command voltage to motor
}
