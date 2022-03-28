

void storeCandy() {
  
  // R=1, G=2. Bl=3, Br=4, Ye=5, Or=6
  if ((vals[0] < rv[0] && vals[0] > rv[1]) && (vals[1] < rv[2] && vals[1] > rv[3]) && (vals[2] < rv[4] && vals[2] > rv[5]))
  {
    
    display.print("Is Red!");
    redCount ++;
    senseSlot = 1;
    oledColor("Red");
  } else if ((vals[0] < blv[0] && vals[0] > blv[1]) && (vals[1] < blv[2] && vals[1] > blv[3]) && (vals[2] < blv[4] && vals[2] > blv[5]))
  {
    Serial.println("Is Blue!");
    blueCount ++;
    senseSlot = 3;
    oledColor("Blue");
  } else if ((vals[0] < gv[0] && vals[0] > gv[1]) && (vals[1] < gv[2] && vals[1] > gv[3]) && (vals[2] < gv[4] && vals[2] > gv[5]))
  {
    Serial.println("Is Green!");
    greenCount ++;
    senseSlot = 2;
    oledColor("Green");
  } else if ((vals[0] < brv[0] && vals[0] > brv[1]) && (vals[1] < brv[2] && vals[1] > brv[3]) && (vals[2] < brv[4] && vals[2] > brv[5]))
  {
    Serial.println("Is Brown!");
    senseSlot = 4;
    oledColor("Brown");
  } else if ((vals[0] < yev[0] && vals[0] > yev[1]) && (vals[1] < yev[2] && vals[1] > yev[3]) && (vals[2] < yev[4] && vals[2] > yev[5]))
  {
    Serial.println("Is yellow!");
    senseSlot = 5;
    oledColor("Yellow");
  } else if ((vals[0] < orv[0] && vals[0] > orv[1]) && (vals[1] < orv[2] && vals[1] > orv[3]) && (vals[2] < orv[4] && vals[2] > orv[5]))
  {
    Serial.println("Is Orange!");
    senseSlot = 6;
    oledColor("Orange");
  } else {
    //if empty
    senseSlot = 0;
    oledColor("No color");
    
  }

}
