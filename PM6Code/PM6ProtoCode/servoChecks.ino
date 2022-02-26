
void servoChecks() {

  //Gate 1:
  if(gate1Slot == 's') {
    OpenGate1();
  } else {
    CloseGate1();
  }

  //Gate 2:
  if(gate2Slot == 'u') {
    OpenGate2();
  } else {
    CloseGate2();
  }
  
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
