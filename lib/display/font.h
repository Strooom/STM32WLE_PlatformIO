// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>

class font {
  public:
    font(uint32_t pixelheight, uint32_t pixelwidth, const uint8_t* pixelData);
    const uint32_t pixelheight;
    const uint32_t pixelwidth;
    const uint8_t* pixelData;

  private:
};
