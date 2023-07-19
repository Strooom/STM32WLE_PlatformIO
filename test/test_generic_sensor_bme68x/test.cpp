#include <unity.h>
#include "bme680.h"

uint8_t mockRegisters[256]{};

void setUp(void) {
    mockRegisters[static_cast<uint8_t>(bme680::registers::chipId)]      = bme680::chipIdValue;
    mockRegisters[static_cast<uint8_t>(bme680::registers::meas_status)] = 0x80;

    // Calibration data
    // Read I2C : register = [8A], data[23] = [62 67 03 10 8F 90 68 D7 58 00 38 22 62 FF 2C 1E 00 00 71 F4 5B F6 1E ]
    // Read I2C : register = [E1], data[14] = [3D BD 37 00 2D 14 78 9C B6 65 AB DC FB 12 ]
    // Read I2C : register = [00], data[5] = [28 AA 16 4C 03 ]

    // Raw data
    // Read I2C : register = [1F], data[8] = [00 00 00 00 00 00 00 00 ]
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

void test_measurements() {
    bme680::sample();
    TEST_ASSERT_EQUAL_FLOAT(0.0F, bme680::getTemperature());
    TEST_ASSERT_EQUAL_FLOAT(0.0F, bme680::getRelativeHumidity());
    TEST_ASSERT_EQUAL_FLOAT(0.0F, bme680::getBarometricPressure());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_isPresent);
    RUN_TEST(test_initialize);
    RUN_TEST(test_sample);
    RUN_TEST(test_measurements);
    UNITY_END();
}
