
//Maximum times the color sensor can run per candy
int const maxDataPerCandy = 100;

int thisCandyR[maxDataPerCandy];
int thisCandyG[maxDataPerCandy];
int thisCandyB[maxDataPerCandy];

int readingIndex = 0;

//Calibrated values. Use Active_color_sensor-2 to recalibrate if needed.
  
    //bgr:  max, min, max, min, max, min
int rv[] = {36, 33, 34, 31, 34, 31};
int blv[]= {32, 28, 32, 29, 37, 34};
int gv[]= {36, 32, 31, 28, 36, 33};
int brv[]= {37, 34, 34, 31, 37, 34};
int yev[] = {36, 33, 31, 28, 32, 29};
int orv[] = {36, 33, 33, 30, 31, 28};

int redM;
int blueM;
int greenM;
int brownM;
int yellowM;
int orangeM;

int analogPin = A0;
int vals[3];                 // array to store three color reading 
int delayTime = 40;          // delay between readings to allow phototransistor to come to steady state
char serialByte = '0';        // incoming serial byte to read desired driving mode


int timeOld = 0;

char lightColor = 'b';

/* Updates the variable input with the mnm reading. Constantly runs while MnM is under the sensor.
 * This function is called by the storeCandies() function.
 */
void colorSensor(bool newCandy) {
  double avgR = 0;
  double avgG = 0;
  double avgB = 0;
  
  //if newCandy is true, the sensor has started reading a new candy and the array needs to restart at zero
  if(newCandy) {
    readingIndex = 0;
  }

  long timeCurrent = millis();
  //Serial.print("current time: ");
  //Serial.println(timeCurrent);
  if(timeCurrent - delayTime >= timeOld) {

    if(lightColor == 'b') {

      // set LED color to blue
      digitalWrite(blue_pin, HIGH);   
      digitalWrite(green_pin,LOW);
      digitalWrite(red_pin,LOW);

      vals[0] = analogRead(analogPin); // read phototransistor and store value
        //Serial.print(vals[0]);Serial.print(", "); // print stored value.
      
      lightColor = 'g';
    } else if(lightColor == 'g') {

      // set LED color to green                       
      digitalWrite(blue_pin,LOW);   
      digitalWrite(green_pin,HIGH);
      digitalWrite(red_pin,LOW);

      vals[1] = analogRead(analogPin); // read phototransistor and store value
        //Serial.print(vals[1]);Serial.print(", ");  // print stored value.
      
      lightColor = 'r';
    } else if(lightColor == 'r') {

      // set LED color to Red
      digitalWrite(blue_pin,LOW);   
      digitalWrite(green_pin,LOW);
      digitalWrite(red_pin,HIGH);

      vals[2] = analogRead(analogPin); // read phototransistor and store value
        //Serial.println(vals[2]); // print stored value.
      
      lightColor = 'b';
    }


    timeOld = timeCurrent;
  }



      // turn off LED and wait for another cycle
      //digitalWrite(blue_pin,LOW);
      //digitalWrite(green_pin,LOW);
      //digitalWrite(red_pin,LOW);
  




  //record one set of RGB readings
  thisCandyR[readingIndex] = vals[2];
  thisCandyG[readingIndex] = vals[1];
  thisCandyB[readingIndex] = vals[0];



  //Increment which reading this is
  readingIndex++;

  //Average all RGB values up to readingIndex. Need to start index at 1 to avoid /0 error.
  for(int i = 1; i < readingIndex+1; i++) {
    avgR = (avgR + thisCandyR[i-1])/i;
    avgG = (avgG + thisCandyG[i-1])/i;
    avgB = (avgB + thisCandyB[i-1])/i;
  }

  //Compare average RGB values to experimentally determined values for each MnM.
  if((avgB<rv[0] && avgB>rv[1]) && (avgG<rv[2] && avgG>rv[3]) && (avgR<rv[4] && avgR>rv[5]))
      {
        Serial.println("Is Red!");
        redM=1;
      }
        else{
          redM=0;
        }
        
      

       if((avgB<blv[0] && avgB>blv[1]) && (avgG<blv[2] && avgG>blv[3]) && (avgR<blv[4] && avgR>blv[5]))
      {
        Serial.println("Is Blue!");;
        blueM=1;
      }
        else
        {
          blueM=0;
        }
      

      if((avgB<gv[0] && avgB>gv[1]) && (avgG<gv[2] && avgG>gv[3]) && (avgR<gv[4] && avgR>gv[5]))
      {
        Serial.println("Is Green!");;
        greenM=1;
      }
        else{
          greenM=0;
        }
      

      if((avgB<brv[0] && avgB>brv[1]) && (avgG<brv[2] && avgG>brv[3]) && (avgR<brv[4] && avgR>brv[5]))
      {
        Serial.println("Is Brown!");;
        brownM=1;
      }
        else{
          brownM=0;
        }


  //Based on what color this module sorts, determine which bin to throw the MnM into.
  input = 'u'; //stub

}
