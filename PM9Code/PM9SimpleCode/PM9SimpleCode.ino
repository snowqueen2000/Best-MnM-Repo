#include <QTRSensors.h>
#include <Encoder.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <SharpIR.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//CHANGE FOR EACH PERSON
int deviceAddress = 3;
// Color to sort
int colorDetect = 1; // R=1, G=2. Bl=3, Br=4, Ye=5, Or=6

// OLED Variables
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
const int OLED_Color = colorDetect;

//start button pins
int startButton = 46;

// color sensor
int redCount = 0;
int greenCount = 0;
int blueCount = 0;
int candySorted = 0;

//LED variables
#define blue_pin 13
#define green_pin 12
#define red_pin 11

// motor driver 
const int mPWM = 5;
const int mp1 = 6;
const int mp2 = 7;

//Hopper motor pins
const int hopPWM = 3;
const int hop1 = 1;
const int hop2 = 2;

// encoder
Encoder myEnc(18,19); // initialize encoder A out --> 18, B out --> 19

//servos
Servo servo1;
Servo servo2;

//servo pins
const int servo1Pin = 9;
const int servo2Pin = 10;

// Q sensor
QTRSensors qtr;
int Qsize = 0;
int maxQsize = 5;
const uint8_t SensorCount = 11;
uint16_t sensorValues[SensorCount];

// IR Sensor
#define IRPin A3
#define model 430 // 430 means 4 to 30 cm it works
int IRdist;
SharpIR mySensor = SharpIR(IRPin, model);

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
double T_movement = 3;      // Movement Delay in seconds
double T_moveOld = 0;
double T_color = 0.04;
double t_colorOld = 0;
double T_oled=3;
double t_old_oled=0;


// Controller variables
double Pos_desired = 0;
double Vel_desired = 0;
double error_old = 0;

//Loop speed measurement
double loopSpeed = 0;
double oldLoopTime = 0;
double runs = 0;

//Color sensor variables
int vals[3];                 // array to store three color reading 

//Color sensor calibartion values
//bgr:  max, min, max, min, max, min
//double rv[6];           //comment for test
//double blv[6];
//double gv[6];
//double brv[6];
//double yev[6];
//double orv[6];
//double emptyv[6];
//double wheelv[6];


//double r[] = {650, 650, 100}; //u       //comment for test 
//double bl[] = {757, 700, 863}; //u
//double g[] = {844, 634, 858}; //u
//double br[] = {853, 754, 858}; //u
//double ye[] = {831, 523, 739}; //u
//double ora[] = {845, 735, 751}; //u
//double empty[] = {852, 766, 860}; //u
//double wheel[] = {};

double rv[] = {676, 481, 736, 665, 410, 300}; //u BGR
double blv[] = {780, 35, 638, 185, 782, 229} ; //u
double gv[] = {522, 400, 445, 300, 714, 574}; //u 
double brv[] = {748, 636, 710, 546, 713, 409}; //u  
double yev[] = {667, 317, 487, 300, 736, 600}; //u  
double orv[] = {676, 239, 665, 400, 371, 200}; //u
double emptyv[] = {873, 397, 722, 479, 876, 486}; //u

double r[] = {31, 31, 23}; //u       //comment for test 
double bl[] = {21, 25, 35}; //u
double g[] = {28, 22, 30}; //u
double br[] = {30, 33, 31}; //u
double ye[] = {28, 21, 20}; //u
double ora[] = {30, 34, 20}; //u
double empty[] = {48, 49, 45}; //u
double wheel[] = {};

//double rv[] = {60, 10, 80, 0, 40, 10}; //Tren's
//double blv[] = {50, 0, 50, 0, 200, 150}; //u
//double gv[] = {60, 10, 50, 0, 60, 10}; //u 
//double brv[] = {60, 10, 60, 10, 60, 10}; //u  
//double yev[] = {60, 0, 50, 10, 50, 10}; //u  
//double orv[] = {41, 31, 49, 39, 28, 18}; //u
//double emptyv[] = {430, 390, 430, 390, 600, 540}; //u

double wheelv[] = {};

int lightError = 5;

int senseSlot = 0;
int gate1 = 0;
int gate2 = 0;

