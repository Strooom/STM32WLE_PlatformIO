// #############################################################################
// ### This file is part of the source code for the MuMo project             ###
// ### https://github.com/Strooom/MuMo-v2-Node-SW                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################

#pragma once
#include <stdint.h>
#include "aeskey.h"

class aesBlock {
  public:
    static constexpr uint32_t lengthAsBytes{16};        //
    static constexpr uint32_t lengthAsWords{4};         //
    void set(uint8_t bytes[lengthAsBytes]);             // load the block with data
    void encrypt(aesKey &key);                          // encrypt the block
    const uint8_t *asBytes();                                 // return the encrypted block as bytes
    const uint32_t *asWords();                                // return the encrypted block as words

#ifndef unitTesting
  private:
#endif
    union {
        uint8_t asByte[lengthAsBytes]{};        // interprete the data as 16 bytes
        uint32_t asWord[lengthAsWords];         // interprete the data as 4 32bit words
    } state;                                    // fancy name for data in the block
};