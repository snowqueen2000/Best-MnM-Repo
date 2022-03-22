#include <Encoder.h>

const int mp1 = 6;
const int mp2 = 7;
const int mPWM = 5;

Encoder myEnc(18,19);

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
double error_old = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(mp1, OUTPUT);
  pinMode(mp2, OUTPUT);
}

void loop() {

  t_ms = millis();
  t = t_ms / 1000.0;  

  //Only run every timestep
  if (t>t_old_enc+T_enc) {

    //Read encoder counts and calculate position/velocity
    EncoderCalcs();

    //Change parameter to 0 if nothing should be printed.
    debugPrinter(1);

    //ask user for the desired position to rotate to
    if(Serial.available()>0) {
        Pos_desired = Serial.parseInt();
        Serial.read();
        Serial.print("Desired position: ");
        Serial.println(Pos_desired);
      }  

    //Convert voltage to position using PID controller
    double input = PID_controller();
    
    //Send command to motor
    motorCommand(mp1, mp2, mPWM, input);

    Pos_old = Pos;
    t_old_enc = t; //save current time and position

  }

}
