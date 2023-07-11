#include "graphics.h"
#include "display.h"

// Initialize the static variables

void graphics::drawPixel(uint32_t x, uint32_t y, color theColor) {
    if (theColor == color::black) {
        display::setPixel(x, y);
    } else {
        display::clearPixel(x, y);
    }
}

void graphics::drawHorizontalLine(uint32_t xStart, uint32_t xEnd, uint32_t y, color theColor) {
    sort(xStart, xEnd);
    for (uint32_t x = xStart; x <= xEnd; x++) {
        drawPixel(x, y, theColor);
    }
}

void graphics::drawVerticalLine(uint32_t x, uint32_t yStart, uint32_t yEnd, color theColor) {
    sort(yStart, yEnd);
    for (uint32_t y = yStart; y <= yEnd; y++) {
        drawPixel(x, y, theColor);
    }
}

void graphics::drawRectangle(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd, color theLineColor) {
    sort(xStart, xEnd);
    sort(yStart, yEnd);

    drawHorizontalLine(xStart, xEnd, yStart, theLineColor);
    drawHorizontalLine(xStart, xEnd, yEnd, theLineColor);
    drawVerticalLine(xStart, yStart, yEnd, theLineColor);
    drawVerticalLine(xEnd, yStart, yEnd, theLineColor);
}

void graphics::drawFilledRectangle(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd, color theFillColor) {
    sort(xStart, xEnd);
    sort(yStart, yEnd);

    for (uint32_t yIndex = yStart; yIndex <= yEnd; yIndex++) {
        drawHorizontalLine(xStart, xEnd, yIndex, theFillColor);
    }
}

void graphics::sort(uint32_t &c1, uint32_t &c2) {
    if (c1 > c2) {
        uint32_t temp = c1;
        c1            = c2;
        c2            = temp;
    }
}

void graphics::drawBitMap(uint32_t xStart, uint32_t yStart, const bitmap &theBitmap) {
    for (uint32_t x = 0; x < theBitmap.width; x++) {
        for (uint32_t y = 0; y < theBitmap.height; y++) {
            if (theBitmap.getPixel(x, y)) {
                drawPixel(xStart + x, yStart + y, color::black);
            }
        }
    }
}