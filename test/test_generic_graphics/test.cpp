// #############################################################################
// ### This file is part of the source code for the MuMo project             ###
// ### https://github.com/Strooom/MuMo-v2-Node-SW                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################
#include <unity.h>
#include "graphics.h"
#include "display.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_drawPixel() {
    // draw pixel in the 4 corners, and check the displayBuffer before and after
    display::clearAllPixels();
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;

    graphics::drawPixel(0, 0, graphics::color::black);
    TEST_ASSERT_EQUAL(0b10000000, display::displayBuffer[0]);
    graphics::drawPixel(0, 0, graphics::color::white);
    TEST_ASSERT_EQUAL(0, display::displayBuffer[0]);

    graphics::drawPixel((display::width - 1), 0, graphics::color::black);
    TEST_ASSERT_EQUAL(0b00000001, display::displayBuffer[24]);
    graphics::drawPixel((display::width - 1), 0, graphics::color::white);
    TEST_ASSERT_EQUAL(0, display::displayBuffer[24]);

    graphics::drawPixel(0, (display::height - 1), graphics::color::black);
    TEST_ASSERT_EQUAL(0b10000000, display::displayBuffer[4999 - 24]);
    graphics::drawPixel(0, (display::height - 1), graphics::color::white);
    TEST_ASSERT_EQUAL(0, display::displayBuffer[4999 - 24]);

    graphics::drawPixel((display::width - 1), (display::height - 1), graphics::color::black);
    TEST_ASSERT_EQUAL(0b00000001, display::displayBuffer[4999]);
    graphics::drawPixel((display::width - 1), (display::height - 1), graphics::color::white);
    TEST_ASSERT_EQUAL(0, display::displayBuffer[4999]);
}

void test_drawHorizontalLine() {
    display::clearAllPixels();
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;

    graphics::drawHorizontalLine(0, display::width - 1, 0, graphics::color::black);
    for (auto i = 0; i < 25; i++) {
        TEST_ASSERT_EQUAL(0xFF, display::displayBuffer[i]);
    }
    for (auto i = 25; i < 5000; i++) {
        TEST_ASSERT_EQUAL(0x00, display::displayBuffer[i]);
    }
    display::clearAllPixels();
    graphics::drawHorizontalLine(display::width - 1, 0, 0, graphics::color::black);
    for (auto i = 0; i < 25; i++) {
        TEST_ASSERT_EQUAL(0xFF, display::displayBuffer[i]);
    }
    for (auto i = 25; i < 5000; i++) {
        TEST_ASSERT_EQUAL(0x00, display::displayBuffer[i]);
    }
}

void test_drawVerticalLine() {
    display::clearAllPixels();
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;

    graphics::drawVerticalLine(0, 0, display::height - 1, graphics::color::black);
    for (auto i = 0; i < 200; i++) {
        TEST_ASSERT_EQUAL(0b10000000, display::displayBuffer[i * 25]);
    }
    display::clearAllPixels();

    graphics::drawVerticalLine(0, display::height - 1, 0, graphics::color::black);
    for (auto i = 0; i < 200; i++) {
        TEST_ASSERT_EQUAL(0b10000000, display::displayBuffer[i * 25]);
    }
}

void test_drawRectangle() {
    display::clearAllPixels();
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;
    graphics::drawRectangle(0, 0, display::width - 1, display::height - 1, graphics::color::black);
    for (auto i = 0; i < 25; i++) {
        TEST_ASSERT_EQUAL(0xFF, display::displayBuffer[i]);
    }
    for (auto i = 4975; i < 5000; i++) {
        TEST_ASSERT_EQUAL(0xFF, display::displayBuffer[i]);
    }
    for (auto i = 1; i < 199; i++) {
        TEST_ASSERT_EQUAL(0b10000000, display::displayBuffer[i * 25]);
    }
    for (auto i = 1; i < 199; i++) {
        TEST_ASSERT_EQUAL(0b00000001, display::displayBuffer[(i * 25) + 24]);
    }
}

void test_drawFilledRectangle() {
    display::clearAllPixels();
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;
    graphics::drawFilledRectangle(0, 0, display::width - 1, 7, graphics::color::black);
    for (auto i = 0; i < (25 * 8); i++) {
        TEST_ASSERT_EQUAL(0xFF, display::displayBuffer[i]);
    }
    for (auto i = (25 * 8); i < 5000; i++) {
        TEST_ASSERT_EQUAL(0x00, display::displayBuffer[i]);
    }
}

void test_drawBitMap() {
    const uint8_t testPixelData[8] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    bitmap testBitMap1{8, 8, testPixelData};
    display::clearAllPixels();
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;
    graphics::drawBitMap(8, 8, testBitMap1);

    for (auto i = 0; i < (25 * 8); i++) {
        TEST_ASSERT_EQUAL(0, display::displayBuffer[i]);
    }
    for (auto i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL(0, display::displayBuffer[(25 * 8) + (25 * i)]);
        TEST_ASSERT_EQUAL(0xAA, display::displayBuffer[(25 * 8) + (25 * i) + 1]);
        TEST_ASSERT_EQUAL(0, display::displayBuffer[(25 * 8) + (25 * i) + 2]);
    }
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_drawPixel);
    RUN_TEST(test_drawHorizontalLine);
    RUN_TEST(test_drawVerticalLine);
    RUN_TEST(test_drawRectangle);
    RUN_TEST(test_drawFilledRectangle);
    RUN_TEST(test_drawBitMap);
    UNITY_END();
}