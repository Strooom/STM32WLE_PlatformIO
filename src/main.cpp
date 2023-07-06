#include <Arduino.h>
#include "buildinfo.h"

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println(BUILD_VERSION);
  Serial.println(BUILD_TIMESTAMP);
  HAL_Delay(1000);
}

