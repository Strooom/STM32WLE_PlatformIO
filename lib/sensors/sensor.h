// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>
#include "sensortype.h"
#include "sensorstate.h"

class sensor {
  public:
    enum class runResult : uint32_t {
        inactive,
        prescaled,
        sampled,
        measured
    };
    void initalize();
    runResult run();        // checks if this sensor needs to be sampled, and if so, samples it, and if enough samples are collected, calculate the average and store it as the lastValue
    void goSleep();



#ifndef unitTesting

  private:
#endif
    state currentState{state::boot};
    sensorType type{sensorType::none};

    static constexpr uint32_t maxPrescaler{4095};         // take a sample every x times of the 30 second RTC tick. 0 means : don't sample this sensor
    static constexpr uint32_t maxOversampling{15};        // average x+1 samples before storing it in the sample collection

    uint32_t oversamplingLowPower{0};                     // controls oversampling for low power mode : on battery
    uint32_t prescalerLowPower{0};                        // controls prescaling for low power mode : on battery
    uint32_t oversamplingHighPower{0};                    // high power mode : on USB power
    uint32_t prescalerHighPower{0};                       //

    float samples[maxOversampling + 1]{};
    uint32_t oversamplingCounter{0};
    uint32_t prescaleCounter{0};

    float lastValue{0.0F};
    uint32_t lastValueTimestamp{0};

    float sample();                               // reads the sensor and store the value into to sample[] array
    float average(uint32_t nmbrOfSamples);        // calculates a measurement from samples

    friend class sensorCollection;                // collection is allowed access to the internals of each sensor in its collection
};