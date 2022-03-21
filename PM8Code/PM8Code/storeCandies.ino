

//This variable ensures that the array updates only once.
bool shouldRun = true;
int j = 0;
//int tDelay = 18/Vel_DesiredM;
bool newCand = true;

/* Updates the sensor variables when candy is below the sensor, and updates the servo commands when in between the sensor and 1st servo gate.
 * 
 */
void storeCandies() {

  //PUT SENSOR CODE HERE


  //

  /*Color codes: 
   * 'n' = no candy
   * 'u' = unsorted (gate 2)
   * 't' = trash (gate 3)
   * 's' = sort this candy (gate 1)
   */

  //if 30 deg, update sensing slot
  if((int)floor(Pos)%40 <= 20) {
    colorSensor(newCand);
    senseSlot = input;
    Serial.println("At 30 deg! Running command: ");
    //Serial.print(j);
    //Serial.println(input[j]);
    shouldRun = true;

    newCand = false;
  }
  
  
  //if 15 deg, update array
  if((int)floor(Pos)%20 <= 10 && (int)floor(Pos)%30 > 10 && shouldRun) {
    gate3Slot = gate2Slot;
    gate2Slot = gate1Slot;
    gate1Slot = senseSlot;
    //Serial.println("array has updated");
    shouldRun = false;
    newCand = true;
    
    j = j+1;
  }

  if(j >= 10) {
    j = 0;
  }
  
   
  
}
