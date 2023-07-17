// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>

// application settings are stored in the EEPROM
// they can have different sizes (uint8t = 1 byte, uint32_t = 4 bytes, aesKey = 16 bytes, ...)
// so each setting has a startAddress and a length

    class setting {
      public:
        const uint32_t startAddress;
        const uint32_t length;
    };


