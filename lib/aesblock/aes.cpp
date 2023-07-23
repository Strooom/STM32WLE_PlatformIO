// This file contains a SW implementation of the AES algorithm.
// In the MuMo application, we use the AES hardware accelerator, but for unitTesting on the desktop, we may use this SW implementation.
#include "aes.h"
#include <cstring>
#include <stdint.h>

const uint8_t aes::sBox[256]{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16};

const uint8_t aes::roundConstant[11]{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

uint8_t aes::roundKey[176];

// Maps a 16 byte vector to a 4x4 matrix in the way AES State expects it
void aes::vectorToMatrix(uint8_t vectorIn[16], uint8_t matrixOut[4][4]) {
    for (auto row = 0; row < 4; row++) {
        for (auto col = 0; col < 4; col++) {
            matrixOut[row][col] = vectorIn[(col * 4) + row];
        }
    }
}
// Maps a 4x4 matrix to a 16 byte vector in the way AES State expects it
void aes::matrixToVector(uint8_t matrixIn[4][4], uint8_t vectorOut[16]) {
    for (auto row = 0; row < 4; row++) {
        for (auto col = 0; col < 4; col++) {
            vectorOut[(col * 4) + row] = matrixIn[row][col];
        }
    }
}

// Mapping aes keys and datablocks to bytes and 32words is a bit tricky, as indexes are confusing :
// 128bit AES Keys are shown as : "FF EE DD CC BB AA 99 88 77 66 55 44 33 22 11 00", where FF holds the Most Signiciant Digits of the number, 00 the least significant.
// When this is stored in a byte array : uint8_t keyBytes[16]{0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00};
// keyBytes[0] = 0xFF, keyBytes[0x0F] = 00 -> the Most Significant Digit is in the FIRST byte, which has the LOWEST array index, and is stored in the LOWEST memory address
// When transferring it to the AES hardware-peripheral, we need 32bit words.
// uint32_t keyWords[4]{
//     0xFFEEDDCC,
//     0xBBAA9988,
//     0x77665544,
//     0x33221100};
// Note that the bytes are expected big-endian, and so we cannot simply use the compilers conversion between uint32 and uint8[4] as this will be little-endian.
// keyWords[0] = 0xFFEEDDCC, keyWords[3] = 0x33221100

// Then when using this with the AES HW, the 4 key registers expect the following :
//   AES_KEYR3 = keyWords[0]
//   AES_KEYR2 = keyWords[1]
//   AES_KEYR1 = keyWords[2]
//   AES_KEYR0 = keyWords[3]

void aes::bytesToWords(uint8_t bytesIn[16], uint32_t wordsOut[4]) {
    for (auto i = 0; i < 4; i++) {
        wordsOut[i] = bytesIn[i * 4] << 24 | bytesIn[i * 4 + 1] << 16 | bytesIn[i * 4 + 2] << 8 | bytesIn[i * 4 + 3];
    }
}

void aes::wordsToBytes(uint32_t wordsIn[4], uint8_t bytesOut[16]) {
    for (auto i = 0; i < 4; i++) {
        bytesOut[i * 4]     = (wordsIn[i] >> 24) & 0xFF;
        bytesOut[i * 4 + 1] = (wordsIn[i] >> 16) & 0xFF;
        bytesOut[i * 4 + 2] = (wordsIn[i] >> 8) & 0xFF;
        bytesOut[i * 4 + 3] = wordsIn[i] & 0xFF;
    }
}

uint8_t aes::substituteByte(const uint8_t theByte) {
    return sBox[theByte];
}

void aes::substituteBytes(uint8_t state[4][4]) {
    for (auto column = 0; column < 4; column++) {
        for (auto row = 0; row < 4; row++) {
            state[row][column] = aes::substituteByte(state[row][column]);
        }
    }
}

void aes::XOR(uint8_t state[4][4], uint8_t theKey[16]) {
    uint8_t keyMatrix[4][4];
    aes::vectorToMatrix(theKey, keyMatrix);
    for (auto row = 0; row < 4; row++) {
        for (auto col = 0; col < 4; col++) {
            state[row][col] ^= keyMatrix[row][col];
        }
    }
}

void aes::addRoundKey(uint8_t* roundKey, uint8_t state[4][4]) {
    uint8_t row, column;
    for (column = 0; column < 4; column++) {
        for (row = 0; row < 4; row++) {
            state[row][column] ^= roundKey[row + (column << 2)];
        }
    }
}

void aes::shiftRows(uint8_t state[4][4]) {
    uint8_t tmp[4];
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tmp[j] = state[i][(j + i) % 4];
        }
        for (int j = 0; j < 4; j++) {
            state[i][j] = tmp[j];
        }
    }
}

void aes::shiftRows2(uint8_t state[4][4]) {
    uint8_t temp;

    temp        = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;
    temp        = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp        = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;
    temp        = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}

void aes::mixColumns(uint8_t state[4][4]) {
    uint8_t row, column;
    uint8_t a[4], b[4];

    for (column = 0; column < 4; column++) {
        for (row = 0; row < 4; row++) {
            a[row] = state[row][column];
            b[row] = (state[row][column] << 1);

            if ((state[row][column] & 0x80) == 0x80) {
                b[row] ^= 0x1B;
            }
        }
        state[0][column] = b[0] ^ a[1] ^ b[1] ^ a[2] ^ a[3];
        state[1][column] = a[0] ^ b[1] ^ a[2] ^ b[2] ^ a[3];
        state[2][column] = a[0] ^ a[1] ^ b[2] ^ a[3] ^ b[3];
        state[3][column] = a[0] ^ b[0] ^ a[1] ^ a[2] ^ b[3];
    }
}

void aes::expandKey(uint8_t theKey[16]) {
    // key[0] is just a copy of the inputKey
    memcpy(roundKey, theKey, 16);

    for (auto round = 1; round <= 10; round++) {
        memcpy(roundKey + (round * 16), roundKey + ((round - 1) * 16), 16);
        calculateRoundKey(round, roundKey + (round * 16));
    }
}

void aes::calculateRoundKey(int Round, uint8_t roundKey[16]) {
    uint8_t i, j, b, Rcon;
    uint8_t temp[4];

    // Calculate Rcon
    Rcon = roundConstant[Round - 1];

    //  Calculate first Temp
    //  Copy laste byte from previous key and substitute the byte, but shift the matrix contents around by 1.
    temp[0] = aes::substituteByte(roundKey[12 + 1]);
    temp[1] = aes::substituteByte(roundKey[12 + 2]);
    temp[2] = aes::substituteByte(roundKey[12 + 3]);
    temp[3] = aes::substituteByte(roundKey[12 + 0]);

    //  XOR with Rcon
    temp[0] ^= Rcon;

    //  Calculate new key
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            roundKey[j + (i << 2)] ^= temp[j];
            temp[j] = roundKey[j + (i << 2)];
        }
    }
}

void aes::encrypt(uint8_t theData[16], uint8_t theKey[16]) {
    uint8_t roundKey[16];
    uint8_t state[4][4];

    aes::vectorToMatrix(theData, state);

    memcpy(&roundKey[0], &theKey[0], 16);
    aes::addRoundKey(roundKey, state);

    for (auto round = 1; round <= 10; round++) {
        aes::substituteBytes(state);
        aes::shiftRows2(state);
        if (round < 10) {
            aes::mixColumns(state);
        }
        aes::calculateRoundKey(round, roundKey);
        aes::addRoundKey(roundKey, state);
    }

    aes::matrixToVector(state, theData);
}
