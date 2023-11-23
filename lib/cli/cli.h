// #############################################################################
// ### This file is part of the source code for the MuMo project             ###
// ### https://github.com/Strooom/MuMo-v2-Node-SW                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################

#pragma once
#include <stdint.h>
#include "circularbuffer.h"


class cli {
  public:
    void handleRxEvent();
    void handleEvents();

  private:
    static constexpr uint32_t commandBufferLength{256};
    static constexpr uint32_t responseBufferLength{256};

    circularBuffer<uint8_t, commandBufferLength> commandBuffer;
    circularBuffer<uint8_t, responseBufferLength> responseBuffer;
};
