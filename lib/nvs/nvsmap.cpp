// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#include "nvsmap.h"

// Initialize the static const block array

const nvsMap::block nvsMap::blocks[static_cast<uint32_t>(blockIndex::numberOfBlocks)] = {
    // Important note : make sure that none of the blocks are mapped into two pages of 128 Bytes, as the page-write of the EEPROM is limited to 128 Byte pages and the address will wrap around to the beginning of the page if addressing more than 128 Bytes
    {0, 1},          // nvsMapVersion : 1 byte
    {1, 1},          // displayVersion : 1 byte
    {2, 1},          // batteryVersion : 1 byte
    {3, 4},          // activelogging::sources : 4 bytes
    {7, 121},        // unusedGeneral : extra blocks can be inserted hereafter for a maximum of 121 bytes

    {128, 4},        // measurementWriteIndex : 32 bits
    {132, 4},        // oldestUnsentMeasurementIndex : 32 bits
    {136, 4},        // oldestUnconfirmedMeasurementindex : 32 bits
    // TODO add a setting to enable resending unconfirmed measurements
    {140, 116},        // unusedMeasurementDataManagement : extra blocks can be inserted hereafter for a maximum of 116 bytes

    {256, 8},          // DevEUI : 64 bits
    {264, 4},          // DevAddr : 32 bits
    {268, 4},          // uplinkFrameCounter : 32 bits
    {272, 4},          // downlinkFrameCounter : 32 bits
    {276, 16},         // applicationSessionKey : 128 bits
    {292, 16},         // networkSessionKey : 128 bits
    {308, 1},          // rx1Delay : 1 byte
    {309, 203},        // unusedLoRaWAN : extra blocks can be inserted hereafter
};

bool nvsMap::isValidBlockIndex(uint32_t blockIndex) {
    return (blockIndex < static_cast<uint32_t>(nvsMap::blockIndex::numberOfBlocks));
}
