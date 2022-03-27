
//commOut connects to module above, commIn is connected to module below
int commOutPin = 50;
int commInPin = 52;

//these pins are connected to each other and the estop pins on every other module. Copper tape?
int estopOutPin = 46;
int estopInPin = 48;

int estopTriggerPin = A1; //MAY NEED TO CHANGE THIS PIN

/**
 * Checks for message from the next module, and sends messages to previous module.
 */
 
void communication() {

  //Tell previous module to stop sending MnMs if queue is full
  if(Qsize >= maxQsize) {
    digitalWrite(commOutPin, HIGH);
  } else {
    digitalWrite(commOutPin, LOW);
  }

  //Measure voltage on 5v bus to determine if estop is triggered and tell other modules to stop
  if(analogRead(estopTriggerPin) < 150) {
    digitalWrite(estopOutPin, HIGH);
  } else {
    digitalWrite(estopOutPin, LOW);
  }
  

  //Stop sorting operation if next module tells it to.
  int commIn = digitalRead(commInPin);
  int estopIn = digitalRead(estopInPin);
    
  if(commIn == 1 || estopIn == 1) {

    stopSorting = true;
  } else {
    stopSorting = false;
  }

}
