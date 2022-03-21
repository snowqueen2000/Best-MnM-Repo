#include <QTRSensors.h>
#include <Encoder.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


const int mp1 = 6;
const int mp2 = 7;
const int mPWM = 5;


QTRSensors qtr;
Encoder myEnc(18,19);

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

//queue sensor variables
int Qsize = 0;
int maxQsize = 6;
const uint8_t SensorCount = 11;
uint16_t sensorValues[SensorCount];

//OLED variables/set up
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//Variables signal from above
int SignalAbove = 51;    
int val = 0;  

char input[] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

void setup() {
  Serial.begin(9600); 
  pinMode(mp1, OUTPUT);
  pinMode(mp2, OUTPUT);
  pinMode(SignalAbove, INPUT);
  //initialize servos
  servo1.attach(servo1Pin); 
  servo2.attach(servo2Pin); 
  servo1.write(0);              
  servo2.write(0);

  //initialize Queue sensor
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){22,24,26,28,30,32,34,36,38,40,42}, SensorCount);
  qtr.setEmitterPin(2);

  //initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  startUp();
  
}

void loop() {

  t_ms = millis();
  t = t_ms / 1000.0;  

  //Serial.println(t_ms);
 

  
  
  //Reads sensor value and translates that into number of candies in the queue (Qsize). Also sends messages to previous module if needed.
  Qsensing();

  debugPrinter(2);
  
  //if stop has been triggered somewhere (see Qsensing), turn off the motor.
  //if(stopper) {
   // motorCommand(mp1,mp2,mPWM,0);
  //}
  
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
    motorCommand(mp1, mp2, mPWM, 4);
    
  //val = digitalRead(SignalAbove); // read the input pin
  //if(val == 1) {
  //  motorCommand(mp1, mp2, mPWM, 0);
  //  Serial.print("Inside if");
  //}
  
    
    Pos_old = Pos;
    t_old_enc = t; //save current time and position

    //updates OLED screen
    screen();
 
  }

  //sensing code and virtual conveyer.
  storeCandies();

  

}
