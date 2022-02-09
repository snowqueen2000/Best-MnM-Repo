#include "DualVNH5019MotorShield.h"

#include "Encoder.h"

DualVNH5019MotorShield md;

// === CHANGING FREQUENCY === //
double f = 0.5;                    //frequency in Hz

// === CHANGING ENCODER PINS === //
//Use only a SINGLE instance of Encoder.  Uncomment the version taht you are evaluating
Encoder myEnc1(20, 21);      // Two-interupt instance of encoder
Encoder myEnc2(20, 53);      // One-interupt instance of encoder
Encoder myEnc3(52, 53);      // Zero-interupt instance


// === GLOBAL VARIABLES === //
double GearRatio = 50;         // the gear ratio
int countsPerRev_motor = 64;   // the counts per revolution of the motor shaft
long counts1 = 0;               // Globally initialize encoder counts
long counts2 = 0;
long counts3 = 0;

//time variables
unsigned long t_ms = 0;
double t = 0;                 // current time
double t_old_enc = 0;         // previous encoder sample time
double t_old_mot = 0;         // previous motor sample time
double Pos = 0;               // current pos
double Vel = 0;               // current velocity
double Pos_old = 0;           // previous pos
double T_enc=0.005;            // sample period in seconds. May need to tune to obtain sufficient counts between sample times.
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

if (t>t_old_enc+T_enc) {
  // !!!!! COMMENT OUT UNUSED SECTION !!!!! 

// === 4.3. Encoder sensing (FIRST HALF) === //
//  counts1 = myEnc1.read();                            // get current counts
//  counts2 = myEnc2.read();                            // get current counts
//  counts3 = myEnc3.read();
//  
//  Serial.print(t, 5);     // print time; comment out if using the serial plotter
//  Serial.print(",\t");     // tab command
//  Serial.print(counts1);
//  Serial.print(",\t");
//  Serial.print(counts2);
//  Serial.print(",\t");
//  Serial.println(counts3);
//  ========================================== //

// === 4.3.10 Position and Velocity (SECOND HALF) === //
  
    counts1 = myEnc1.read();                            // get current counts

   // !!!! === STUDENT INPUT POSITION AND VELOCITY CALCULATIONS !!!! === //
    Pos = (counts1*2*3.14159)/(64*50);               // Position in rad (removed for student calc)
    Vel = ((Pos - Pos_old))/((t - t_old_enc));              // Velocity in rad/sec (removed for student calc)

    Serial.print(t, 5);     // print time; comment out if using the serial plotter
    Serial.print(",\t");     // tab command
    Serial.print(Pos, 5);   // print position
    Serial.print(",\t");
  
    Serial.println(Vel, 5); // print velocity
  
    Pos_old = Pos;
// ================================================== //

t_old_enc = t; //save current time and position

}

if (t>t_old_mot+T_motor) {
int M = 400 * sin(2.0 * PI * f * t); // Sinusoid motor Voltage command
  md.setM1Speed(M);              // command voltage to motor
//  Serial.println(t,5);           // uncomment to check update rate
  t_old_mot=t;
}
}
