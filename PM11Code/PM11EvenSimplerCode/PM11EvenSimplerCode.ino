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
int colorDetect = 2; // R=1, G=2. Bl=3, Ye=4, Or=5, Br=6, empty=0

// OLED Variables
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
const int OLED_Color = colorDetect;

//start button pins
int startButton = 46;

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
Encoder myEnc(18, 19); // initialize encoder A out --> 18, B out --> 19

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
double T_enc = 0.05;          // sample period in seconds
double T_motor = 0.01;        // motor control sample time
double T_movement = 0.9;      // Movement Delay in seconds
double T_moveOld = 0;
double T_color = 0.1;
double t_color_old = 0;
double t_checks_old = 0;
double T_checks = 0.1; //How often (in seconds) to check the stops and communicate with modules
double t_move_old = 0;
double t_OLED_old = 0;
double T_OLED = 0.5;


int movementProgress = 0;

// Controller variables
double Pos_desired = 0;
double Vel_desired = 0;
double error_old = 0;

//Loop speed measurement
double loopSpeed = 0;
double oldLoopTime = 0;
double runs = 0;

//Color sensor variables
double vals[] = {0, 0, 0};               // array to store three color reading
int instVals[3];
int colorReadings = 0;
int maxColorReadings = 5;

int redCount = 0;
int greenCount = 0;
int blueCount = 0;
int candySorted = 0;

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

double rv[] = {650, 645, 679, 676, 44, 43}; //u BGR
double blv[] = {43, 40, 246, 229, 676, 672} ; //u
double gv[] = {426, 416, 37,  37,  493, 489}; //u
double brv[] = {706, 688, 721, 702, 660, 641}; //u
double yev[] = {649, 598, 37, 36, 33, 32}; //u
double orv[] = {640, 632, 666, 665, 34, 33}; //u
double emptyv[] = {758, 751, 684, 680, 759, 751}; //u

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

//color values storage
//int senseSlot = 0;
int gate1 = 0;
int gate2 = 0;


//metal values storage
int metalSlot = 0;
int metalGate1 = 0;
int metalGate2 = 0;

//Variable can be changed by ANY OTHER module's estop or previous module's queue sensor.
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
  qtr.setSensorPins((const uint8_t[]) {
    22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42
  }, SensorCount);
  qtr.setEmitterPin(2);

  for (int i = 0; i < 6; i += 2) {    //comment for test
    rv[i] = r[i / 2] + lightError;
    rv[i + 1] = r[i / 2] - lightError;
    blv[i] = bl[i / 2] + lightError;
    blv[i + 1] = bl[i / 2] - lightError;
    gv[i] = g[i / 2] + lightError;
    gv[i + 1] = g[i / 2] - lightError;
    brv[i] = br[i / 2] + lightError;
    brv[i + 1] = br[i / 2] - lightError;
    yev[i] = ye[i / 2] + lightError;
    yev[i + 1] = ye[i / 2] - lightError;
    orv[i] = ora[i / 2] + lightError;
    orv[i + 1] = ora[i / 2] - lightError;
    emptyv[i] = empty[i / 2] + lightError;
    emptyv[i + 1] = empty[i / 2] - lightError;

  }

  for (int i = 0; i < 6; i++) {
    Serial.print("Blue max/mins: "); Serial.println(blv[i]);
  }

  startup();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

}

