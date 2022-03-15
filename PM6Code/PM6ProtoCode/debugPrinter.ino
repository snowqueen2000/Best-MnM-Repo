//Function that prints data to serial. Only needed for debugging.
//If type = 0, nothing will be printed.
void debugPrinter(int type) {

  switch(type) {
    
    default:
      Serial.print(t, 5);     // print time; comment out if using the serial plotter
      Serial.print(",\t");     // tab command
      Serial.print(Pos, 5);   // print position
      Serial.print(",\t");
      Serial.println(Vel, 5); // print velocity
      
    break;

    case 1:
      Serial.print("Queue size: ");
      Serial.println(Qsize);
    break;

    case 2:
      //print the sensor values as numbers from 0 to 2500, where 0 means maximum reflectance and 2500 means minimum reflectance
      for (uint8_t i = 0; i < SensorCount; i++)
      {
        
        Serial.print(sensorValues[i]);
        Serial.print('\t');
      }
    break;
    
  case 0:
  break;
  }
  
}
