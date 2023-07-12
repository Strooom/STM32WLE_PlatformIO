// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>

class font {
  public:
    font(const uint32_t thePixelHeight, const uint32_t thePixelWidth, const uint8_t* thePixelData) : pixelHeight(thePixelHeight), pixelWidth(thePixelWidth), bytesPerRow(((thePixelWidth - 1) / 8) + 1), bytesPerCharacter(pixelHeight * bytesPerRow), pixelData(thePixelData){};
    const uint32_t pixelHeight;
    const uint32_t pixelWidth;
    const uint32_t bytesPerRow;
    const uint32_t bytesPerCharacter;
    const uint8_t* pixelData;

    static constexpr uint8_t asciiStart = 32;        // making this static implies that ALL fonts have the characterset : 32..126
    static constexpr uint8_t asciiEnd   = 126;

#ifndef unitTesting

  private:
#endif
    static bool isInBounds(uint8_t asciiCode);
    uint32_t byteOffset(uint8_t asciiCode) const;
};
