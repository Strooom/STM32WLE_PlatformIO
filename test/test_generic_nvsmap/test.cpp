#include <unity.h>
#include "nvsmap.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_isValidBlockIndex() {
    TEST_ASSERT_TRUE(nvsMap::isValidBlockIndex(0));
    TEST_ASSERT_TRUE(nvsMap::isValidBlockIndex(static_cast<uint32_t>(nvsMap::blockIndex::numberOfBlocks) - 1));
    TEST_ASSERT_FALSE(nvsMap::isValidBlockIndex(static_cast<uint32_t>(nvsMap::blockIndex::numberOfBlocks)));
}

void test_blockOverlap() {
    for (uint32_t index = 0; index < (static_cast<uint32_t>(nvsMap::blockIndex::numberOfBlocks) - 1); index++) {
        TEST_ASSERT_EQUAL_UINT32(nvsMap::blocks[index].startAddress + nvsMap::blocks[index].length, nvsMap::blocks[index + 1].startAddress);
    }
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_isValidBlockIndex);
    RUN_TEST(test_blockOverlap);
    UNITY_END();
}