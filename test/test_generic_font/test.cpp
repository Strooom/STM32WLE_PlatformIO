// #############################################################################
// ### This file is part of the source code for the MuMo project             ###
// ### https://github.com/Strooom/MuMo-v2-Node-SW                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################
#include <unity.h>
#include "display.h"
#include "graphics.h"
#include "font.h"

extern font couriernew12;

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_isInBounds1() {
    TEST_ASSERT_TRUE(font::isInBounds(32));
    TEST_ASSERT_TRUE(font::isInBounds(126));
    TEST_ASSERT_FALSE(font::isInBounds(31));
    TEST_ASSERT_FALSE(font::isInBounds(127));
}

void test_isInBounds2() {
    TEST_ASSERT_TRUE(couriernew12.isInBounds(0, 0));
    TEST_ASSERT_TRUE(couriernew12.isInBounds(6, 0));
    TEST_ASSERT_TRUE(couriernew12.isInBounds(0, 11));
    TEST_ASSERT_TRUE(couriernew12.isInBounds(6, 11));

    TEST_ASSERT_FALSE(couriernew12.isInBounds(7, 0));
    TEST_ASSERT_FALSE(couriernew12.isInBounds(0, 12));
    TEST_ASSERT_FALSE(couriernew12.isInBounds(7, 12));
}

void test_initialize() {
    font testFont1(8, 8, nullptr);
    TEST_ASSERT_EQUAL(1, testFont1.bytesPerRow);
    TEST_ASSERT_EQUAL(8, testFont1.bytesPerCharacter);

    font testFont2(12, 7, nullptr);
    TEST_ASSERT_EQUAL(1, testFont2.bytesPerRow);
    TEST_ASSERT_EQUAL(12, testFont2.bytesPerCharacter);

    font testFont3(20, 11, nullptr);
    TEST_ASSERT_EQUAL(2, testFont3.bytesPerRow);
    TEST_ASSERT_EQUAL(40, testFont3.bytesPerCharacter);
}

void test_getByteIndex1() {
    font testFont1(8, 8, nullptr);
    TEST_ASSERT_EQUAL(0, testFont1.getByteIndex(32));
    TEST_ASSERT_EQUAL((126 - 32) * 8, testFont1.getByteIndex(126));
}

void test_getByteIndex2() {
    TEST_ASSERT_EQUAL(11, couriernew12.getByteIndex(0, 0));
    TEST_ASSERT_EQUAL(11, couriernew12.getByteIndex(6, 0));
    TEST_ASSERT_EQUAL(0, couriernew12.getByteIndex(0, 11));
    TEST_ASSERT_EQUAL(0, couriernew12.getByteIndex(6, 11));
}

void test_getPixel() {
    uint8_t testChar = '_';
    TEST_ASSERT_TRUE(couriernew12.getPixel(0, 0, testChar));
    TEST_ASSERT_TRUE(couriernew12.getPixel(6, 0, testChar));
    TEST_ASSERT_FALSE(couriernew12.getPixel(0, 1, testChar));
    TEST_ASSERT_FALSE(couriernew12.getPixel(6, 1, testChar));
}

void test_getPixelOutOfBounds() {
    uint8_t testChar = 128;
    TEST_ASSERT_FALSE(couriernew12.getPixel(0, 0, testChar));
    testChar = 32;
    TEST_ASSERT_FALSE(couriernew12.getPixel(7, 0, testChar));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_isInBounds1);
    RUN_TEST(test_isInBounds2);
    RUN_TEST(test_initialize);
    RUN_TEST(test_getByteIndex1);
    RUN_TEST(test_getByteIndex2);
    RUN_TEST(test_getPixel);
    RUN_TEST(test_getPixelOutOfBounds);
    UNITY_END();
}