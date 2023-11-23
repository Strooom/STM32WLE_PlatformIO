#pragma once
#include "stdint.h"
#include "buildtype.h"
#include "buildenvironment.h"

class version {
  public:

    static uint8_t getIsVersionMajor() { return isVersionMajor; }
    static uint8_t getIsVersionMinor() { return isVersionMinor; }
    static uint8_t getIsVersionPatch() { return isVersionPatch; }
    static uint8_t getToBeVersionMajor() { return toBeVersionMajor; }
    static uint8_t getToBeVersionMinor() { return toBeVersionMinor; }
    static uint8_t getToBeVersionPatch() { return toBeVersionPatch; }
    static buildType getBuildType() { return theBuildType; }
    static buildEnvironment getBuildEnvironment() { return theBuildEnvironment; }
    static const char* getIsVersionAsString() { return isVersionString; }
    static const char* getToBeVersionAsString() { return toBeVersionString; }

    static bool isVersionEqualsToBeVersion();

    static void setIsVersion();
    
    static bool isValidToBeVersionString(const char* aVersion);
    static void setToBeVersionFromString(const char* aVersion);
    static void replaceDelimitorWithDot(char* theString, char theDelimitor);
    static void stripLeadingV(char* theString);

#ifndef unitTesting
  private:
#endif

    static uint8_t isVersionMajor;
    static uint8_t isVersionMinor;
    static uint8_t isVersionPatch;

    static uint8_t toBeVersionMajor;
    static uint8_t toBeVersionMinor;
    static uint8_t toBeVersionPatch;

    static buildType theBuildType;
    static buildEnvironment theBuildEnvironment;

    static constexpr uint8_t maxVersionStringLength{40U};        // maximum length of string holding the version, eg V30_50_00_00-100-g7da1beb-PROD
    static char isVersionString[maxVersionStringLength];
    static char toBeVersionString[maxVersionStringLength];
};