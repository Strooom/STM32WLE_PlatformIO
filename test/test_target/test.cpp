#include <unity.h>
#include "aes.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test


void test_encrypt() {
    TEST_IGNORE_MESSAGE("Implement me!");
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_encrypt);
    UNITY_END();
}