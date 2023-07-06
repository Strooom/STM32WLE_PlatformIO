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

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_inBounds);
    RUN_TEST(test_swapCoordinates);
    RUN_TEST(test_mirrorCoordinate);
    RUN_TEST(test_mirrorCoordinates);
    RUN_TEST(test_rotateCoordinates);
    UNITY_END();
}