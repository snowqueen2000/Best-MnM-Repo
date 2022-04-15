bool oneIsOpen = false;
bool twoIsOpen = false;


void servoChecks() {

  //Gate 1: Trash
  if(metalGate1 == 1) {
    OpenGate1();
    Serial.println("Trash found!");
    trashCount++;
  } else {
    //CloseGate1();
  }

  //Gate 2: Unsorted
  if(gate2 != 0 && gate2 != colorDetect) { //gate2 != 0 &&
    OpenGate2();
    unsortedCount++;
  } else {
   //CloseGate1();
  }

  //Increase sort count if needed
  if(gate2 == colorDetect) {
    candySorted++;
    Serial.println("Sorted a candy! Yay!");
  }
  
}

// Functions
void CloseGate1(){
  if(!oneIsOpen) {
    for (int pos = 0; pos <= 90; pos += 1) { 
        servo1.write(pos); 
    }
    oneIsOpen = true;
    }
  }

void OpenGate2(){
  if(!twoIsOpen) {
    for (int pos = 0; pos <= 90; pos += 1) { 
      servo2.write(pos);
    }
    twoIsOpen = true;
  }
}

void OpenGate1(){
 if(oneIsOpen) {
 for (int pos = 90; pos >= 0; pos -= 1) { 
    servo1.write(pos);                       
   }
   oneIsOpen = false;
 }
  }


void CloseGate2(){
 if(twoIsOpen) {
 for (int pos = 90; pos >= 0; pos -= 1) { 
    servo2.write(pos);                      
    }
    twoIsOpen = false;
 }
}
