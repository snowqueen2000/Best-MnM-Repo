// for type put 1 to sort Red, 2 to sort Green, and 3 to sort Blue
// if no input then it will sort red

void OLED(int type) {
  if (type == 1) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Sorting Red: "); display.println(candySorted);
      display.print("MnMs in Queue: ");
      display.print(Qsize);
      display.print("/");
      display.println(maxQsize);
      display.display();
  }

  else if (type == 2) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Sorting Green: "); display.println(candySorted);
      display.print("MnMs in Queue: ");
      display.print(Qsize);
      display.print("/");
      display.println(maxQsize);
      display.display();
  }

   else if (type == 3) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Sorting Blue: "); display.println(candySorted);
      display.print("MnMs in Queue: ");
      display.print(Qsize);
      display.print("/");
      display.println(maxQsize);
      display.display();
   }

   else {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Enter color to start sorting");
      display.display();
  }
  
}

void oledColor(String c) {
  
      //display.setTextSize(1);
      //display.setTextColor(WHITE);
      //display.setCursor(0,15);
      display.print("Sensing: "); display.println(c);
      display.display();


  
}
