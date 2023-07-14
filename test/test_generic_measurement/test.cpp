#include <unity.h>
#include "measurement.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_dummy() {
    (void)toString(measurementChannel::batteryChargeLevel);
    (void)toString(measurementChannel::batteryVoltage);
    (void)toString(measurementChannel::BME680SensorBarometricPressure);
    (void)toString(measurementChannel::BME680SensorRelativeHumidity);
    (void)toString(measurementChannel::BME680SensorTemperature);
    (void)toString(measurementChannel::events);
    (void)toString(measurementChannel::none);
    (void)toString(measurementChannel::status);
    (void)toString(measurementChannel::TSL25911Infrared);
    (void)toString(measurementChannel::TSL25911VisibleLight);
    TEST_IGNORE_MESSAGE("For testCoverage only");
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_dummy);
    UNITY_END();
}