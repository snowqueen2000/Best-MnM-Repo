
int sBPin = 41;
int sGPin = 43;
int sRPin = 45;

void statusLED(String color) {

  if (color == "red")  {

    digitalWrite(sBPin, LOW);
    digitalWrite(sGPin, LOW);
    digitalWrite(sRPin, HIGH);

  } else if (color == "green") {

    digitalWrite(sBPin, LOW);
    digitalWrite(sGPin, HIGH);
    digitalWrite(sRPin, LOW);
  } else if (color == "blue") {

    digitalWrite(sBPin, HIGH);
    digitalWrite(sGPin, LOW);
    digitalWrite(sRPin, LOW);
  } else if (color == "off") {

    digitalWrite(sBPin, LOW);
    digitalWrite(sGPin, LOW);
    digitalWrite(sRPin, LOW);
  }



}
