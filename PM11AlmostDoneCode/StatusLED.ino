
int sBPin = 0;
int sGPin = 0;
int sRPin = 0;

void StatusLED(String color) {

  if (color == "red")  {

     digitalWrite(sBPin, LOW);
     digitalWrite(sGPin, LOW);
     digitalWrite(sRPin, LOW);

  }



}
