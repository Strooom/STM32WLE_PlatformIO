#include <unity.h>
#include "power.h"
#include "channelcollection.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_dummy_for_coverage() {
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_dummy_for_coverage);
    UNITY_END();
}
