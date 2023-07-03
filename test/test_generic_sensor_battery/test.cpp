#include <unity.h>
#include "battery.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_check() {
    TEST_ASSERT_TRUE(battery::checkVoltageVsCharge());
}

void test_interpolation() {
    TEST_ASSERT_EQUAL_UINT8(0, battery::calculateCharge(2.0F));           // voltage below minimum
    TEST_ASSERT_EQUAL_UINT8(0, battery::calculateCharge(2.80F));          // voltage at minimum
    TEST_ASSERT_EQUAL_UINT8(255, battery::calculateCharge(3.60F));        // voltage at maximum
    TEST_ASSERT_EQUAL_UINT8(255, battery::calculateCharge(4.0F));         // voltage above maximum

    TEST_ASSERT_EQUAL_UINT8(128, battery::calculateCharge(3.2F));         // voltage at 50%
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_check);
    RUN_TEST(test_interpolation);
    UNITY_END();
}
