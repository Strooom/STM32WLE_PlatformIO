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

buildType version::theBuildType{buildType::unknown};
buildEnvironment version::theBuildEnvironment{buildEnvironment::unknown};

char version::isVersionString[maxVersionStringLength]{};

void version::setIsVersion() {
    isVersionMajor      = buildInfo::mainVersionDigit;
    isVersionMinor      = buildInfo::minorVersionDigit;
    isVersionPatch      = buildInfo::patchVersionDigit;
    theBuildType        = buildInfo::theBuildType;
    theBuildEnvironment = buildInfo::theBuildEnvironment;

    snprintf(isVersionString, maxVersionStringLength, "v%d.%d.%d", isVersionMajor, isVersionMinor, isVersionPatch);
}



