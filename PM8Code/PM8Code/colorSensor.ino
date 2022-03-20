
//Maximum times the color sensor can run per candy
int const maxDataPerCandy = 100;

int thisCandyR[maxDataPerCandy];
int thisCandyG[maxDataPerCandy];
int thisCandyB[maxDataPerCandy];

int readingIndex = 0;

/* Updates the variable input with the mnm reading. Constantly runs while MnM is under the sensor.
 * This function is called by the storeCandies() function.
 */
void colorSensor(bool newCandy) {
  int avgR = 0;
  int avgG = 0;
  int avgB = 0;
  
  //if newCandy is true, the sensor has started reading a new candy and the array needs to restart at zero
  if(newCandy) {
    readingIndex = 0;
  }



  //shine LED and record one set of RGB readings
  //thisCandyR[readingIndex] = 
  //thisCandyG[readingIndex] = 
  //thisCandyB[readingIndex] = 



  //Increment which reading this is
  readingIndex++;

  //Average all RGB values up to readingIndex. Need to start index at 1 to avoid /0 error.
  for(int i = 1; i < readingIndex+1; i++) {
    avgR = (avgR + thisCandyR[i-1])/i;
    avgG = (avgG + thisCandyG[i-1])/i;
    avgB = (avgB + thisCandyB[i-1])/i;
  }

  //Compare average RGB values to experimentally determined values for each MnM.



  //Based on what color this module sorts, determine which bin to throw the MnM into.
  input = 'u'; //stub

}
