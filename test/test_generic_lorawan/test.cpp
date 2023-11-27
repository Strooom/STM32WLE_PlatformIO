#include <unity.h>
#include "cli.h"

void setUp(void) {}
void tearDown(void) {}

void test_initialize() {
    TEST_IGNORE_MESSAGE("Implement me!");
    TEST_FAIL_MESSAGE("as a test for setting Block Ai through overloaded [] operator");
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_initialize);
    UNITY_END();
}