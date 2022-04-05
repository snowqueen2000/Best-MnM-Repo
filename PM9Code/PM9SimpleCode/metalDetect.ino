
int HEpin = A8;

/*
 * Runs every 30 degrees
 * Checks HE sensor for metal, stores that value in senseSlot
 */
void metalDetect() {
  //Store sensor value in senseSlot
  metalSlot = analogRead(HEpin);
  Serial.print("Metal sensor: "); Serial.println(metalSlot);
  
}
