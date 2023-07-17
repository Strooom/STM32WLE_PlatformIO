#include <unity.h>
#include "hexascii.h"
#include "aeskey.h"
#include "aesblock.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

void test_initialize() {
    aesBlock aBlock;
    uint8_t expectedBytes[aesBlock::lengthAsBytes]{};
    uint32_t expectedWords[aesBlock::lengthAsWords]{};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedBytes, aBlock.asBytes(), aesBlock::lengthAsBytes);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expectedWords, aBlock.asWords(), aesBlock::lengthAsWords);
}

void test_setFromBytes() {
    aesBlock aBlock;
    uint8_t expectedBytes[aesBlock::lengthAsBytes]{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    uint32_t expectedWords[aesBlock::lengthAsWords]{0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C};
    aBlock.set(expectedBytes);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedBytes, aBlock.asBytes(), aesBlock::lengthAsBytes);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expectedWords, aBlock.asWords(), aesBlock::lengthAsWords);
}

void test_encryptBlock() {
    aesKey theKey;
    const char keyAsString[] = "2B7E151628AED2A6ABF7158809CF4F3C";
    uint8_t keyAsBytes[aesKey::lengthAsBytes];
    hexAscii::hexStringToBinaryArray(keyAsString, keyAsBytes);
    theKey.set(keyAsBytes);

    aesBlock aBlock;
    const char clearTextAsString[] = "6BC1BEE22E409F96E93D7E117393172A";
    uint8_t clearTextAsBytes[aesBlock::lengthAsBytes];
    hexAscii::hexStringToBinaryArray(clearTextAsString, clearTextAsBytes);
    aBlock.set(clearTextAsBytes);

    aBlock.encrypt(theKey);

    const char expectedCypherAsString[] = "3AD77BB40D7A3660A89ECAF32466EF97";
    uint8_t expectedCypherAsBytes[aesBlock::lengthAsBytes];
    hexAscii::hexStringToBinaryArray(expectedCypherAsString, expectedCypherAsBytes);

    //TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedCypherAsBytes, aBlock.asBytes(), aesBlock::lengthAsBytes);
     TEST_IGNORE_MESSAGE("test_encryptBlock() not implemented yet");
}

// void test_encryptBlock1() {
//     aesKey theKey;
//     theKey.setFromASCII("2B7E151628AED2A6ABF7158809CF4F3C");

//     unsigned char plainText[16];
//     hexStringToBinaryArray("AE2D8A571E03AC9C9EB76FAC45AF8E51", plainText);

//     AES_Encrypt(plainText, theKey.asUnsignedChar());

//     char cipherAsHexString[33];
//     binaryArrayToHexString(plainText, 16, cipherAsHexString);

//     TEST_ASSERT_EQUAL_STRING("F5D3D58503B9699DE785895A96FDBAAF", cipherAsHexString);
// }

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_initialize);
    RUN_TEST(test_setFromBytes);
    RUN_TEST(test_encryptBlock);
    UNITY_END();
}