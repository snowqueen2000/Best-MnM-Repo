#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()  
{
  // Open serial communications with computer and wait for port to open:
  Serial.begin(9600);

  // Print a message to the computer through the USB
  Serial.println("Hello Computer!");

  // Open serial communications with the other Arduino board
  mySerial.begin(9600);

  // Send a message to the other Arduino board
  mySerial.print("Hello other Arduino!");

}

void loop() // run over and over
{

}
