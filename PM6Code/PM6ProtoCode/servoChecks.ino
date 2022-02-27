bool oneIsOpen = false;
bool twoIsOpen = false;


void servoChecks() {

  //Gate 1:
  if(gate1Slot == 's' && !oneIsOpen) {
    OpenGate1();
  } else if(gate1Slot != 's' && oneIsOpen) {
    CloseGate1();
  }

  //Gate 2:
  if(gate2Slot == 'u' && !twoIsOpen) {
    OpenGate2();
  } else if(gate2Slot != 'u' && twoIsOpen) {
    CloseGate2();
  }
  
}


// Functions
void OpenGate1(){
  for (int pos = 0; pos <= 90; pos += 1) { 
      servo1.write(pos); 
  }
  oneIsOpen = true;
  }

void OpenGate2(){
  for (int pos = 0; pos <= 90; pos += 1) { 
   servo2.write(pos);
   }
   twoIsOpen = true;
}
void CloseGate1(){
 for (int pos = 90; pos >= 0; pos -= 1) { 
    servo1.write(pos);                       
   }
   oneIsOpen = false;
  }


void CloseGate2(){
 for (int pos = 90; pos >= 0; pos -= 1) { 
    servo2.write(pos);                      
    }
    twoIsOpen = false;
}
