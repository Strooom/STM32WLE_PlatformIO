// #############################################################################
// ### This file is part of the source code for the MuMo project             ###
// ### https://github.com/Strooom/MuMo-v2-Node-SW                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################

#pragma once
#include <stdint.h>
#include "aeskey.h"
#include "aesblock.h"

// Notes : 
// expandKey only use for testing fttb, encrypt uses calculateRoundKey instead
// shoftrows is not being used fttb, shiftrows2 is used instead


class aes {
  public:
    static void encrypt(uint8_t data[16], uint8_t key[16]);

#ifndef unitTesting

  private:
#endif
    static const uint8_t sBox[256];
    static const uint8_t roundConstant[11];
    static uint8_t roundKey[176];

    static void matrixToVector(uint8_t matrixIn[4][4], uint8_t vectorOut[16]);
    static void vectorToMatrix(uint8_t vectorIn[16], uint8_t matrixOut[4][4]);
    static void bytesToWords(uint8_t bytesIn[16], uint32_t wordsOut[4]);
    static void wordsToBytes(uint32_t wordsIn[4], uint8_t bytesOut[16]);

    static void expandKey(uint8_t theKey[16]);

    static uint8_t substituteByte(const uint8_t theByte);
    static void substituteBytes(uint8_t State[4][4]);
    static void XOR(uint8_t State[4][4], uint8_t theKey[16]);
    static void addRoundKey(uint8_t *Round_Key, uint8_t State[4][4]);
    static void shiftRows(uint8_t state[4][4]);
    static void shiftRows2(uint8_t state[4][4]);
    static void mixColumns(uint8_t state[4][4]);
    static void calculateRoundKey(int Round, uint8_t theKey[16]);
    
};
