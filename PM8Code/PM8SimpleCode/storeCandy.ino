
//bgr:  max, min, max, min, max, min
int rv[] = {36, 33, 34, 31, 34, 31};
int blv[] = {32, 28, 32, 29, 37, 34};
int gv[] = {36, 32, 31, 28, 36, 33};
int brv[] = {37, 34, 34, 31, 37, 34};
int yev[] = {36, 33, 31, 28, 32, 29};
int orv[] = {36, 33, 33, 30, 31, 28};
int emptyv[] = {};
int wheelv[] = {};


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
  }
  else {
    redM = 0;
  }


  if ((vals[0] < blv[0] && vals[0] > blv[1]) && (vals[1] < blv[2] && vals[1] > blv[3]) && (vals[2] < blv[4] && vals[2] > blv[5]))
  {
    Serial.println("Is Blue!");;
    blueM = 1;
    blueCount ++;
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
  }
  else {
    greenM = 0;
  }

//  if ((vals[0] < brv[0] && vals[0] > brv[1]) && (vals[1] < brv[2] && vals[1] > brv[3]) && (vals[2] < brv[4] && vals[2] > brv[5]))
//  {
//    Serial.println("Is Brown!");;
//    brownM = 1;
//  }
//  else {
//    brownM = 0;
//  }

}
