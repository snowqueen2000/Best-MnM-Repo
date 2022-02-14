#include <Encoder.h>

int mp1 = 5;
int mp2 = 6;

double f = 0.5; // frequency in Hz

Encoder myEnc(50, 51);

// === GLOBAL VARIABLES === //
double GearRatio = 313;         // the gear ratio
int countsPerRev_motor = 20;   // the counts per revolution of the motor shaft
long counts = 0;               // Globally initialize encoder counts

//time variables
unsigned long t_ms = 0;
double t = 0;                 // current time
double t_old_enc = 0;         // previous encoder sample time
double t_old_mot = 0;         // previous motor sample time
double Pos = 0;               // current pos
double Vel = 0;               // current velocity
double Pos_old = 0;           // previous pos
double T_enc=0.1;            // sample period in seconds
double T_motor=0.01;         // motor control sample time

void setup() {
  Serial.begin(9600); 
  pinMode(mp1, OUTPUT);
  pinMode(mp2, OUTPUT);
}

void loop() {
  digitalWrite(mp1, LOW);
  digitalWrite(mp2, HIGH);

  t_ms = millis();
  t = t_ms / 1000.0;  

if (t>t_old_enc+T_enc) {
// === Position and Velocity === //
  counts = myEnc.read();  // get current counts
  Pos = (counts*2*3.14159)/(20*313);               // Position in rad
  Vel = (Pos - Pos_old)/(t - t_old_enc);           // Velocity in rad/sec 

  Serial.print(t, 5);     // print time; comment out if using the serial plotter
  Serial.print(",\t");     // tab command
  Serial.print(Pos, 5);   // print position
  Serial.print(",\t");
  Serial.println(Vel, 5); // print velocity
  
  Pos_old = Pos;
t_old_enc = t; //save current time and position
}
}
