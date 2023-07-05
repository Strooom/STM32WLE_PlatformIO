#include "graphics.h"
#include "display.h"

// Initialize the static variables

static graphics::colorMode theColorMode{graphics::colorMode::normal};

void graphics::drawPixel(uint32_t x, uint32_t y, color theColor) {
    if ((theColor == color::black) == (theColorMode == colorMode::normal)) {        // EXOR : black on normal = black, white on inverted = black, white on normal = white, black on inverted = white
        display::setPixel(x, y);
    } else {
        display::clearPixel(x, y);
    }
}

void graphics::drawHorizontalLine(uint32_t xStart, uint32_t y, uint32_t xEnd, color theColor) {
    sort(xStart, xEnd);
    for (uint32_t x = xStart; x <= xEnd; x++) {
        drawPixel(x, y, theColor);
    }
}

void graphics::drawVerticalLine(uint32_t x, uint32_t yStart, uint32_t yEnd, color theColor) {
    sort(yStart, yEnd);
    for (uint32_t y = yStart; x <= yEnd; y++) {
        drawPixel(x, y, theColor);
    }
}

void graphics::drawRectangle(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd, color theLineColor) {
    sort(xStart, xEnd);
    sort(yStart, yEnd);

    drawHorizontalLine(xStart, yStart, xEnd, theLineColor);
    drawHorizontalLine(xStart, yEnd, xEnd, theLineColor);
    drawVerticalLine(xStart, yStart, yEnd, theLineColor);
    drawVerticalLine(xEnd, yStart, yEnd, theLineColor);
}

void graphics::drawFilledRectangle(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd, color theFillColor) {
    sort(xStart, xEnd);
    sort(yStart, yEnd);

    for (uint32_t yIndex = yStart; yIndex <= yEnd; yIndex++) {
        drawHorizontalLine(xStart, yIndex, xEnd, theFillColor);
    }
}

void graphics::sort(uint32_t &c1, uint32_t &c2) {
    if (c1 > c2) {
        uint32_t temp = c1;
        c1            = c2;
        c2            = temp;
    }
}
