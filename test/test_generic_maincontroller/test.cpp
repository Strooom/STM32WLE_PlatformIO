#include <unity.h>
#include "maincontroller.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_initialize() {
    mainController::initialize();
    TEST_ASSERT_EQUAL(mainState::boot, mainController::theMainState);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_initialize);
    UNITY_END();
}