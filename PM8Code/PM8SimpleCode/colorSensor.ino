

int analogPin = A0;


char lightColor = 'b';

/* 
 *  Stores RGB values to vals[] array.
 *  
 */
void colorSensor() {

    Serial.print("R: "); Serial.print(vals[2]);
    Serial.print(" G: "); Serial.print(vals[1]);
    Serial.print(" B: "); Serial.println(vals[0]);
    
    if(lightColor == 'b') {

      vals[0] = analogRead(analogPin); // read phototransistor and store value
        //Serial.println(vals[2]); // print stored value.

      // set LED color to blue
      digitalWrite(blue_pin, HIGH);   
      digitalWrite(green_pin,LOW);
      digitalWrite(red_pin,LOW);


      
      lightColor = 'g';
    } else if(lightColor == 'g') {

      vals[1] = analogRead(analogPin); // read phototransistor and store value
        //Serial.print(vals[0]);Serial.print(", "); // print stored value.

      // set LED color to green                       
      digitalWrite(blue_pin,LOW);   
      digitalWrite(green_pin,HIGH);
      digitalWrite(red_pin,LOW);


      
      lightColor = 'r';
    } else if(lightColor == 'r') {

      vals[2] = analogRead(analogPin); // read phototransistor and store value
        //Serial.print(vals[1]);Serial.print(", ");  // print stored value.

      // set LED color to Red
      digitalWrite(blue_pin,LOW);   
      digitalWrite(green_pin,LOW);
      digitalWrite(red_pin,HIGH);

      
      lightColor = 'b';
    }
  

  }
