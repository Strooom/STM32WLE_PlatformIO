#include <unity.h>
#include "circularbuffer.h"
#include "applicationevent.h"
#include "maincontroller.h"

circularBuffer<applicationEvent, 16U> applicationEventBuffer;

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_initialize() {
    mainController::initialize();
    TEST_ASSERT_EQUAL(mainState::boot, mainController::theMainState);
}

void test_toString() {
    // for test coverage only
    TEST_ASSERT_EQUAL_STRING("boot", toString(mainState::boot));
    TEST_ASSERT_EQUAL_STRING("sampling", toString(mainState::sampling));
    TEST_ASSERT_EQUAL_STRING("storing", toString(mainState::storing));
    TEST_ASSERT_EQUAL_STRING("sending", toString(mainState::sending));
    TEST_ASSERT_EQUAL_STRING("sleeping", toString(mainState::sleeping));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_initialize);
    RUN_TEST(test_toString);
    UNITY_END();
}