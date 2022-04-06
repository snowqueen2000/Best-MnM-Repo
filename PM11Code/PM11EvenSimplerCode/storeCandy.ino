

void storeCandy() {


  
  // R=1, G=2. Bl=3,  Ye=4, Or=5  Br=6,
  // red = 1, green = 2, blue = 3, yellow = 4, orange = 5, brown = 6

  
  if ((vals[0] < rv[0] && vals[0] > rv[1]) && (vals[1] < rv[2] && vals[1] > rv[3]) && (vals[2] < rv[4] && vals[2] > rv[5]))
  {
    
    Serial.println("Is Red!");
    redCount ++;
    gate1 = 1;
    oledColor("Red");
  } else if ((vals[0] < blv[0] && vals[0] > blv[1]) && (vals[1] < blv[2] && vals[1] > blv[3]) && (vals[2] < blv[4] && vals[2] > blv[5]))
  {
    Serial.println("Is Blue!");
    blueCount ++;
    gate1 = 3;
    oledColor("Blue");
  } else if ((vals[0] < gv[0] && vals[0] > gv[1]) && (vals[1] < gv[2] && vals[1] > gv[3]) && (vals[2] < gv[4] && vals[2] > gv[5]))
  {
    Serial.println("Is Green!");
    greenCount ++;
    gate1 = 2;
    oledColor("Green");
  } else if ((vals[0] < brv[0] && vals[0] > brv[1]) && (vals[1] < brv[2] && vals[1] > brv[3]) && (vals[2] < brv[4] && vals[2] > brv[5]))
  {
    Serial.println("Is Brown!");
    gate1 = 6;
    oledColor("Brown");
  } else if ((vals[0] < yev[0] && vals[0] > yev[1]) && (vals[1] < yev[2] && vals[1] > yev[3]) && (vals[2] < yev[4] && vals[2] > yev[5]))
  {
    Serial.println("Is yellow!");
    gate1 = 4;
    oledColor("Yellow");
  } else if ((vals[0] < orv[0] && vals[0] > orv[1]) && (vals[1] < orv[2] && vals[1] > orv[3]) && (vals[2] < orv[4] && vals[2] > orv[5]))
  {
    Serial.println("Is Orange!");
    gate1 = 5;
    oledColor("Orange");
  } else {
    //if empty
    gate1 = 0;
    oledColor("No color");
    
  }

}
