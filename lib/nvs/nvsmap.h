// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>

class nvsMap {
  public:
    class block {
      public:
        const uint32_t startAddress;
        const uint32_t length;
    };
    enum class blockIndex : uint32_t {
        nvsMapVersion = 0,
        displayVersion,
        batteryVersion,
        unusedGeneral,
        activeloggingSources,

        measurementWriteIndex,
        oldestUnsentMeasurementIndex,
        oldestUnconfirmedMeasurementindex,
        unusedMeasurementDataManagement,

        DevEUI,
        DevAddr,
        uplinkFrameCounter,
        downlinkFrameCounter,
        applicationSessionKey,
        networkSessionKey,
        rx1Delay,
        unusedLoRaWAN,

        numberOfBlocks
    };
    static bool isValidBlockIndex(uint32_t blockIndex);

#ifndef unitTesting
  private:
#endif
    static const block blocks[static_cast<uint32_t>(blockIndex::numberOfBlocks)];
};
