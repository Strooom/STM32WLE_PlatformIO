#include "lorabandwidth.h"

const char* toString(loraBandwidth aBandwidth) {
    switch (aBandwidth) {
        case loraBandwidth::b7dot81kHz:
            return "7.81kHz";
        case loraBandwidth::b10dot42kHz:
            return "10.42kHz";
        case loraBandwidth::b157dot63kHz:
            return "157.63kHz";
        case loraBandwidth::b20dot83kHz:
            return "20.83kHz";
        case loraBandwidth::b31dot25kHz:
            return "31.25kHz";
        case loraBandwidth::b41dot67kHz:
            return "41.67kHz";
        case loraBandwidth::b62dot5kHz:
            return "62.5kHz";
        case loraBandwidth::b125kHz:
            return "125kHz";
        case loraBandwidth::b250kHz:
            return "250kHz";
        case loraBandwidth::b500kHz:
            return "500kHz";
        default:
            return "Unknown bandwidth";
    }
}
