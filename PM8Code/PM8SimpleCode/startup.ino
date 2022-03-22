
int initialVals[3];
double calDiff;

/* Gets ambient light value and uses that to calibrate for current light value
 *  Also closes servo gates.
 * Assumes that the module starts over an empty hole
 */
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
  for(int i = 0; i < 6; i++) {
    rv[i] = rv[i] + calDiff;
    blv[i] = blv[i] + calDiff;
    gv[i] = gv[i] + calDiff;
    brv[i] = brv[i] + calDiff;
    yev[i] = yev[i] + calDiff;
    orv[i] = orv[i] + calDiff;
    emptyv[i] = emptyv[i] + calDiff;

    
  }

  Serial.println("Sensor calibration complete.");
  Serial.print("difference: "); Serial.println(calDiff);
  
}
