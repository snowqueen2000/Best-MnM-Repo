
//This variable ensures that the array updates only once.
bool shouldRun = true;
int i = 0;
int j = 0;

void storeCandies() {

  //PUT SENSOR CODE HERE


  //

  /*Color codes: 
   * 'n' = no candy
   * 'u' = unsorted (gate 2)
   * 't' = trash (gate 3)
   * 's' = sort this candy (gate 1)
   */

   char input;
  if(Serial.available()>0) {
    input[i] = Serial.read();
    i++;
  }

  //Serial command to stop the motor
  if(input[i-1] == ' ') {
    stopper = true;
  } else if(input[i-1] != ' ') {
    stopper = false;
  }
  

  //if 30 deg, update sensing slot
  if((int)floor(Pos)%30 == 0) {
    senseSlot = input[j];
    Serial.println("sense recieved!");
    shouldRun = true;
  }
  
  
  //if 15 deg, update array
  if((int)floor(Pos)%15 == 0 && (int)floor(Pos)%30 != 0 && shouldRun) {
    gate3Slot = gate2Slot;
    gate2Slot = gate1Slot;
    gate1Slot = senseSlot;
    Serial.println("array has updated");
    shouldRun = false;
  }
  
   
  
}
