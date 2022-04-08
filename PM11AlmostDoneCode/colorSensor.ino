

int analogPin = A0;


char lightColor = 'b';


void colorSense(int index) {

  vals[index] = analogRead(analogPin);

}


void setLED(int Bpin, int Gpin, int Rpin) {


    // set LED color
    digitalWrite(blue_pin, Bpin);
    digitalWrite(green_pin, Gpin);
    digitalWrite(red_pin, Rpin);



}
