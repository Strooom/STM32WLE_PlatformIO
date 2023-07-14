// #############################################################################
// ### This file is part of the source code for the MuMo project             ###
// ### https://github.com/Strooom/MuMo-v2-Node-SW                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################
#include <unity.h>
#include "display.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_inBounds() {
    uint32_t displayWidthHeight{display::width};        // 200
    TEST_ASSERT_TRUE(display::inBounds(0));
    TEST_ASSERT_TRUE(display::inBounds(displayWidthHeight - 1));
    TEST_ASSERT_FALSE(display::inBounds(displayWidthHeight));

    TEST_ASSERT_TRUE(display::inBounds(0, 0));
    TEST_ASSERT_TRUE(display::inBounds(0, displayWidthHeight - 1));
    TEST_ASSERT_TRUE(display::inBounds(displayWidthHeight - 1, 0));
    TEST_ASSERT_TRUE(display::inBounds(displayWidthHeight - 1, displayWidthHeight - 1));

    TEST_ASSERT_FALSE(display::inBounds(displayWidthHeight, 0));
    TEST_ASSERT_FALSE(display::inBounds(0, displayWidthHeight));
    TEST_ASSERT_FALSE(display::inBounds(displayWidthHeight, displayWidthHeight));
}

void test_swapCoordinates() {
    uint32_t c1{1};
    uint32_t c2{2};
    display::swapCoordinates(c1, c2);
    TEST_ASSERT_EQUAL(2, c1);
    TEST_ASSERT_EQUAL(1, c2);
}

void test_mirrorCoordinate() {
    uint32_t c{10};
    display::mirrorCoordinate(c, display::width);
    TEST_ASSERT_EQUAL(189, c);
}

void test_mirrorCoordinates() {
    {
        uint32_t xTest{10};
        uint32_t yTest{20};
        display::rotation  = displayRotation::rotation0;
        display::mirroring = displayMirroring::none;
        display::rotateAndMirrorCoordinates(xTest, yTest);
        TEST_ASSERT_EQUAL(10, xTest);
        TEST_ASSERT_EQUAL(20, yTest);
    }
    {
        uint32_t xTest{10};
        uint32_t yTest{20};
        display::mirroring = displayMirroring::horizontal;
        display::rotateAndMirrorCoordinates(xTest, yTest);
        TEST_ASSERT_EQUAL((display::width - 1) - 10, xTest);
        TEST_ASSERT_EQUAL(20, yTest);
    }
    {
        uint32_t xTest{10};
        uint32_t yTest{20};
        display::mirroring = displayMirroring::vertical;
        display::rotateAndMirrorCoordinates(xTest, yTest);
        TEST_ASSERT_EQUAL((display::width - 1) - 20, yTest);
        TEST_ASSERT_EQUAL(10, xTest);
    }
    {
        uint32_t xTest{10};
        uint32_t yTest{20};
        display::mirroring = displayMirroring::both;
        display::rotateAndMirrorCoordinates(xTest, yTest);
        TEST_ASSERT_EQUAL((display::width - 1) - 10, xTest);
        TEST_ASSERT_EQUAL((display::width - 1) - 20, yTest);
    }
}

void test_rotateCoordinates() {
    {
        uint32_t xTest{10};
        uint32_t yTest{20};
        display::mirroring = displayMirroring::none;
        display::rotation  = displayRotation::rotation0;
        display::rotateAndMirrorCoordinates(xTest, yTest);
        TEST_ASSERT_EQUAL(10, xTest);
        TEST_ASSERT_EQUAL(20, yTest);
    }
    {
        uint32_t xTest{10};
        uint32_t yTest{20};
        display::rotation = displayRotation::rotation90;
        display::rotateAndMirrorCoordinates(xTest, yTest);
        TEST_ASSERT_EQUAL(20, xTest);
        TEST_ASSERT_EQUAL((display::width - 1) - 10, yTest);
    }
    {
        uint32_t xTest{10};
        uint32_t yTest{20};
        display::rotation = displayRotation::rotation180;
        display::rotateAndMirrorCoordinates(xTest, yTest);
        TEST_ASSERT_EQUAL((display::width - 1) - 10, xTest);
        TEST_ASSERT_EQUAL((display::width - 1) - 20, yTest);
    }
    {
        uint32_t xTest{10};
        uint32_t yTest{20};
        display::rotation = displayRotation::rotation270;
        display::rotateAndMirrorCoordinates(xTest, yTest);
        TEST_ASSERT_EQUAL((display::width - 1) - 20, xTest);
        TEST_ASSERT_EQUAL(10, yTest);
    }
}

