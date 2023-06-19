#include <unity.h>

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_one() {
    TEST_ABORT();
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_one);
    UNITY_END();
}