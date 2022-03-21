#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield md;

int f = 2;                        //frequency in Hz

//time variables
unsigned long t_ms = 0;
double t = 0;                 // current time
double t_old_mot = 0;         // previous motor sample time
double T_motor=0.01;         // motor control sample time.  Assures that the motor command has time to update between command updates.


// === SETUP LOOP === //
void setup() {
  md.init();                  // initialize motor controller
  Serial.begin(9600);         // initialize serial monitor
}

// === MAIN LOOP === //
void loop() {
  t_ms = micros();
  t = t_ms / 1000000.0;       // current time

if (t>t_old_mot+T_motor) {
int M = 400 * sin(2.0 * PI * f * t); // Sinusoid motor Voltage command
  md.setM1Speed(M);              // command voltage to motor
//  Serial.println(t,5);           // uncomment to check update rate
  t_old_mot=t;
}
}
