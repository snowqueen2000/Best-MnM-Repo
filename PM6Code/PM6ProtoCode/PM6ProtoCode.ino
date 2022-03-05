#include <QTRSensors.h>
#include <Encoder.h>
#include <Servo.h>

const int mp1 = 6;
const int mp2 = 7;
const int mPWM = 5;


Encoder myEnc(20,21);

//Attach servos
Servo servo1;
Servo servo2;

//servo pins
const int servo1Pin = 9;
const int servo2Pin = 10;

//time variables
unsigned long t_ms = 0;
double t = 0;                 // current time
double t_old_enc = 0;         // previous encoder sample time
double t_old_mot = 0;         // previous motor sample time
double Pos = 0;               // current pos
double Vel = 0;               // current velocity
double Pos_old = 0;           // previous pos
double T_enc=0.05;            // sample period in seconds
double T_motor=0.01;         // motor control sample time

//Controller variables
double Pos_desired = 0;
double error_old = 0;

//Sensor variables
char senseSlot = 'n';
char gate1Slot = 'n';
char gate2Slot = 'n';
char gate3Slot = 'n';
char stopper = false;

int Qsize = 0;

char input[] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

void setup() {
  Serial.begin(9600); 
  pinMode(mp1, OUTPUT);
  pinMode(mp2, OUTPUT);

  //initialize servos
  servo1.attach(servo1Pin); 
  servo2.attach(servo2Pin); 
  servo1.write(0);              
  servo2.write(0);

  startUp();
  
}

void loop() {

  t_ms = millis();
  t = t_ms / 1000.0;  

  //Reads sensor value and translates that into number of candies in the queue (Qsize). Also sends messages to previous module if needed.
  Qsensing();
  
  //if stop has been triggered somewhere (see Qsensing), turn off the motor.
  if(stopper) {
    motorCommand(mp1,mp2,mPWM,0);
  }
  
  //Only run every timestep
  if (t>t_old_enc+T_enc && !stopper) {

 
    //Read encoder counts and calculate position/velocity
    EncoderCalcs();
    
    
    //Checks current position and decides which gates to open/close
    servoChecks();

    //Change parameter to 0 if nothing should be printed.
    debugPrinter(1);


    //Convert voltage to position using PID controller
    double input = PID_controller();
    
    //Send command to motor
    motorCommand(mp1, mp2, mPWM, input);

    Pos_old = Pos;
    t_old_enc = t; //save current time and position

 
  }

  //sensing code and virtual conveyer.
  storeCandies();

  //updates OLED screen
  screen();  

}
