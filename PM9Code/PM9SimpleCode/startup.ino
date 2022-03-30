
int initialVals[3];
double calDiff;

/* Gets ambient light value and uses that to calibrate for current light value
 *  Also closes servo gates.
 * Assumes that the module starts over an empty hole
 */

int configPins[] = {31,33,35,37,39,41,43,45,47};
 
void startup() {

  Serial.println("Starting sensor calibration in 3 seconds");
  delay(1000);
  CloseGate1();
  delay(1000);
  CloseGate2();
  delay(1000);
  
  //throw out garbage values
  for (int i = 0; i < 3; i++) {
    colorSensor();
  }
  
  //Read initial RGB values
  for (int i = 0; i < 3; i++) {
    colorSensor();
    initialVals[i] = vals[i];
  }
  
  //Compare empty values to empty calibration values
  calDiff = (emptyv[0] - initialVals[0]) + (emptyv[1] - initialVals[1]) + (emptyv[2] - initialVals[2]);
  calDiff = -calDiff/3;
  
  //Multiply all calibration data by that difference
//  for(int i = 0; i < 6; i++) {
//    rv[i] = rv[i] + calDiff;
//    blv[i] = blv[i] + calDiff;
//    gv[i] = gv[i] + calDiff;
//    brv[i] = brv[i] + calDiff;
//    yev[i] = yev[i] + calDiff;
//    orv[i] = orv[i] + calDiff;
//    emptyv[i] = emptyv[i] + calDiff;
//
//    
//  }

  Serial.println("Sensor calibration complete.");
  Serial.print("difference: "); Serial.println(calDiff);




    Serial.println("\nWaiting for configuration, or 5 seconds...");

  int waitTime = 5000;
  int configStartTime = millis();
  int commAddress;

  digitalWrite(configPins[8], LOW);

  //wait until a commanded color is seen, or until 5 seconds have passed. NEED TO ADD START BUTTON
  while(binaryConversion(configPins[4], configPins[3], configPins[2]) == 0 && millis() < configStartTime + waitTime) {
  
  }
  
  //wait until correct address recieved
  while(commAddress != deviceAddress) {

    commAddress = binaryConversion(configPins[1], configPins[0], 0);
    
  }

  //If a command was seen, update which color to sort, and Queue size.
  if(millis() < configStartTime + waitTime) {
    colorDetect = binaryConversion(configPins[4], configPins[3], configPins[2]);
    maxQsize = binaryConversion(configPins[7], configPins[6], configPins[5]);
    Serial.print("Config recieved! Color: "); Serial.print(colorDetect); Serial.println(". Queue size: ");
  }




  
}
