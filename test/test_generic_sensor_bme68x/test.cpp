#include <unity.h>
#include "bme680.h"

extern uint8_t mockRegisters[256];

void setUp(void) {
    mockRegisters[static_cast<uint8_t>(bme680::registers::chipId)]      = bme680::chipIdValue;
    mockRegisters[static_cast<uint8_t>(bme680::registers::meas_status)] = 0x80;
}

void tearDown(void) {}        // after test

void test_isPresent() {
    TEST_ASSERT_TRUE(bme680::isPresent());
}

void test_initialize() {
    TEST_ASSERT_EQUAL(sensorState::boot, bme680::state);
    bme680::initialize();
    // TODO : check calibration data is read correctly
    TEST_ASSERT_EQUAL(sensorState::idle, bme680::state);
}

void test_sample() {
    bme680::sample();
    TEST_ASSERT_EQUAL_UINT32(0, bme680::rawDataTemperature);
    TEST_ASSERT_EQUAL_UINT32(0, bme680::rawDataRelativeHumidity);
    TEST_ASSERT_EQUAL_UINT32(0, bme680::rawDataBarometricPressure);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_isPresent);
    RUN_TEST(test_initialize);
    RUN_TEST(test_sample);
    UNITY_END();
}
