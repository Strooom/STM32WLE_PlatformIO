// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#include "sensortype.h"

const char* toString(sensorType type) {
    switch (type) {
        case sensorType::batteryChargeLevel:
            return "batteryChargeLevel";
            break;

        case sensorType::batteryVoltage:
            return "batteryChargeLevel";
            break;

        case sensorType::BME680Temperature:
            return "BME680 - Temperature";
            break;

        case sensorType::BME680RelativeHumidity:
            return "BME680 - Relative Humidity";
            break;

        case sensorType::BME680BarometricPressure:
            return "BME680 - Barometer";
            break;

        case sensorType::TSL25911VisibleLight:
            return "TSL25911 - Visible Light";
            break;

        case sensorType::TSL25911Infrared:
            return "TSL25911 - Infrared Light";
            break;

        default:
            return "unknown infoChannel";
            break;
    }
}