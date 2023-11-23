#include "datarate.h"

const dataRate dataRates::theDataRates[dataRates::nmbrUsedDataRates]{
    {spreadingFactor::SF12, bandwidth::b125kHz, 51},
    {spreadingFactor::SF11, bandwidth::b125kHz, 51},
    {spreadingFactor::SF10, bandwidth::b125kHz, 51},
    {spreadingFactor::SF9, bandwidth::b125kHz, 115},
    {spreadingFactor::SF8, bandwidth::b125kHz, 242},
    {spreadingFactor::SF7, bandwidth::b125kHz, 242},
};

uint32_t dataRates::getDownlinkDataRateIndex(uint32_t uplinkDataRateIndex, uint32_t Rx1DataRateOffset) {
    if (uplinkDataRateIndex > Rx1DataRateOffset) {
        return uplinkDataRateIndex - Rx1DataRateOffset;
    }
    return 0;
}