void loop() {

  t_ms = millis();
  t = t_ms / 1000.0;

  //Stopper checks and communication
  if (t > t_checks_old + T_checks) {
    //Run communication function
    //Check interlock
    IR();

    //Send messages to other modules and check interlock, estop, communication.
    communication();

    t_checks_old = t;


    //Stop motor if needed
    if (irStopped || commStopped || estopped) {
      motorCommand(mp1, mp2, mPWM, 0);
      motorCommand(hop1, hop2, hopPWM, 0);

      setLED(1, 1, 1);

      if (digitalRead(startButton) == 0) {
        irStopped = false;
        estopped = false;
        Serial.println("Sorting resumed!");
      }
    }



  }

  //Queue and OLED
  if (t > t_OLED_old + T_OLED) {

    //Update Queue
    Qsensing();

    //Update OLED
    OLED(OLED_Color);
    t_OLED_old = t;
  }

  //Enocder stuff
  if (t > t_old_enc + T_enc && !irStopped && !commStopped && !estopped) {

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

  }

  //Movement loop
  if (!irStopped && !commStopped && !estopped) {
    switch (movementProgress) {


      case 0:
        //Rotate 30 degrees
        Pos_desired += 30;

        movementProgress = 1;
        break;

      case 1:
        //Wait until rotation completes
        if (abs(Pos - Pos_desired) < 10) {
          movementProgress = 2;
        }
        break;

      case 2:
        //Open gates if needed
        servoChecks();

        t_servo_old = t;

        movementProgress = 3;
        //reset color sensing values from the previous candy
        vals[0] = 0;
        vals[1] = 0;
        vals[2] = 0;

        Breadings = 0;
        Greadings = 0;
        Rreadings = 0;

        break;

      case 3:

          //Runs color sensor
          if (t > t_colorOld + T_color) { //color timing check
            colorSensor();

            t_colorOld = t;
          }

          //Once all readings are taken, Store what color that candy is and move on to next step.
          if (colorReadings >= maxColorReadings) {
            vals[0] = vals[0] / maxColorReadings;
            vals[1] = vals[1] / maxColorReadings;
            vals[2] = vals[2] / maxColorReadings;

            Serial.println(vals[0]);
            Serial.println(vals[1]);
            Serial.println(vals[2]);
            
            storeCandy();
            movementProgress = 4;
//            Serial.print("gate 1: "); Serial.println(gate1);
//            Serial.print("gate 2: "); Serial.println(gate2);
          }

        }
        metalDetect();
        //Color/metal sense until enough data points are taken, then move on
        if (metalGate1 == 0 || true) { //TEMPORARY UNTIL WE GET HALL SENSORS SET UP

          if (colorToSense == 'B') {
            //Turn on BLUE LED
            setLED(0, 1, 1);
            if (firstCheck) {
              t_color_old = t;
              firstCheck = false;
            }

            if (t > t_color_old + T_color) {
              colorSense(0);
              Breadings++;
              colorToSense = 'G';
              firstCheck = true;
              //setLED(0, 0, 0);
            }
          } else if (colorToSense == 'G') {
            //Turn on GREEN LED
            setLED(1, 0, 1);
            if (firstCheck) {
              t_color_old = t;
              firstCheck = false;
            }

            if (t > t_color_old + T_color) {
              colorSense(1);
              Greadings++;
              colorToSense = 'R';
              firstCheck = true;
              //setLED(0, 0, 0);
            }
          } else if (colorToSense == 'R') {
            //Turn on RED LED
            setLED(1, 1, 0);
            if (firstCheck) {
              t_color_old = t;
              firstCheck = false;
            }

            if (t > t_color_old + T_color) {
              colorSense(2);
              Rreadings++;
              colorToSense = 'B';
              firstCheck = true;
              //setLED(0, 0, 0);
            }

          }

          if (Breadings >= 1 && Greadings >= 1 && Rreadings >= 1) {
            movementProgress = 4;
          }


        } else { //If there's a nut under the color sensor, move to the next step
          movementProgress = 4;
        }


        break;

      //Average color sensor values and decide what color it is
      case 4:

        setLED(1, 1, 1);

        Serial.print("B: "); Serial.print(vals[0]);
        Serial.print(" G: "); Serial.print(vals[1]);
        Serial.print(" R: "); Serial.println(vals[2]);

        storeCandy();
        movementProgress = 5;
        break;

      //delay for servos NEED TO ADD
      case 5:
        if (t > t_servo_old + T_servo) {
          movementProgress = 6;
        }
        break;

      case 6:
        //close gates. Might need to add a "delay" here so that the gates close before the motor starts moving.
        CloseGate1();
        CloseGate2();
        movementProgress = 7;
        break;

      case 7:
        //Update virtual conveyer and reset to progress to 0.

        gate2 = gate1;
        //gate1 = senseSlot;

        metalGate2 = metalGate1;
        metalGate1 = metalSlot;
        metalSlot = 0;

        movementProgress = 0;
        break;
    }

    T_moveOld = t;
  }

  //Serial.print("MovementProgress: "); Serial.println(movementProgress);

}
