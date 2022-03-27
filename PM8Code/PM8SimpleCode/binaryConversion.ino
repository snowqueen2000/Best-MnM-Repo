


/* Reads digital values from 2 or 3 pins, and converts those binary values to and integer.
 * 
 * If there's only 2 pins to read, set mostPin to 0 and it will be ignored.
 *
  */
int binaryConversion(int leastPin, int midPin, int mostPin) {
  
  int value = digitalRead(leastPin) + digitalRead(midPin) * 2;

  if(mostPin != 0) {
    value = value + digitalRead(mostPin) * 4;
  }

  return value; //stub
  
}
