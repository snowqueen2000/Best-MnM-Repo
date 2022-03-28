

/* Updates the OLED screen. Does not include startup animation.
 *  
 *  Currently displays: 
 *  
 */
 
void screen(int type) {
  
 // for type put 1 to sort Red, 2 to sort Green, and 3 to sort Blue
// if no input then it will sort red

  if (type = 1) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Sorting Red!");
  }

  if (type = 2) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Sorting Green!");
  }

   if (type = 3) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Sorting Blue!");
   }

   else {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Enter 'type' to start sorting");
  }

}
}
