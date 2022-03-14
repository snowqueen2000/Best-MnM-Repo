


/* Qsensing: updates the global variable Qsize and if Qsize >= 6, tells the previous module to stop by setting pin __ to HIGH.
 *    Qsize should be a number between 0 and 8.
 *    
 * 
 */
void Qsensing() {

  int mnms = 0;
    // read raw sensor values
    qtr.read(sensorValues);
  
    // print the sensor values as numbers from 0 to 2500, where 0 means maximum
    // reflectance and 2500 means minimum reflectance
    //for (uint8_t i = 0; i < SensorCount; i++)
    //{
      
      //Serial.print(sensorValues[i]);
      //Serial.print('\t');
    //}
  
    if(sensorValues[0] > 600) {
      if(sensorValues[1] > 600) {
        if(sensorValues[2] > 600) {
          if(sensorValues[3] > 600) {
            if(sensorValues[4] > 600) {
              if(sensorValues[5] > 600) {
                if(sensorValues[6] > 600) {
                  if(sensorValues[7] > 600) {
                    if(sensorValues[8] > 600) {
                      if(sensorValues[9] > 600) {
                        if(sensorValues[10] > 600) {
                          mnms = 0;
                        } else {
                          mnms = 1;
                        }
                      } else {
                        mnms = 2;
                      }
                    } else {
                      mnms = 2;
                    }
                  } else {
                    mnms = 3;
                    }
                } else {
                  mnms = 3;
                  }
              } else {
                mnms = 4;
              }
            } else {
              mnms = 5;
            }
          } else {
            mnms = 5;
          }
        } else {
          mnms = 6;
        }
      } else {
        mnms = 6;
      }
    } else {
      mnms = 7;
    }
    
    //Serial.println();  
    //Serial.println(mnms);
    Qsize = mnms;
}
