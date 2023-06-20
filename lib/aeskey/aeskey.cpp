#include "aeskey.h"
#include <cstring>        // needed for memcpy()

const uint8_t* aesKey::asBytes() {
    return key.asByte;
}

const uint32_t* aesKey::asWords() {
    return key.asWord;
}

void aesKey::set(uint8_t bytes[lengthAsBytes]) {
    memcpy(key.asByte, bytes, lengthAsBytes);
}

