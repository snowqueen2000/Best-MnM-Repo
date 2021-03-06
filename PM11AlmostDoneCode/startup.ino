
int initialVals[3];
double calDiff;

/* Gets ambient light value and uses that to calibrate for current light value
    Also closes servo gates.
   Assumes that the module starts over an empty hole
*/

int configPins[] = {23, 25, 27, 29, 31, 33, 35, 37, 39};


void startup() {

  Serial.println("Starting sensor calibration in 3 seconds");
  delay(1000);
  CloseGate1();
  delay(1000);
  CloseGate2();
  delay(1000);

  //throw out garbage values NEED TO REWORK
  for (int i = 0; i < 3; i++) {
    //colorSense();
  }

  //Read initial RGB values NEED TO REWORK THIS WITH THE NEW COLOR CODE
  for (int i = 0; i < 3; i++) {
    //colorSense();
    initialVals[i] = vals[i];
  }

  //Compare empty values to empty calibration values
  calDiff = (emptyv[0] - initialVals[0]) + (emptyv[1] - initialVals[1]) + (emptyv[2] - initialVals[2]);
  calDiff = -calDiff / 3;

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

  //Zeroing stuff
  zeroMotor();
  
  Serial.println("\nWaiting for configuration, or until start button is pressed...");

  //  int waitTime = 5000;
  //  int configStartTime = millis();
  int commAddress;
  int buttonState = 1;


  digitalWrite(configPins[8], LOW);

  //wait until a commanded color is seen, or until start button is pressed
  while (binaryConversion(configPins[4], configPins[3], configPins[2]) == 0 && buttonState == buttonOff) {

    buttonState = digitalRead(startButton);
    Serial.println(binaryConversion(configPins[4], configPins[3], configPins[2]));
  }
  Serial.println("Command seen!");
  //wait until correct address recieved or button is pressed
  while (commAddress != deviceAddress && buttonState == buttonOff) {
    //&& digitalRead(startButton) == 0
    commAddress = binaryConversion(0, configPins[1], configPins[0]);
    buttonState = digitalRead(startButton);
    Serial.println(commAddress);
  }
  Serial.println("Address seen!");

  //If a command was seen, update which color to sort, and Queue size.
  if (buttonState == buttonOff) {
    //digitalRead(startButton) == 0
    colorDetect = binaryConversion(configPins[4], configPins[3], configPins[2]);
    maxQsize = binaryConversion(configPins[7], configPins[6], configPins[5]);
    Serial.print("Config recieved! Color: "); Serial.print(colorDetect); Serial.print(". Queue size: "); Serial.println(maxQsize);
    otherModulesConnected = true;
  }

  Serial.println("Press button to continue...");
  while (buttonState == buttonOff) {
    buttonState = digitalRead(startButton);
    };

}
