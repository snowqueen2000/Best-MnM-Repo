/* Qsensing: updates the global variable Qsize and if Qsize >= 6, tells the previous module to stop by setting pin __ to HIGH.
 *    Qsize should be a number between 0 and 8.
 *    
 * 
 */

//double avgSensorVals[11];  
//int sensorRuns = 1;
void Qsensing() {

  int mnms = 0;
    // read raw sensor values
    qtr.read(sensorValues);
  
    //Serial.println("Queue code is running!");
  

    if(sensorValues[0] > 600) {
      if(sensorValues[1] > 600) {
        if(sensorValues[2] > 400) {
          if(sensorValues[3] > 400) {
            if(sensorValues[4] > 400) {
              if(sensorValues[5] > 1500) {
                if(sensorValues[6] > 500) {
                  if(sensorValues[7] > 1600) {
                    if(sensorValues[8] > 2200) {
                      if(sensorValues[9] > 1000) {
                        if(sensorValues[10] > 500) {

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

    for(int i = 0; i < 11; i++) {
      Serial.print(sensorValues[i]); Serial.print(" "); 
      } 
      Serial.println();
      
    Qsize = mnms;
    
}
