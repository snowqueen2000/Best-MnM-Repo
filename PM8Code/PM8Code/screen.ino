

/* Updates the OLED screen. Does not include startup animation.
 *  
 *  Currently displays: 
 *  
 */
void screen() {
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("In queue:");
  display.print(Qsize);
  display.print("/");
  display.println(maxQsize);
  display.display();
  
}
