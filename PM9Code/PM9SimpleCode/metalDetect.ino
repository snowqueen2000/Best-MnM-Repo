
int HEpin = 51;

/*
 * Runs every 30 degrees
 * Checks HE sensor for metal, stores that value in senseSlot
 */
void metalDetect() {
  //Store sensor value in senseSlot
  metalSlot = digitalRead(HEpin);
  
  
}
