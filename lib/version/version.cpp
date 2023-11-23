#include "version.h"
#include <stdio.h>
#include <stdlib.h>
#include "strl.h"
#include "logging.h"
#include "buildinfo.h"

// Instantiate/initialize the static variables

uint8_t version::isVersionMajor{0};
uint8_t version::isVersionMinor{0};
uint8_t version::isVersionPatch{0};

uint8_t version::toBeVersionMajor{0};
uint8_t version::toBeVersionMinor{0};
uint8_t version::toBeVersionPatch{0};

buildType version::theBuildType{buildType::unknown};
buildEnvironment version::theBuildEnvironment{buildEnvironment::unknown};

char version::isVersionString[maxVersionStringLength]{};
char version::toBeVersionString[maxVersionStringLength]{};

void version::setIsVersion() {
    isVersionMajor      = buildInfo::mainVersionDigit;
    isVersionMinor      = buildInfo::minorVersionDigit;
    isVersionPatch      = buildInfo::patchVersionDigit;
    theBuildType        = buildInfo::theBuildType;
    theBuildEnvironment = buildInfo::theBuildEnvironment;

    snprintf(isVersionString, maxVersionStringLength, "v%d.%d.%d", isVersionMajor, isVersionMinor, isVersionPatch);
}

bool version::isVersionEqualsToBeVersion() {
    return (isVersionMajor == toBeVersionMajor) && (isVersionMinor == toBeVersionMinor) && (isVersionPatch == toBeVersionPatch);
}

// void version::setVersion(const char* aVersion) {
//     char tmpVersionString[maxVersionStringLength];
//     strlcpy(tmpVersionString, aVersion, maxVersionStringLength);        // TODO it would be better to parse the integers, then regenerate the string, so we get rid of any invalid stuff
//     stripLeadingV(tmpVersionString);
//     // replaceDelimitorWithDot(tmpVersionString, '_');

//     // int tmpMajor{0};
//     // int tmpMinor{0};
//     // int tmpBugfix{0};
//     // int tmpCandidate{0};

//     char* firstDot = strchr(tmpVersionString, '_');
//     if (firstDot != nullptr) {
//         *firstDot = 0x00;
//         // tmpMajor        = atoi(tmpVersionString);
//         char* secondDot = strchr(firstDot + 1, '_');
//         if (secondDot != nullptr) {
//             *secondDot = 0x00;
//             // tmpMinor       = atoi(firstDot + 1);
//             char* thirdDot = strchr(secondDot + 1, '_');
//             if (thirdDot != nullptr) {
//                 *thirdDot = 0x00;
//                 // tmpBugfix    = atoi(secondDot + 1);
//                 // tmpCandidate = atoi(thirdDot + 1);
//                 validversion = true;
//                 findBuildParameters(aVersion);
//             } else {
//                 // tmpBugfix = atoi(secondDot + 1);
//                 validversion = true;
//                 findBuildParameters(aVersion);
//             }
//         }
//     }
//     if (validversion) {
//         strlcpy(fullVersionString, aVersion, maxVersionStringLength);
//     }
// }

// void version::findBuildParameters(const char* aVersionString) {
//     char tmpVersionString[maxVersionStringLength];
//     strlcpy(tmpVersionString, aVersionString, maxVersionStringLength);

//     bool envFound = false;

//     // first check the build environment. The new version string should always include the environment which is a combination of the partion (MCU4M or MCU16M) and the development state (PROD, DEV, INT)
//     if (strstr(aVersionString, "PROD") != nullptr) {
//         theEnvironment = versionEnvironment::production;
//         production     = true;
//         envFound       = true;
//     } else if (strstr(aVersionString, "DEV") != nullptr) {
//         theEnvironment = versionEnvironment::development;
//         production     = false;
//         envFound       = true;
//     } else if (strstr(aVersionString, "INT")) {
//         theEnvironment = versionEnvironment::integrationtest;
//         production     = false;
//         envFound       = true;
//     } else if (strstr(aVersionString, "LOCAL") != nullptr) {
//         theEnvironment = versionEnvironment::local;
//         production     = false;
//         envFound       = true;
//     } else if (strstr(aVersionString, "FIRSTFLASH") != nullptr) {
//         theEnvironment = versionEnvironment::local;
//         production     = false;
//         envFound       = true;
//     } else {
//         theEnvironment = versionEnvironment::unknown;
//         logging::snprintf(logging::source::criticalError, "No build environment found");
//         production = false;
//         envFound   = false;
//     }

