
//Runs in the setup function. Finds motor zero position. 
//Note: While this function is running, nothing else will happen!
void startUp() {

  //close all gates
  CloseGate1();
  CloseGate2();

  //Welcome message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Waiting for serial \ninput...");
  display.display();

  //User input to mimic sensor
  
  //Can take up to 9 commands before restarting arduino.

  for (int i = 0; i < 10; i++) {
    while(Serial.available() <= 0) {}
      input[i] = Serial.read();
      Serial.println("Input updated!");
  }
  
  Serial.println("All input recieved. Input:");
  for(int k = 0; k < 10; k++) {
    Serial.println(input[k] + ", ");
  }
  
  //turn motor slowly
  //motorCommand(mp1, mp2, mPWM, 3);
  
  //wait until the sensor passes one hole, then stop at the next hole.

  //move forward a given offset, and set that position to zero.
  
}
