#include <unity.h>
#include "sensorcollection.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test



// void test_sensorCollection_discover() {
//     sensorChannelCollection aCollection;
//     aCollection.discover();
//     TEST_ASSERT_EQUAL_UINT32(1, aCollection.actualNumberOfChannels);        // battery is always present, all other sensors are not being detected as I2C is not being mocked
// }


int main(int argc, char **argv) {
    UNITY_BEGIN();
//    RUN_TEST(test_sensorCollection_initalize);
    UNITY_END();
}
