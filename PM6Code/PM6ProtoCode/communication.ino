
int commOutPin = 50;
int commInPin = 52;

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

  //Stop sorting operation if next module tells it to.
  bool commIn = digitalRead(commInPin);

  if(commIn) {
    stopper = true;
  } else {
    stopper = false;
  }

}
