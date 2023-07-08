// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>
#include "nvsmap.h"
#include "measurement.h"

class nonVolatileStorage {
  public:
    static bool isReady();        // testing if the EEPROM is found correctly on the I2C bus
    // bool isInitialized();         // testing if the EEPROM is initialized or still has factory reset values of 0xFF
    // void initializeOnce();        // reset the EEPROM to meaningfull values at our very first boot
    // void initialize();            // initialize the nvsMap for subsequent boots

    // // API to access the Settings section of the EEPROM
    // uint8_t readBlock8(uint32_t blockIndex);                                    // reads uint8_t from a block in EEPROM
    // void writeBlock8(uint32_t blockIndex, uint8_t sourceData);                  // write uint8_t data to a block in EEPROM
    // uint32_t readBlock32(uint32_t blockIndex);                                  // reads uint32_t from a block in EEPROM
    // void writeBlock32(uint32_t blockIndex, uint32_t sourceData);                // write uint32_t data to a block in EEPROM
    // void readBlock(uint32_t blockIndex, uint8_t* destinationDataBuffer);        // reads the block from EEPROM and stores it in the destinationDataBuffer
    // void writeBlock(uint32_t blockIndex, uint8_t* sourceDataBuffer);            // write data from sourceDataBuffer to the block in EEPROM

    // // API to access the Measurement section of the EEPROM
    // void readMeasurement(uint32_t measurementIndex, measurement& destination);        // reads the measurement from EEPROM and stores it in the destination measurement object
    // void writeMeasurement(uint32_t measurementIndex, measurement& source);            // write data from source measurement object to the EEPROM at specific location
    // void writeMeasurement(measurement& source);                                       // write measurement data from sourceDataBuffer to the EEPROM at the next write location, using the measurementWriteIndex

    static constexpr uint32_t size{64 * 1024};

    static constexpr uint8_t i2cAddress{0x50};         // default I2C address of the first EEPROM, the second one has an address i2cAddress+1, set by its A0 pin being ties to VDD
    static constexpr uint8_t halTrials{0x03};          // ST HAL requires a 'retry' parameters
    static constexpr uint8_t halTimeout{100};          // ST HAL requires a 'timeout' in ms
    static constexpr uint8_t writeCycleTime{4};        // [ms] : the BR24G512xxx EEPROM requires a wait time of 3.5 ms after writing to internally store the data

#ifndef unitTesting
  private:
#endif

    // uint32_t measurementWriteIndex{0};                                            // measurement block index where we will write the next measurement
    // uint32_t oldestUnsentMeasurementIndex{0};                                     // measurement block index of the oldest unconfirmed measurement
    // uint32_t oldestUnconfirmedMeasurementindex{0};                                // measurement block index of the oldest unsent measurement
    //                                                                               //    uint32_t nmbrMeasurementBlocks{12288};                // (120*1024)/100 = 12288
    // uint32_t nmbrMeasurementBlocks{6144};                                         // (60*1024)/100 = 6144
    // uint32_t measurementBlockLength{10};                                          // 10 bytes
    // uint32_t measurementsAddressOffset{4096};                                     // First 4K is for settings, Last 60K for measurements

    static void read(uint32_t startAddress, uint8_t* data, uint32_t dataLength);         // low-level I2C reading from EEPROM
    static void write(uint32_t startAddress, uint8_t* data, uint32_t dataLength);        // low-level I2C writing to EEPROM

    static void erase();                                                                 // erase the EEPROM by writing 0xFF to all locations
    static void fill(uint8_t value);                                                     // fill the EEPROM with a specific value
};
