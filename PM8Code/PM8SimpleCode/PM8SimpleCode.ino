#include <QTRSensors.h>
#include <Encoder.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Color detected 
int colorDetect = 1; // R=1, G=2. B=3

// OLED Variables
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
const int OLED_Color = 4;

//LED variables
#define blue_pin 13
#define green_pin 12
#define red_pin 11

const int mPWM = 5;
const int mp1 = 6;
const int mp2 = 7;

Encoder myEnc(18,19); // initialize encoder A out --> 18, B out --> 19

// time variables
unsigned long t_ms = 0;
double t = 0;                 // current time
double t_old_enc = 0;         // previous encoder sample time
double t_old_mot = 0;         // previous motor sample time
double Pos = 0;               // current position
double Vel = 0;               // current velocity
double Pos_old = 0;           // previous position
double T_enc=0.05;            // sample period in seconds
double T_motor=0.01;          // motor control sample time
double T_movement = 0.9;      // Movement Delay in seconds
double T_moveOld = 0;
double T_color = 0.04;
double t_colorOld = 0;

// Controller variables
double Pos_desired = 0;
double Vel_desired = 0.3;
double error_old = 0;

//Loop speed measurement
double loopSpeed = 0;
double oldLoopTime = 0;
double runs = 0;

//Color sensor variables
int vals[3];                 // array to store three color reading 

void setup() {
  Serial.begin(9600); 
  pinMode(mp1, OUTPUT);
  pinMode(mp2, OUTPUT); 

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  t_ms = millis();
  t = t_ms / 1000.0;  

  //calculate how fast the loop is running
  loopSpeed = (t_ms - oldLoopTime);
  // Serial.print("Loop speed: ");
  // Serial.println(loopSpeed);

  // Only run every timestep
  if (t>t_old_enc+T_enc) {

    //Read encoder counts and calculate position/velocity
    EncoderCalcs();
    
    // Convert voltage to position using PID controller    
    double input = PID_controller();
    
    //Send command to motor
    motorCommand(mp1, mp2, mPWM, input);

    Pos_old = Pos;
    t_old_enc = t; //save current time and position

    // calculations for finding loop speed
    oldLoopTime = t_ms;
    runs++;
  }


  if(t > t_colorOld + T_color) {
    colorSensor();
    t_colorOld = t;
  }


  //Rotate to next 30 degree slot
  if(t > T_moveOld + T_movement) {
    //Decide what color candy is under the sensor and which slot it will need to go to
    storeCandy();
    
    //update the virtual slots

    //Move servos

    //Move to next position
    Pos_desired += 30;
    T_moveOld = t;

    // update OLED
    OLED(OLED_Color);
  }

}
