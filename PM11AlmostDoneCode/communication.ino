


/**
   Checks for message from the next module, and sends messages to previous module.
*/

void communication() {


  //Serial.println(analogRead(estopTriggerPin));


  //Tell previous module to stop sending MnMs if queue is full
  if (Qsize >= maxQsize) {
    digitalWrite(commOutPin, HIGH);
  } else {
    digitalWrite(commOutPin, LOW);
  }

  //Measure voltage on 5v bus to determine if estop is triggered and tell other modules to stop
  if (analogRead(estopTriggerPin) < 400) {
    digitalWrite(estopOutPin, HIGH);
    estopped = true;
    Serial.println("\t\tE stop triggered!!");
    statusLED("red");
  } else {
    //digitalWrite(estopOutPin, LOW);
  }
  Serial.print("Estop trigger: "); Serial.println(analogRead(estopTriggerPin));


  //Stop sorting operation if next module tells it to.
  int commIn = digitalRead(commInPin);
  int estopIn = analogRead(estopInPin);
  Serial.print("E stop in: "); Serial.println(estopIn);
  Serial.print("My estop value: "); Serial.println(analogRead(estopTriggerPin));

  if (otherModulesConnected) {
    if (commIn == 1) {
      commStopped = true;

    } else {
      commStopped = false;
    }

    if (estopIn >= 300) {
      estoppedOther = true;
      statusLED("blue");
    } else {
      estoppedOther = false;
    }

  }

  if (IRdist < 21 && IRdist != 0) {
    irStopped = true;
    statusLED("red");
  }

}
