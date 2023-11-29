#include <unity.h>
#include "power.h"
#include "sensordevicetype.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_dummy_for_coverage() {
    TEST_ASSERT_EQUAL_STRING("battery", toString(sensorDeviceType::battery));
    TEST_ASSERT_EQUAL_STRING("bme680", toString(sensorDeviceType::bme680));
    TEST_ASSERT_EQUAL_STRING("bme688", toString(sensorDeviceType::bme688));
    TEST_ASSERT_EQUAL_STRING("tsl2591", toString(sensorDeviceType::tsl2591));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_dummy_for_coverage);
    UNITY_END();
}