void test_getByteOffset() {
    TEST_ASSERT_EQUAL(0, display::getByteOffset(0, 0));
    TEST_ASSERT_EQUAL((display::bufferSize - 1), display::getByteOffset((display::width - 1), (display::height - 1)));
}

void test_getBitOffset() {
    TEST_ASSERT_EQUAL(7, display::getBitOffset(0));
    TEST_ASSERT_EQUAL(0, display::getBitOffset(display::width - 1));
}

void test_setPixel() {
    display::clearAllPixels();
    // set the pixel in the four corners, and check the related bytes in the buffer
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;
    display::setPixel(0, 0);
    TEST_ASSERT_EQUAL(0b10000000, display::displayBuffer[0]);
    display::setPixel((display::width - 1), 0);
    TEST_ASSERT_EQUAL(0b00000001, display::displayBuffer[24]);
    display::setPixel(0, (display::height - 1));
    TEST_ASSERT_EQUAL(0b10000000, display::displayBuffer[5000 - 25]);
    display::setPixel((display::width - 1), (display::height - 1));
    TEST_ASSERT_EQUAL(0b00000001, display::displayBuffer[5000 - 1]);
}

void test_clearPixel() {
    // set all pixels
    for (uint32_t i = 0; i < display::bufferSize; i++) {
        display::displayBuffer[i] = 0xFF;        // sets all pixels on, so we can easily test the clearPixel function
    }
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;

    display::clearPixel(0, 0);
    TEST_ASSERT_EQUAL(0b01111111, display::displayBuffer[0]);
    display::clearPixel((display::width - 1), 0);
    TEST_ASSERT_EQUAL(0b11111110, display::displayBuffer[24]);
    display::clearPixel(0, (display::height - 1));
    TEST_ASSERT_EQUAL(0b01111111, display::displayBuffer[5000 - 25]);
    display::clearPixel((display::width - 1), (display::height - 1));
    TEST_ASSERT_EQUAL(0b11111110, display::displayBuffer[5000 - 1]);
}

void test_changePixel() {
    display::clearAllPixels();
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;
    for (uint32_t y = 0; y < display::height; y++) {
        for (uint32_t x = 0; x < display::width; x++) {
            display::changePixel(x, y, ((x + y) % 2));
        }
    }

    for (uint32_t y = 0; y < display::height; y++) {
        for (uint32_t x = 0; x < (display::width / 8); x++) {
            if (y % 2) {
                TEST_ASSERT_EQUAL(0b10101010, display::displayBuffer[25 * y + x]);
            } else {
                TEST_ASSERT_EQUAL(0b01010101, display::displayBuffer[25 * y + x]);
            }
        }
    }
}

void test_changePixelOutOfBounds() {
    display::clearAllPixels();
    display::mirroring = displayMirroring::none;
    display::rotation  = displayRotation::rotation0;

    display::changePixel(200, 0, true);        // set some pixels outside the display area
    display::changePixel(0, 200, true);
    display::changePixel(200, 200, true);

    for (uint32_t i = 0; i < display::bufferSize; i++) {
        TEST_ASSERT_EQUAL(0, display::displayBuffer[i]);        // all of the displaybuffer should still be cleared
    }
}

void test_dummy() {
    display::initialize();
    display::goSleep();
    TEST_IGNORE_MESSAGE("For testCoverage only");
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_inBounds);
    RUN_TEST(test_swapCoordinates);
    RUN_TEST(test_mirrorCoordinate);
    RUN_TEST(test_mirrorCoordinates);
    RUN_TEST(test_rotateCoordinates);
    RUN_TEST(test_getByteOffset);
    RUN_TEST(test_getBitOffset);
    RUN_TEST(test_setPixel);
    RUN_TEST(test_clearPixel);
    RUN_TEST(test_changePixel);
    RUN_TEST(test_changePixelOutOfBounds);
    RUN_TEST(test_dummy);
    UNITY_END();
}