//Variable can be changed by ANY OTHER module's estop or previous modulu's queue sensor.
//bool stopSorting = false;
bool estopped = false;
bool commStopped = false;
bool irStopped = false;

void setup() {
  Serial.begin(9600); 
  pinMode(mp1, OUTPUT);
  pinMode(mp2, OUTPUT); 

  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

  //turn off color sensor light
  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, HIGH);
  digitalWrite(blue_pin, HIGH);
  
  //initialize servos
  servo1.attach(servo1Pin); 
  servo2.attach(servo2Pin); 
  servo1.write(0);              
  servo2.write(0);

  // Initialize Queue sensor 
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){22,24,26,28,30,32,34,36,38,40,42}, SensorCount);
  qtr.setEmitterPin(2);
  
  for(int i = 0; i < 6; i+=2) {       //comment for test 
    rv[i] = r[i/2] + lightError; 
    rv[i+1] = r[i/2] - lightError;
    blv[i] = bl[i/2] + lightError;
    blv[i+1] = bl[i/2] - lightError;
    gv[i] = g[i/2] + lightError;
    gv[i+1] = g[i/2] - lightError;
    brv[i] = br[i/2] + lightError;
    brv[i+1] = br[i/2] - lightError;
    yev[i] = ye[i/2] + lightError;
    yev[i+1] = ye[i/2] - lightError;
    orv[i] = ora[i/2] + lightError;
    orv[i+1] = ora[i/2] - lightError;
    emptyv[i] = empty[i/2] + lightError;
    emptyv[i+1] = empty[i/2] - lightError;
    
  }
  
  for(int i = 0; i < 6; i++) {
    Serial.print("Blue max/mins: "); Serial.println(blv[i]);
  }

  startup();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

}

void loop() {

  //Serial.print("stopSorting: "); Serial.println(stopSorting);
  
  t_ms = millis();
  t = t_ms / 1000.0;  

  //calculate how fast the loop is running
  //loopSpeed = (t_ms - oldLoopTime);
  // Serial.print("Loop speed: ");
  // Serial.println(loopSpeed);

  // Queue sensing
  Qsensing();

  // update OLED
  //OLED(OLED_Color);

  // Run IR Sensor
  IR();


  //Send messages to other modules
  communication();
  
  // Only run every timestep
  if (t>t_old_enc+T_enc && !irStopped && !commStopped && !estopped) {

    //Read encoder counts and calculate position/velocity
    EncoderCalcs();
    
    // Convert voltage to position using PID controller    
    double input = PID_controller();
    
    //Send command to motor
    motorCommand(mp1, mp2, mPWM, input);

    //Send command to hopper motor
    motorCommand(hop1, hop2, hopPWM, 10);
    
    Pos_old = Pos;
    t_old_enc = t; //save current time and position

    // calculations for finding loop speed
    oldLoopTime = t_ms;
    runs++;

  }
  
// OLED Timing
//if (t>t_old_oled+T_oled) {
//OLED(OLED_Color);
//t_old_oled=t;
//  
//}

  //Check button


  //Comand
  if(irStopped || commStopped || estopped) {
    motorCommand(mp1, mp2, mPWM, 0);

    if(digitalRead(startButton) == 0) {
      irStopped = false;
      Serial.println("Sorting resumed!");
    }
  }


  if(t > t_colorOld + T_color) {
    colorSensor();
    t_colorOld = t;
  }


  //Rotate to next 30 degree slot
  if(t > T_moveOld + T_movement && !irStopped && !commStopped && !estopped ) {

//    //These might need to move to somewhere else if they don't open for long enough.
//    CloseGate1();
//    CloseGate2();
    
    //Decide what color candy is under the sensor and which slot it will need to go to
    OLED(OLED_Color);
    storeCandy();
    colorSensor();
    //Assign colors to slots
    Serial.print("senseSlot: "); Serial.println(senseSlot);
    Serial.print("gate 1: "); Serial.println(gate1);
    Serial.print("gate 2: "); Serial.println(gate2);

    //Move servos
    servoChecks();
    
    //update the virtual slots
    gate2 = gate1;
    gate1 = senseSlot;


    
    //Move to next position
    Pos_desired += 30;
    T_moveOld = t;
    


  }

}
