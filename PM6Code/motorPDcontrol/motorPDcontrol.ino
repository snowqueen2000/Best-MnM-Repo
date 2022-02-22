#include <Encoder.h>

const int mp1 = 6;
const int mp2 = 7;
const int mPWM = 5;

double f = 0.5; // frequency in Hz
// hello
Encoder myEnc(20,21);

// === GLOBAL VARIABLES === //
const double GearRatio = 313;         // the gear ratio
const int countsPerRev_motor = 20;   // the counts per revolution of the motor shaft
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

//Controller variables
double Pos_desired = 0;
double acceptableError = 2;

//Controller gains. NEED TUNING
double Kp  = 2;
double Kd = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(mp1, OUTPUT);
  pinMode(mp2, OUTPUT);
}

void loop() {

  t_ms = millis();
  t = t_ms / 1000.0;  

//  if(t_ms % 4000 == 0 && t_ms%8000 != 0) {
//    digitalWrite(mp1, LOW);
//    digitalWrite(mp2, HIGH);
//  } else if(t_ms%8000 == 0) {
//    digitalWrite(mp1, HIGH);
//    digitalWrite(mp2, LOW);
//
//  }

//=======
  if (t>t_old_enc+T_enc) {
  // === Position and Velocity === //
    counts = myEnc.read();  // get current counts
    Pos = (counts*360)/(20*313);               // Position in deg
    Vel = (Pos - Pos_old)/(t - t_old_enc);           // Velocity in deg/sec 
  
//    Serial.print(t, 5);     // print time; comment out if using the serial plotter
//    Serial.print(",\t");     // tab command
//    Serial.print(Pos, 5);   // print position
//    Serial.print(",\t");
//    Serial.println(Vel, 5); // print velocity
    
    Pos_old = Pos;
    t_old_enc = t; //save current time and position





    //Loop position back to zero if it gets over 360 degrees
    if(Pos >= 360.0) {
      Pos = Pos - 360.0;
    }

    //If motor is at the desired position.
    if(abs(Pos - Pos_desired) < acceptableError || abs((Pos-360.0) - Pos_desired) < acceptableError || abs(Pos - (Pos_desired - 360.0)) < acceptableError) {
      Serial.println("Please enter an integer position in degrees from 0 to 359");
      if(Serial.available()>0) {
        Pos_desired = Serial.parseInt();
      }
    }

    double input = Kp*(Pos - Pos_desired);
    
    input = input + Kd*Vel;
    
    //Ensure values are something that the motor controller can provide
    input = constrain(input, -10.0, 10.0);
  
    //Send command to motor
    motorCommand(mp1, mp2, mPWM, input);

  }

}

void motorCommand(int mpa, int mpb, int PWM, double command) {

  if(command > 0) {
    digitalWrite(mpa, HIGH);
    digitalWrite(mpb, LOW);
  } else {
    digitalWrite(mpa, LOW);
    digitalWrite(mpb, HIGH);
  }
  analogWrite(PWM, command);
  
}
