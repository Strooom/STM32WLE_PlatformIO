#include "font.h"

bool font::isInBounds(uint8_t asciiCode) {
    return (asciiCode >= asciiStart && asciiCode <= asciiEnd);
};

uint32_t font::byteOffset(uint8_t asciiCode) const {
    if (isInBounds(asciiCode)) {
        return (asciiCode - asciiStart) * bytesPerRow * pixelHeight;
    } else {
        return 0;
    }
};
