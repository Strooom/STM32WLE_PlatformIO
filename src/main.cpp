#include <Arduino.h>

//HardwareSerial mySerial(USART2);

void setup()
{
  Serial.begin(115200);
  //mySerial.begin(115200);
}

void loop()
{
  Serial.println("Hello World");
  //mySerial.println("Hello World");
  // delay(1000);
  HAL_Delay(1000);
}