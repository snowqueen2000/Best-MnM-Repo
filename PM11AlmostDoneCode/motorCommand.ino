/**Gives motor the correct direction and speed based on a signed input.
 * mpa: motor pin 1
 * mpb: motor pin 2
 * PWM: motor PWM pin
 * command: analog speed from -10 to 10
 */
 
void motorCommand(int mpa, int mpb, int PWM, double command) {

  if(command > 0) {
    digitalWrite(mpa, LOW);
    digitalWrite(mpb, HIGH);
    command = map(command, 0, 10, 0, 255);

  } else if(command == 0.0) {
      digitalWrite(mpa, LOW);
      digitalWrite(mpb, LOW);
      
  } else {
    digitalWrite(mpa, HIGH);
    digitalWrite(mpb, LOW);
    command = map(command, -10, 0, 255, 0);
  }

  //Serial.println(command);
  analogWrite(PWM, command);

}

void zeroMotor() {

  Serial.println("Zeroing...");

  
  int zeropos = digitalRead(clicking);
  //Serial.println(zeropos);
  while (zeropos == 1) {
    motorCommand(mp1, mp2, mPWM, -2);
    zeropos = digitalRead(clicking);
    //Serial.println(zeropos);
  }



  while (zeropos == 0) {
    motorCommand(mp1, mp2, mPWM, -2);
    zeropos = digitalRead(clicking);
    //Serial.println(zeropos);
  }

  motorCommand(mp1, mp2, mPWM, 0);
  myEnc.write(200);
  Pos = 0;
  Pos_desired = 0;

  Serial.println("Zeroing complete!");
}
