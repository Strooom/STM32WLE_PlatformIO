#include "sensor.h"
#include "power.h"

// List of all sensors we know about

#include "bme680.h"
#include "tsl2591.h"
#include "battery.h"

sensor::runResult sensor::run() {
    if (active) {
        uint32_t oversampling;
        uint32_t prescaler;
        if (power::hasUsbPower()) {
            oversampling = oversamplingHighPower;
            prescaler    = prescalerHighPower;
        } else {
            oversampling = oversamplingLowPower;
            prescaler    = prescalerLowPower;
        }

        if (prescaleCounter > prescaler) {        // when switching between low power and high power mode, the prescaleCounter could need to be reset in the appropriate range
            prescaleCounter = prescaler;
        }
        if (oversamplingCounter > oversampling) {        // when switching between low power and high power mode, the oversamplingCounter could need to be reset in the appropriate range
            oversamplingCounter = oversampling;
        }

        if (prescaleCounter == 0) {
            prescaleCounter              = prescaler;
            lastSample                   = read();                      // take a new sample for this sensor and ...
            samples[oversamplingCounter] = lastSample;                  // ... store it in the array of samples
            if (oversamplingCounter == 0) {
                lastMeasurement     = average(oversampling + 1);        // average all samples & output this measurement to NVS
                oversamplingCounter = oversampling;
                return runResult::measured;
            } else {
                oversamplingCounter--;
                prescaleCounter = prescaler;
                return runResult::sampled;
            }
        } else {
            prescaleCounter--;
            return runResult::prescaled;
        }
    } else {
        return runResult::inactive;
    }
}

float sensor::read() {
    switch (type) {
        case measurementChannel::batteryVoltage:
        if (!battery::isAwake()) {
                battery::run();
            }
            return battery::getVoltage();
            break;

        case measurementChannel::batteryChargeLevel:
        if (!battery::isAwake()) {
                battery::run();
            }
            return battery::getChargeLevel();
            break;

        case measurementChannel::BME680SensorTemperature:
            if (!bme680::isAwake()) {
                bme680::run();
            }
            return bme680::getTemperature();
            break;

        case measurementChannel::BME680SensorRelativeHumidity:
            if (!bme680::isAwake()) {
                bme680::run();
            }
            return bme680::getRelativeHumidity();
            break;

        case measurementChannel::BME680SensorBarometricPressure:
            if (!bme680::isAwake()) {
                bme680::run();
            }
            return bme680::getBarometricPressure();
            break;

        default:
            return 0.0F;
            break;
    }
}

void sensor::goSleep() {
    switch (type) {
        case measurementChannel::batteryVoltage:
            break;

        case measurementChannel::BME680SensorTemperature:
        case measurementChannel::BME680SensorRelativeHumidity:
        case measurementChannel::BME680SensorBarometricPressure:
            if (bme680::isAwake()) {
                bme680::goSleep();
            }
            break;

        case measurementChannel::TSL25911Infrared:
        case measurementChannel::TSL25911VisibleLight:
            tsl2591::goSleep();
            break;

        default:
            break;
    }
}

float sensor::average(uint32_t nmbrOfSamples) {
    float sum{0.0F};
    for (uint32_t i = 0; i < nmbrOfSamples; i++) {
        sum += samples[i];
    }
    return (sum / nmbrOfSamples);
}

void sensor::initalize() {
    switch (type) {
        case measurementChannel::batteryVoltage:
            break;

        case measurementChannel::BME680SensorTemperature:
        case measurementChannel::BME680SensorRelativeHumidity:
        case measurementChannel::BME680SensorBarometricPressure:
            bme680::initialize();
            break;

        default:
            break;
    }
}
