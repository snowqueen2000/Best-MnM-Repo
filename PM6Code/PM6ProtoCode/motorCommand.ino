void motorCommand(int mpa, int mpb, int PWM, double command) {

  if(command > 0) {
    digitalWrite(mpa, HIGH);
    digitalWrite(mpb, LOW);
    command = map(command, 0, 10, 0, 255);
  } else {
    digitalWrite(mpa, LOW);
    digitalWrite(mpb, HIGH);
    command = map(command, -10, 0, 255, 0);
  }

  //Serial.println(command);
  analogWrite(PWM, command);
  
}
