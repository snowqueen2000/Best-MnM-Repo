

int analogPin = A0;


char lightColor = 'b';

/* 
 *  Stores RGB values to vals[] array.
 *  
 */
 
void colorSensor() {

//  Serial.print("B: "); Serial.print(vals[0]);
//  Serial.print(" G: "); Serial.print(vals[1]);
//  Serial.print(" R: "); Serial.println(vals[2]);
    
    if(lightColor == 'b') {

      instVals[2] = analogRead(analogPin); // read phototransistor and store value
        //Serial.println(vals[2]); // print stored value.

      // set LED color to blue
      digitalWrite(blue_pin, LOW);   
      digitalWrite(green_pin,HIGH);
      digitalWrite(red_pin,HIGH);


      vals[2] = vals[2] + instVals[2];
      lightColor = 'g';
    } else if(lightColor == 'g') {

      instVals[0] = analogRead(analogPin); // read phototransistor and store value
        //Serial.print(vals[0]);Serial.print(", "); // print stored value.

      // set LED color to green                       
      digitalWrite(blue_pin,HIGH);   
      digitalWrite(green_pin,LOW);
      digitalWrite(red_pin,HIGH);

      vals[0] = vals[0] + instVals[0];
      lightColor = 'r';
    } else if(lightColor == 'r') {

      instVals[1] = analogRead(analogPin); // read phototransistor and store value
        //Serial.print(vals[1]);Serial.print(", ");  // print stored value.

      // set LED color to Red
      digitalWrite(blue_pin,HIGH);   
      digitalWrite(green_pin,HIGH);
      digitalWrite(red_pin,LOW);

      vals[1] = vals[1] + instVals[1];
      lightColor = 'b';
      colorReadings++;
    }
  

  }
