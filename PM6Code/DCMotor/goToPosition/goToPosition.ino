/* Code to run DC motor to an angle provided by the serial monitor.
 * Current state: The first few commands work well, but after that it won't stop in time?
 * 
 * 
 * 
 */
//test Omar :D
#include <Encoder.h>

//Default conveyer speed from 0 to 100%
int defaultSpeed = 50;

//map motor speed from 0 to 255 for PWM control
int PWMspeed = map(defaultSpeed, 0, 100, 0, 255);

//motor pins
int mp1 = 6;
int mp2 = 7;
int mPWM = 5;

double f = 0.5; // frequency in Hz

Encoder myEnc(20,21);

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
double T_enc=0.5;            // sample period in seconds
double T_motor=0.01;         // motor control sample time

double desiredPosition = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(mp1, OUTPUT);
  pinMode(mp2, OUTPUT);
  pinMode(mPWM, OUTPUT);

  
  
}

void loop() {
  
  t_ms = millis();
  t = t_ms / 1000.0;  

  //If something has been sent to the serial, update command variables
  if(Serial.available() > 0) {

      
      int dataRecieved = double(Serial.parseInt());
      if(dataRecieved != 0)
        desiredPosition = dataRecieved;

   
    //Serial.println(desiredPosition);
  }

  
  toPosition(desiredPosition);
  
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
  }

//Constrain position between 0 and 359
  if(Pos >= 360) {
    Pos = Pos - 360;
  }

}

void toPosition(int desiredPos) {

  //if position is outside  the deadzone, set speed
  if( abs(desiredPos - Pos) > 15.0 ) {
    analogWrite(mPWM, PWMspeed);
    digitalWrite(mp1, HIGH);
    digitalWrite(mp2, LOW);
    Serial.println("Moving...");
    
  } else if( abs(desiredPos - Pos) > 4.0 ) {
    analogWrite(mPWM, 25);
    digitalWrite(mp1, HIGH);
    digitalWrite(mp2, LOW);
    Serial.println("almost there...");
    
  } else {
    //analogWrite(mPWM, 0);
    digitalWrite(mp1, LOW);
    digitalWrite(mp2, LOW);
    Serial.println(desiredPos);
    Serial.println(Pos);
  }
  
}
