
//Minimum amount of color sensor data needed per candy
int dataNeeded = 10;

//This variable ensures that the array updates only once.
bool shouldRun = true;
int j = 0;
//int tDelay = 18/Vel_DesiredM;
bool newCand = true;

/* Updates the sensor variables when candy is below the sensor, and updates the servo commands when in between the sensor and 1st servo gate.
 * 
 */
void storeCandies() {

  /*Color codes: 
   * 'n' = no candy
   * 'u' = unsorted (gate 2)
   * 't' = trash (gate 3)
   * 's' = sort this candy (gate 1)
   */

  //if 30 deg, update sensing slot
  if((int)floor(Pos)%35 <= 10) {
    colorSensor(newCand);
    senseSlot = input;
    Serial.println("At 30 deg! Running sensor");
    //Serial.print(j);
    //Serial.println(input[j]);
    shouldRun = true;
    
    newCand = false;

    //If enough sensor data has been collected, the motor can move
    if(dataCollected >= dataNeeded) {
      sensingComplete = true;
    }
    
  } //Should run once while the motor is moving to next slot
  else if(shouldRun) {
    gate3Slot = gate2Slot;
    gate2Slot = gate1Slot;
    gate1Slot = senseSlot;
    //Serial.println("array has updated");
    shouldRun = false;
    newCand = true;
    sensingComplete = false;
    j = j+1;
  }
  
  


  if(j >= 10) {
    j = 0;
  }
  
   
  
}
