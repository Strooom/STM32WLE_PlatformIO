#include <unity.h>
#include "nvs.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_write_read_bytes() {
    uint32_t testAddress{0};
    const uint32_t testDataLength{16};
    uint8_t testBytesToWrite[testDataLength]{0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    uint8_t testBytesToRead[testDataLength]{};

    nonVolatileStorage::write(testAddress, testBytesToWrite, testDataLength);
    nonVolatileStorage::read(testAddress, testBytesToRead, testDataLength);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(testBytesToWrite, testBytesToRead, testDataLength);
}

void test_erase() {
    const uint32_t testDataLength{nonVolatileStorage::size};
    uint8_t testBytesToRead[testDataLength]{};
    uint8_t expectedBytes[testDataLength];
    for (uint32_t i = 0; i < testDataLength; i++) {
        expectedBytes[i] = 0xFF;
    }

    nonVolatileStorage::erase();
    nonVolatileStorage::read(0, testBytesToRead, testDataLength);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedBytes, testBytesToRead, testDataLength);
}

void test_write_read_block() {
    uint8_t testBytesToWrite[16]{0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    uint8_t testBytesToRead[16]{};

    uint32_t testIndex  = static_cast<uint32_t>(nvsMap::blockIndex::nvsMapVersion);        // 1 byte block
    uint32_t testLength = nvsMap::blocks[testIndex].length;
    nonVolatileStorage::erase();
    nonVolatileStorage::writeBlock(testIndex, testBytesToWrite);
    nonVolatileStorage::readBlock(testIndex, testBytesToRead);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(testBytesToWrite, testBytesToRead, testLength);

    uint8_t testValueByte{0x55};
    nonVolatileStorage::erase();
    nonVolatileStorage::writeBlock8(testIndex, testValueByte);
    TEST_ASSERT_EQUAL_UINT8(testValueByte, nonVolatileStorage::readBlock8(testIndex));

    testIndex  = static_cast<uint32_t>(nvsMap::blockIndex::uplinkFrameCounter);        // 4 byte block
    testLength = nvsMap::blocks[testIndex].length;
    nonVolatileStorage::erase();
    nonVolatileStorage::writeBlock(testIndex, testBytesToWrite);
    nonVolatileStorage::readBlock(testIndex, testBytesToRead);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(testBytesToWrite, testBytesToRead, testLength);

    uint32_t testValueDoubleWord{0x55AA00FF};
    nonVolatileStorage::erase();
    nonVolatileStorage::writeBlock32(testIndex, testValueDoubleWord);
    TEST_ASSERT_EQUAL_UINT32(testValueDoubleWord, nonVolatileStorage::readBlock32(testIndex));

    nonVolatileStorage::erase();
    nonVolatileStorage::writeBlock32b(testIndex, testValueDoubleWord);
    TEST_ASSERT_EQUAL_UINT32(testValueDoubleWord, nonVolatileStorage::readBlock32b(testIndex));

    testIndex  = static_cast<uint32_t>(nvsMap::blockIndex::applicationSessionKey);        // 16 byte block
    testLength = nvsMap::blocks[testIndex].length;
    nonVolatileStorage::erase();
    nonVolatileStorage::writeBlock(testIndex, testBytesToWrite);
    nonVolatileStorage::readBlock(testIndex, testBytesToRead);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(testBytesToWrite, testBytesToRead, testLength);
}

void test_write_read_block_b() {
    uint8_t testBytesToWrite[16]{0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    uint8_t testBytesToRead[16]{};

    uint32_t testIndex  = static_cast<uint32_t>(nvsMap::blockIndex::uplinkFrameCounter);        // 4 byte block
    uint32_t testLength = nvsMap::blocks[testIndex].length;
    uint32_t testValueDoubleWord{0x01020304};

    nonVolatileStorage::erase();
    nonVolatileStorage::writeBlock32(testIndex, testValueDoubleWord);
    TEST_ASSERT_EQUAL_UINT32(testValueDoubleWord, nonVolatileStorage::readBlock32b(testIndex));

    nonVolatileStorage::erase();
    nonVolatileStorage::writeBlock32b(testIndex, testValueDoubleWord);
    TEST_ASSERT_EQUAL_UINT32(testValueDoubleWord, nonVolatileStorage::readBlock32(testIndex));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_write_read_bytes);
    RUN_TEST(test_erase);
    RUN_TEST(test_write_read_block);
    // RUN_TEST(test_write_read_block_b);
    UNITY_END();
}