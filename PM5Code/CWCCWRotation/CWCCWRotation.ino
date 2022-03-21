#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

int IN3 = 6;
int IN4 = 7;
int SignalAbove = 51;    
bool val = 0; 

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

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  

}

void loop() // run over and over
{
//  clockwise
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
val = digitalRead(SignalAbove); // read the input pin
  Serial.println(val);
  if(val == 1) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  
  
  
  
  

}
