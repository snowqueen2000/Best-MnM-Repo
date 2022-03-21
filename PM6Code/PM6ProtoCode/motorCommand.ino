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
  } else if(command == 0) {
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
