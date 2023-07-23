#include <unity.h>
#include "aes.h"

// https://www.cryptool.org/en/cto/aes-step-by-step
// https://braincoke.fr/blog/2020/08/the-aes-key-schedule-explained/

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

// Tests the correct mapping of a 16 byte vector to a 4x4 matrix in the way AES State expects it, on both directions
void testMatrixToVectorToMatrix() {
    uint8_t vectorIn[16]{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    uint8_t matrixOut[4][4];
    aes::vectorToMatrix(vectorIn, matrixOut);
    TEST_ASSERT_EQUAL_UINT8(0x00, matrixOut[0][0]);
    TEST_ASSERT_EQUAL_UINT8(0x01, matrixOut[1][0]);
    TEST_ASSERT_EQUAL_UINT8(0x02, matrixOut[2][0]);
    TEST_ASSERT_EQUAL_UINT8(0x03, matrixOut[3][0]);

    TEST_ASSERT_EQUAL_UINT8(0x04, matrixOut[0][1]);
    TEST_ASSERT_EQUAL_UINT8(0x05, matrixOut[1][1]);
    TEST_ASSERT_EQUAL_UINT8(0x06, matrixOut[2][1]);
    TEST_ASSERT_EQUAL_UINT8(0x07, matrixOut[3][1]);

    TEST_ASSERT_EQUAL_UINT8(0x08, matrixOut[0][2]);
    TEST_ASSERT_EQUAL_UINT8(0x09, matrixOut[1][2]);
    TEST_ASSERT_EQUAL_UINT8(0x0A, matrixOut[2][2]);
    TEST_ASSERT_EQUAL_UINT8(0x0B, matrixOut[3][2]);

    TEST_ASSERT_EQUAL_UINT8(0x0C, matrixOut[0][3]);
    TEST_ASSERT_EQUAL_UINT8(0x0D, matrixOut[1][3]);
    TEST_ASSERT_EQUAL_UINT8(0x0E, matrixOut[2][3]);
    TEST_ASSERT_EQUAL_UINT8(0x0F, matrixOut[3][3]);

    uint8_t vectorOut[16];
    aes::matrixToVector(matrixOut, vectorOut);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(vectorIn, vectorOut, 16);
}

void testBytesToWordsToBytes() {
    uint8_t bytesIn[16]{0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00};
    uint32_t wordsOut[4];
    aes::bytesToWords(bytesIn, wordsOut);
    TEST_ASSERT_EQUAL_UINT32(0xFFEEDDCC, wordsOut[0]);
    TEST_ASSERT_EQUAL_UINT32(0xBBAA9988, wordsOut[1]);
    TEST_ASSERT_EQUAL_UINT32(0x77665544, wordsOut[2]);
    TEST_ASSERT_EQUAL_UINT32(0x33221100, wordsOut[3]);

    uint8_t bytesOut[16];
    aes::wordsToBytes(wordsOut, bytesOut);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(bytesIn, bytesOut, 16);
}

// Tests the basic operations in AES : substituteByte, shiftRows, mixColumns, addRoundKey
void test_substituteByte() {
    TEST_ASSERT_EQUAL(0x63, aes::substituteByte(0x00));
    TEST_ASSERT_EQUAL(0x7C, aes::substituteByte(0x01));

    TEST_ASSERT_EQUAL(0xBB, aes::substituteByte(0xFE));
    TEST_ASSERT_EQUAL(0x16, aes::substituteByte(0xFF));
}

void test_shiftRows() {
    uint8_t inputState[4][4];
    for (auto row = 0; row < 4; row++) {
        for (auto col = 0; col < 4; col++) {
            inputState[row][col] = (row * 4) + col;
        }
    }
    aes::shiftRows2(inputState);
    // First row is unchanged
    TEST_ASSERT_EQUAL_UINT8(0, inputState[0][0]);
    TEST_ASSERT_EQUAL_UINT8(1, inputState[0][1]);
    TEST_ASSERT_EQUAL_UINT8(2, inputState[0][2]);
    TEST_ASSERT_EQUAL_UINT8(3, inputState[0][3]);
    // Second row is shifted left by 1
    TEST_ASSERT_EQUAL_UINT8(5, inputState[1][0]);
    TEST_ASSERT_EQUAL_UINT8(6, inputState[1][1]);
    TEST_ASSERT_EQUAL_UINT8(7, inputState[1][2]);
    TEST_ASSERT_EQUAL_UINT8(4, inputState[1][3]);
    // Third row is shifted left by 2
    TEST_ASSERT_EQUAL_UINT8(10, inputState[2][0]);
    TEST_ASSERT_EQUAL_UINT8(11, inputState[2][1]);
    TEST_ASSERT_EQUAL_UINT8(8, inputState[2][2]);
    TEST_ASSERT_EQUAL_UINT8(9, inputState[2][3]);
    // Fourth row is shifted left by 3
    TEST_ASSERT_EQUAL_UINT8(15, inputState[3][0]);
    TEST_ASSERT_EQUAL_UINT8(12, inputState[3][1]);
    TEST_ASSERT_EQUAL_UINT8(13, inputState[3][2]);
    TEST_ASSERT_EQUAL_UINT8(14, inputState[3][3]);
}

void test_mixColumns() {
    uint8_t inputState[4][4]{};
    inputState[0][0] = 0xdb;
    inputState[1][0] = 0x13;
    inputState[2][0] = 0x53;
    inputState[3][0] = 0x45;

    aes::mixColumns(inputState);

    TEST_ASSERT_EQUAL_UINT8(0x8e, inputState[0][0]);
    TEST_ASSERT_EQUAL_UINT8(0x4d, inputState[1][0]);
    TEST_ASSERT_EQUAL_UINT8(0xa1, inputState[2][0]);
    TEST_ASSERT_EQUAL_UINT8(0xbc, inputState[3][0]);
}

void test_addRoundKey() {
    uint8_t key[16]{00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0};
    uint8_t stateOut[4][4];
    aes::vectorToMatrix(key, stateOut);
    uint8_t stateIn[4][4]{};
    aes::addRoundKey(key, stateIn);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(stateIn, stateOut, 16);
}

void test_expandKey() {
    uint8_t theKey[16]{00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0};
    aes::expandKey(theKey);

    uint8_t expectedKey1[16]{0x71, 0xf1, 0xac, 0x8a, 0x31, 0xa1, 0xcc, 0xfa, 0xb1, 0x31, 0x6c, 0x4a, 0x71, 0xe1, 0x8c, 0xba};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedKey1, aes::roundKey + 16, 16);

    uint8_t expectedKey2[16]{0x8b, 0x95, 0x58, 0x29, 0xba, 0x34, 0x94, 0xd3, 0x0b, 0x05, 0xf8, 0x99, 0x7a, 0xe4, 0x74, 0x23};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedKey2, aes::roundKey + 32, 16);

    uint8_t expectedKey3[16]{0xe6, 0x07, 0x7e, 0xf3, 0x5c, 0x33, 0xea, 0x20, 0x57, 0x36, 0x12, 0xb9, 0x2d, 0xd2, 0x66, 0x9a};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedKey3, aes::roundKey + 48, 16);

    uint8_t expectedKey10[16]{0x78, 0x88, 0x5b, 0xc3, 0x40, 0x35, 0xca, 0x08, 0x7d, 0xec, 0xe5, 0x27, 0xec, 0x21, 0x52, 0xf3};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedKey10, aes::roundKey + 160, 16);
}

