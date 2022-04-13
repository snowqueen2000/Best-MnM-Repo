// for type put 1 to sort Red, 2 to sort Green, and 3 to sort Blue
// if no input then it will sort red
// red = 1, green = 2, blue = 3, yellow = 4, orange = 5, brown = 6

void OLED(int type) {

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("MnMs in Queue: ");
  display.print(Qsize);
  display.print("/");
  display.println(maxQsize);
  display.print("T: ");
  display.print(trashCount);
  display.print("  U: ");
  display.println(unsortedCount);

  if (type == 1) {
    display.print("Sorting Red: "); display.println(candySorted);
  } else if (type == 2) {
    display.print("Sorting Green: "); display.println(candySorted);
  } else if (type == 3) {
    display.print("Sorting Blue: "); display.println(candySorted);
  } else if (type == 4) {
    display.print("Sorting Yellow: "); display.println(candySorted);
  } else if (type == 5) {
    display.print("Sorting Orange: "); display.println(candySorted);
  } else if (type == 6) {
    display.print("Sorting Brown: "); display.println(candySorted);
  } else {
    display.print("Sorting no color: "); display.println(candySorted);

  }

  display.display();

}

void oledColor(String c) {

  //display.setTextSize(1);
  //display.setTextColor(WHITE);
  //display.setCursor(0,15);
  display.print("Sensing: "); display.println(c);
  display.display();



}
