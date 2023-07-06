// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>
#include "font.h"

class graphics {
  public:
    enum class color : uint32_t { black = 0,
                                  white = 1 };

    enum class colorMode : uint32_t { normal   = 0,          // black on white background
                                      inverted = 1 };        // white on black background

    enum class font : uint32_t { font12 = 0,
                                 font24 = 1 };

    static void drawPixel(uint32_t x, uint32_t y, color theColor);
    static void drawLine(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd, color theColor);
    static void drawHorizontalLine(uint32_t xStart, uint32_t y, uint32_t xEnd, color theColor);
    static void drawVerticalLine(uint32_t x, uint32_t yStart, uint32_t yEnd, color theColor);
    static void drawRectangle(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd, color theLineColor);
    static void drawFilledRectangle(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd, color theFillColor);
    static void drawText(uint32_t xStart, uint32_t yStart, font theFont, color theColor, unsigned char* theText);
    static void drawBitMap(uint32_t xStart, uint32_t yStart, color theColor, uint8_t* theBitmap);

#ifndef unitTesting
  private:
#endif
    static colorMode theColorMode;
static void sort(uint32_t &c1, uint32_t &c2);
  private:
};