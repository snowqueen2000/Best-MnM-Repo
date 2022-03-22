// for type put 1 to sort Red, 2 to sort Green, and 3 to sort Blue
// if no input then it will sort red

void OLED(int type) {
  if (type == 1) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Sorting Red!");
      display.println(Qsize);
      display.display();
  }

  else if (type == 2) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Sorting Green!");
      display.println(Qsize);
      display.display();
  }

   else if (type == 3) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Sorting Blue!");
      display.println(Qsize);
      display.display();
   }

   else {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Enter 'type' to start sorting");
      display.display();
  }

}