// Tests the implementation of the AES algorithm step by step for round 1
// Follow along on https://www.cryptool.org/en/cto/aes-step-by-step
void test_encrypt_step_by_step() {
    uint8_t theKey[16]{00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0};
    aes::expandKey(theKey);
    uint8_t theInput[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    uint8_t theOutput[16];
    uint8_t theState[4][4];
    aes::vectorToMatrix(theInput, theState);
    aes::XOR(theState, theKey);
    aes::matrixToVector(theState, theOutput);
    uint8_t expected1[16]{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected1, theOutput, 16);

    aes::substituteBytes(theState);
    uint8_t expected2[16]{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76};
    aes::matrixToVector(theState, theOutput);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected2, theOutput, 16);

    aes::shiftRows2(theState);
    uint8_t expected3[16]{0x63, 0x6b, 0x67, 0x76, 0xf2, 0x01, 0xab, 0x7b, 0x30, 0xd7, 0x77, 0xc5, 0xfe, 0x7c, 0x6f, 0x2b};
    aes::matrixToVector(theState, theOutput);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected3, theOutput, 16);

    aes::mixColumns(theState);
    uint8_t expected4[16]{0x6a, 0x6a, 0x5c, 0x45, 0x2c, 0x6d, 0x33, 0x51, 0xb0, 0xd9, 0x5d, 0x61, 0x27, 0x9c, 0x21, 0x5c};
    aes::matrixToVector(theState, theOutput);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected4, theOutput, 16);

    uint8_t expectedKey1[16]{0x71, 0xf1, 0xac, 0x8a, 0x31, 0xa1, 0xcc, 0xfa, 0xb1, 0x31, 0x6c, 0x4a, 0x71, 0xe1, 0x8c, 0xba};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedKey1, aes::roundKey + 16, 16);

    aes::addRoundKey(aes::roundKey + 16, theState);
    uint8_t expected5[16]{0x1b, 0x9b, 0xf0, 0xcf, 0x1d, 0xcc, 0xff, 0xab, 0x01, 0xe8, 0x31, 0x2b, 0x56, 0x7d, 0xad, 0xe6};
    aes::matrixToVector(theState, theOutput);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected5, theOutput, 16);
}

// Tests the full encryption of a block
// Using testvectors from https://csrc.nist.gov/projects/cryptographic-algorithm-validation-program/block-ciphers#AES
void test_encryptBlock() {
    uint8_t theKey[16]{0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
    uint8_t clearText[16]{0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96, 0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A};
    aes::encrypt(clearText, theKey);
    uint8_t expectedCypherText[16]{0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedCypherText, clearText, 16);
}

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

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(testMatrixToVectorToMatrix);
    RUN_TEST(testBytesToWordsToBytes);

    RUN_TEST(test_substituteByte);
    RUN_TEST(test_shiftRows);
    RUN_TEST(test_mixColumns);
    RUN_TEST(test_addRoundKey);
    RUN_TEST(test_expandKey);

    RUN_TEST(test_encrypt_step_by_step);
    RUN_TEST(test_encryptBlock);

    RUN_TEST(test_initialize);
    RUN_TEST(test_setFromBytes);
    UNITY_END();
}