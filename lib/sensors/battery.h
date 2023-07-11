// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>
#include "batterytype.h"

struct interpolationPoint
{
  float voltage;  // [mV]
  uint8_t charge; // [%, 0-255]
};

constexpr uint32_t nmbrInterpolationPoints{8};

class battery
{
public:
  // static bool isPresent(); // true : when no USBPower (and code still executing) it means we do have a battery.
  // false : we don't know if there is a battery or not, as external USB power is present and masking the battery voltage.
  static void run();

  static bool isAwake();
  static float getVoltage();
  static uint8_t getChargeLevel();

  static batteryType type; // TODO : we need to read this from nvs
  
#ifndef unitTesting
  private:
#endif
  static bool checkVoltageVsCharge(uint32_t batteryTypeIndex); // this checks that the voltage/charge curve is monotone, ie that the voltage is always increasing when the charge is increasing
  static const interpolationPoint voltageVsCharge[nmbrBatteryTypes][nmbrInterpolationPoints];
  static uint8_t calculateCharge(float voltage);
};