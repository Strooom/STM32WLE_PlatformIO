#include "sensordevicetype.h"

const char* toString(sensorDeviceType theType) {
    switch (theType) {
        case sensorDeviceType::battery:
            return "battery";
            break;

        case sensorDeviceType::bme680:
            return "bme680";
            break;

        case sensorDeviceType::bme688:
            return "bme688";
            break;

        case sensorDeviceType::tsl2591:
            return "tsl2591";
            break;

        default:
            return "unknown";
            break;
    }
}