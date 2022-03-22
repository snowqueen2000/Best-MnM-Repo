
int redM;
int blueM;
int greenM;
int brownM;
int yellowM;
int orangeM;

void storeCandy() {


  if ((vals[0] < rv[0] && vals[0] > rv[1]) && (vals[1] < rv[2] && vals[1] > rv[3]) && (vals[2] < rv[4] && vals[2] > rv[5]))
  {
    //Serial.println("Is Red!");
    display.print("Is Red!");
    redM = 1;  
    redCount ++;
    senseSlot = "red";
  }
  else {
    redM = 0;
  }


  if ((vals[0] < blv[0] && vals[0] > blv[1]) && (vals[1] < blv[2] && vals[1] > blv[3]) && (vals[2] < blv[4] && vals[2] > blv[5]))
  {
    Serial.println("Is Blue!");
    blueM = 1;
    blueCount ++;
    senseSlot = "blue";
  }
  else
  {
    blueM = 0;
  }


  if ((vals[0] < gv[0] && vals[0] > gv[1]) && (vals[1] < gv[2] && vals[1] > gv[3]) && (vals[2] < gv[4] && vals[2] > gv[5]))
  {
    Serial.println("Is Green!");;
    greenM = 1;
    greenCount ++;
    senseSlot = "green";
  }
  else {
    greenM = 0;
  }

//  if ((vals[0] < brv[0] && vals[0] > brv[1]) && (vals[1] < brv[2] && vals[1] > brv[3]) && (vals[2] < brv[4] && vals[2] > brv[5]))
//  {
//    Serial.println("Is Brown!");;
//    brownM = 1;
//    senseSlot = "brown";
//  }
//  else {
//    brownM = 0;
//  }

  if ((vals[0] < yev[0] && vals[0] > yev[1]) && (vals[1] < yev[2] && vals[1] > yev[3]) && (vals[2] < yev[4] && vals[2] > yev[5]))
  {
    Serial.println("Is yellow!");;
    yellowM = 1;
    senseSlot = "yellow";
  }
  else {
    yellowM = 0;
  }

  if ((vals[0] < orv[0] && vals[0] > orv[1]) && (vals[1] < orv[2] && vals[1] > orv[3]) && (vals[2] < orv[4] && vals[2] > orv[5]))
  {
    Serial.println("Is Orange!");
    orangeM = 1;
    senseSlot = "orange";
  }
  else {
    orangeM = 0;
  }

}
