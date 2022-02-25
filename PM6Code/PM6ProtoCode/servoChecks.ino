
void servoChecks() {

  

  
}


// Functions
void OpenGate1(){
  for (int pos = 0; pos <= 90; pos += 1) { 
      servo1.write(pos); 
  }
  }

void OpenGate2(){
  for (int pos = 0; pos <= 90; pos += 1) { 
   servo2.write(pos);
   }
}
void CloseGate1(){
 for (int pos = 90; pos >= 0; pos -= 1) { 
    servo1.write(pos);                       
   }
  }


void CloseGate2(){
 for (int pos = 90; pos >= 0; pos -= 1) { 
    servo2.write(pos);                      
    }
}
