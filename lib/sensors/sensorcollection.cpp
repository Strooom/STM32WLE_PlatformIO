// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#include "sensorcollection.h"
#include "bme680.h"
#include "tsl2591.h"
#include "logging.h"

sensorCollection::runResult sensorCollection::run() {
    actualNumberOfMeasurements = 0;        // reset the array of measurements

    for (uint32_t sensorIndex = 0; sensorIndex < actualNumberOfSensors; sensorIndex++) {
        sensor::runResult theResult = theSensorCollection[sensorIndex].run();
        switch (theResult) {
            case sensor::runResult::inactive:
                break;
            case sensor::runResult::prescaled:
                logging::snprintf(logging::source::sensorEvents, "Sensor %s : prescale tick\n", toString(theSensorCollection[sensorIndex].type));
                break;
            case sensor::runResult::sampled:
                logging::snprintf(logging::source::sensorEvents, "Sensor %s : sampled %.2f\n", toString(theSensorCollection[sensorIndex].type), theSensorCollection[sensorIndex].lastValue);
                break;
            case sensor::runResult::measured:
                logging::snprintf(logging::source::sensorEvents, "Sensor %s : measurement %.4f\n", toString(theSensorCollection[sensorIndex].type), theSensorCollection[sensorIndex].lastValue);
                addMeasurement(theSensorCollection[sensorIndex].type, theSensorCollection[sensorIndex].lastValue);
                break;
        }
    }

    // After all measurements are done, check them all and put them to sleep if needed.
    for (uint32_t sensorIndex = 0; sensorIndex < actualNumberOfSensors; sensorIndex++) {
        theSensorCollection[sensorIndex].goSleep();
    }

    if (actualNumberOfMeasurements > 0) {
        return runResult::newMeasurements;
    } else {
        return runResult::none;
    }
}

void sensorCollection::discover() {
    // addSensor(sensorType::batteryVoltage, 7, 359, 7, 14);        // one measurement per day on battery, one per hour on USB power
    // addSensor(sensorType::batteryVoltage, 0, 3, 0, 3);        // test Version
    addSensor(sensorType::batteryVoltage, 3, 59, 3, 4);        // test Version

    if (bme680::isPresent()) {
        bme680::initialize();        // this reads the calibration data from the sensor
        // addSensor(sensorType::BME680Temperature, 3, 14, 3, 14);               // one measurement per 30 minutes
        // addSensor(sensorType::BME680RelativeHumidity, 3, 29, 3, 29);          // one measurement per 60 minutes
        // addSensor(sensorType::BME680BarometricPressure, 3, 59, 3, 59);        // one measurement per 120 minutes
        addSensor(sensorType::BME680Temperature, 3, 59, 3, 4);               // test
        addSensor(sensorType::BME680RelativeHumidity, 3, 59, 3, 4);          // test
        addSensor(sensorType::BME680BarometricPressure, 3, 59, 3, 4);        // test
    }

    // if (tsl2591::isPresent()) {
    //     //        addSensor(sensorType::TSL25911VisibleLight, 3, 9, 3, 9);        //
    //     //        addSensor(sensorType::TSL25911Infrared, 3, 9, 3, 9);            //
    // }
}

void sensorCollection::addSensor(sensorType aType, uint32_t oversamplingLowPower, uint32_t prescalerLowPower, uint32_t oversamplingHighPower, uint32_t prescalerHighPower) {
    if (actualNumberOfSensors < maxNumberOfSensors) {
        if (oversamplingLowPower > sensor::maxOversampling) {
            oversamplingLowPower = sensor::maxOversampling;
        }
        if (oversamplingHighPower > sensor::maxOversampling) {
            oversamplingHighPower = sensor::maxOversampling;
        }
        if (prescalerLowPower > sensor::maxPrescaler) {
            prescalerLowPower = sensor::maxPrescaler;
        }
        if (prescalerHighPower > sensor::maxPrescaler) {
            prescalerHighPower = sensor::maxPrescaler;
        }
        theSensorCollection[actualNumberOfSensors].type                  = aType;
        theSensorCollection[actualNumberOfSensors].oversamplingLowPower  = oversamplingLowPower;
        theSensorCollection[actualNumberOfSensors].prescalerLowPower     = prescalerLowPower;
        theSensorCollection[actualNumberOfSensors].oversamplingHighPower = oversamplingHighPower;
        theSensorCollection[actualNumberOfSensors].prescalerHighPower    = prescalerHighPower;

        theSensorCollection[actualNumberOfSensors].oversamplingCounter = sensor::maxOversampling;        // will be reduced to either oversamplingLowPower or oversamplingHighPower on the first run. If it would be initialized to 0, it would output a measurement on first run without having done all the samples

        actualNumberOfSensors++;
    } else {
        // TODO : log the error
    }
}

void sensorCollection::addMeasurement(sensorType aType, float aValue) {
    if (actualNumberOfMeasurements < maxNumberOfSensors) {
        latestMeasurements[actualNumberOfMeasurements].timestamp.asDoubleWord = measurement::getTimeStamp();
        latestMeasurements[actualNumberOfMeasurements].type                   = aType;
        latestMeasurements[actualNumberOfMeasurements].value.asFloat          = aValue;
        latestMeasurements[actualNumberOfMeasurements].flags                  = 0;
        actualNumberOfMeasurements++;
    }
}
