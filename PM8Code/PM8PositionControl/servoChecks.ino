bool oneIsOpen = false;
bool twoIsOpen = false;


void servoChecks() {
  
  //Gate 1:
  if(gate1Slot == 's' && !oneIsOpen) {
    servoMoveComplete[0] = false;
    OpenGate1();
    servoMoveComplete[0] = true;
  } else if(gate1Slot != 's' && oneIsOpen) {
    servoMoveComplete[0] = false;
    CloseGate1();
    servoMoveComplete[0] = true;
  }

  //Gate 2:
  if(gate2Slot == 'u' && !twoIsOpen) {
    servoMoveComplete[1] = false;
    OpenGate2();
    servoMoveComplete[1] = true;
  } else if(gate2Slot != 'u' && twoIsOpen) {
    servoMoveComplete[1] = false;
    CloseGate2();
    servoMoveComplete[1] = true;
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
