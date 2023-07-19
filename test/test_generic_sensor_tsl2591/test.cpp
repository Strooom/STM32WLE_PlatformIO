#include <unity.h>
#include "tsl2591.h"

uint8_t mockRegisters[256];

void setUp(void) {
    mockRegisters[static_cast<uint8_t>(tsl2591::registers::id)]      = tsl2591::chipIdValue;
}

void tearDown(void) {}        // after test

void test_isPresent() {
    TEST_ASSERT_TRUE(tsl2591::isPresent());
}

void test_initialize() {
    TEST_ASSERT_EQUAL(sensorState::boot, tsl2591::state);
    tsl2591::initialize();
    TEST_ASSERT_EQUAL(sensorState::idle, tsl2591::state);
}

void test_sample() {
    tsl2591::sample();
    TEST_ASSERT_EQUAL_UINT32(0, tsl2591::rawChannel0);
    TEST_ASSERT_EQUAL_UINT32(0, tsl2591::rawChannel1);

}

// void test_measurements() {
//     bme680::sample();
//     TEST_ASSERT_EQUAL_FLOAT(0.0F, bme680::getTemperature());
//     TEST_ASSERT_EQUAL_FLOAT(0.0F, bme680::getRelativeHumidity());
//     TEST_ASSERT_EQUAL_FLOAT(0.0F, bme680::getBarometricPressure());
// }

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_isPresent);
    RUN_TEST(test_initialize);
    RUN_TEST(test_sample);
    //RUN_TEST(test_measurements);
    UNITY_END();
}