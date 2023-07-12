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

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_isInBounds() {
    TEST_ASSERT_TRUE(font::isInBounds(32));
    TEST_ASSERT_TRUE(font::isInBounds(126));
    TEST_ASSERT_FALSE(font::isInBounds(31));
    TEST_ASSERT_FALSE(font::isInBounds(127));
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

void test_byteOffset() {
    font testFont1(8, 8, nullptr);
    TEST_ASSERT_EQUAL(0, testFont1.byteOffset(32));
    TEST_ASSERT_EQUAL((126-32) * 8, testFont1.byteOffset(126));
    TEST_ASSERT_EQUAL(0, testFont1.byteOffset(20));
}



int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_isInBounds);
    RUN_TEST(test_initialize);
    RUN_TEST(test_byteOffset);
    UNITY_END();
}