//     if (envFound) {
//         logging::snprintf(logging::source::info, "Build environment: %s", getEnvironmentString());
//     } else {
//         logging::snprintf(logging::source::info, "No build environment found");
//     }

//     bool partionFound = false;
//     if (strstr(aVersionString, "MCU4M") != nullptr) {
//         thePartitionFormat = partitionFormat::partition_4Mbyte;
//         partionFound       = true;
//     } else if (strstr(aVersionString, "MCU16M") != nullptr) {
//         thePartitionFormat = partitionFormat::partition_16Mbyte;
//         partionFound       = true;
//     }

//     if (partionFound) {
//         logging::snprintf(logging::source::info, "Partition version found: %s", getPartitionString());
//     } else {
//         logging::snprintf(logging::source::info, "No partiton version found");
//     }
// }

// const char* version::asCharPtr() const {
//     return fullVersionString;
// }

// partitionFormat version::getPartitionFormat() {
//     return thePartitionFormat;
// }

void version::setToBeVersionFromString(const char* aVersion) {
    if (!isValidToBeVersionString(aVersion)) {
        logging::snprintf(logging::source::criticalError, "Invalid version string: %s", aVersion);
        return;
    }

    char tmpVersionString[maxVersionStringLength];
    strlcpy(tmpVersionString, aVersion, maxVersionStringLength);

    stripLeadingV(tmpVersionString);

    char* firstSeparator = strchr(tmpVersionString, '_');
    if (firstSeparator != nullptr) {
        *firstSeparator       = 0x00;
        toBeVersionMajor      = atoi(tmpVersionString);
        char* secondSeparator = strchr(firstSeparator + 1, '_');
        if (secondSeparator != nullptr) {
            *secondSeparator = 0x00;
            toBeVersionMinor = atoi(firstSeparator + 1);
            toBeVersionPatch = atoi(secondSeparator + 1);
        }
    }
    snprintf(toBeVersionString, maxVersionStringLength, "v%d.%d.%d", toBeVersionMajor, toBeVersionMinor, toBeVersionPatch);
}

void version::replaceDelimitorWithDot(char* theString, char theDelimitor) {
    for (uint32_t index = 0; index < maxVersionStringLength; index++) {
        if (theString[index] == 0) {
            return;
        }
        if (theString[index] == theDelimitor) {
            theString[index] = '.';
        }
    }
}

void version::stripLeadingV(char* theString) {
    if ((theString[0] == 'V') || (theString[0] == 'v')) {
        for (uint32_t index = 0; index < maxVersionStringLength; index++) {
            theString[index] = theString[index + 1];
            if (theString[index] == 0) {
                return;
            }
        }
        theString[maxVersionStringLength - 1] = 0;
    }
}

bool version::isValidToBeVersionString(const char* aString) {
    if (aString == nullptr) {
        return false;
    }
    uint32_t aStringLength = strnlen(aString, maxVersionStringLength);
    if (aStringLength == 0) {
        return false;
    }
    if (aStringLength >= maxVersionStringLength) {
        return false;
    }
    char firstChar = aString[0];
    if (firstChar < '0' || firstChar > '9') {
        if ((firstChar != 'V') &&
            (firstChar != 'v')) {
            return false;
        }
    }
    // TODO : we should check the actual presence of 3 digits and a separator

    return true;
}
