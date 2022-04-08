// Color Sensing Function
int analogPin = A0;

char lightColor = 'b';

/* 
 *  Stores RGB values to vals[] array.
 *  
 */
 
void colorSensor() {
    
    if(lightColor == 'b') {

      instVals[2] = analogRead(analogPin); // read phototransistor and store value
      //Serial.println(vals[2]); // print stored value.

}


      vals[2] = vals[2] + instVals[2];
      lightColor = 'g';
    }
    
      else if(lightColor == 'g') {


    // set LED color
    digitalWrite(blue_pin, Bpin);
    digitalWrite(green_pin, Gpin);
    digitalWrite(red_pin, Rpin);

      vals[0] = vals[0] + instVals[0];
      lightColor = 'r';
      }
      
      else if(lightColor == 'r') {

      // set LED color to Red
      digitalWrite(blue_pin,HIGH);   
      digitalWrite(green_pin,HIGH);
      digitalWrite(red_pin,LOW);

      vals[1] = vals[1] + instVals[1];
      lightColor = 'b';
      colorReadings++;
    }
  
  }
