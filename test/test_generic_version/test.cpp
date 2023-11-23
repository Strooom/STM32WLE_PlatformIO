#define unitTest
#include <cstring>
#include <unity.h>
#include "version.h"
#include "buildinfo.h"

void setUp() {}
void tearDown() {}

void test_initialize() {
    // Before initialization values...
    TEST_ASSERT_EQUAL_UINT8(0, version::isVersionMajor);
    TEST_ASSERT_EQUAL_UINT8(0, version::isVersionMinor);
    TEST_ASSERT_EQUAL_UINT8(0, version::isVersionPatch);
    TEST_ASSERT_EQUAL_UINT8(0, version::toBeVersionMajor);
    TEST_ASSERT_EQUAL_UINT8(0, version::toBeVersionMinor);
    TEST_ASSERT_EQUAL_UINT8(0, version::toBeVersionPatch);
    TEST_ASSERT_EQUAL(buildType::unknown, version::theBuildType);
    TEST_ASSERT_EQUAL(buildEnvironment::unknown, version::theBuildEnvironment);
    TEST_ASSERT_EQUAL_STRING("", version::isVersionString);
    TEST_ASSERT_EQUAL_STRING("", version::toBeVersionString);

    version::setIsVersion();
    // After initialization values...
    TEST_ASSERT_EQUAL_UINT8(buildInfo::mainVersionDigit, version::isVersionMajor);
    TEST_ASSERT_EQUAL_UINT8(buildInfo::minorVersionDigit, version::isVersionMinor);
    TEST_ASSERT_EQUAL_UINT8(buildInfo::patchVersionDigit, version::isVersionPatch);
    TEST_ASSERT_EQUAL(buildInfo::theBuildType, version::theBuildType);
    TEST_ASSERT_EQUAL(buildInfo::theBuildEnvironment, version::theBuildEnvironment);
    TEST_ASSERT_GREATER_THAN(0, strlen(version::getIsVersionAsString()));

    version::setToBeVersionFromString("v1.2.3");
    TEST_ASSERT_GREATER_THAN(0, strlen(version::getToBeVersionAsString()));
}

void test_isVersionEqualsToBeVersion() {
    version::isVersionMajor = 1;
    version::isVersionMinor = 2;
    version::isVersionPatch = 3;

    version::toBeVersionMajor = 1;
    version::toBeVersionMinor = 2;
    version::toBeVersionPatch = 3;
    TEST_ASSERT_TRUE(version::isVersionEqualsToBeVersion());

    version::toBeVersionMajor = 4;
    version::toBeVersionMinor = 2;
    version::toBeVersionPatch = 3;
    TEST_ASSERT_FALSE(version::isVersionEqualsToBeVersion());

    version::toBeVersionMajor = 1;
    version::toBeVersionMinor = 4;
    version::toBeVersionPatch = 3;
    TEST_ASSERT_FALSE(version::isVersionEqualsToBeVersion());

    version::toBeVersionMajor = 1;
    version::toBeVersionMinor = 2;
    version::toBeVersionPatch = 4;
    TEST_ASSERT_FALSE(version::isVersionEqualsToBeVersion());
}

void test_isValidToBeVersionString() {
    TEST_ASSERT_FALSE(version::isValidToBeVersionString(nullptr));        // nullptr
    TEST_ASSERT_FALSE(version::isValidToBeVersionString(""));             // empty string
    char testString[version::maxVersionStringLength];
    memset(testString, 'A', version::maxVersionStringLength);
    memcpy(testString, "v1.2.3", 6U);
    TEST_ASSERT_FALSE(version::isValidToBeVersionString(testString));        // too long

    char testString2[version::maxVersionStringLength] = "v1.2.3";
    TEST_ASSERT_TRUE(version::isValidToBeVersionString(testString2));        // valid
}

void test_setToBeVersionFromString() {
    version::setToBeVersionFromString("v6_7_8");
    TEST_ASSERT_EQUAL_UINT8(6, version::toBeVersionMajor);
    TEST_ASSERT_EQUAL_UINT8(7, version::toBeVersionMinor);
    TEST_ASSERT_EQUAL_UINT8(8, version::toBeVersionPatch);
    TEST_ASSERT_EQUAL_STRING("v6.7.8", version::toBeVersionString);
}

void test_replaceDelimitorWithDot() {
    char testString[] = "V30_50_00_00-100-g7da1beb-PROD";
    version::replaceDelimitorWithDot(testString, '_');
    TEST_ASSERT_EQUAL_STRING("V30.50.00.00-100-g7da1beb-PROD", testString);
}

void test_stripLeadingV() {
    char testString1[] = "V30_50_00_00-100-g7da1beb-PROD";
    version::stripLeadingV(testString1);
    TEST_ASSERT_EQUAL_STRING("30_50_00_00-100-g7da1beb-PROD", testString1);
    char testString2[] = "v30_50_00_00-100-g7da1beb-PROD";
    version::stripLeadingV(testString2);
    TEST_ASSERT_EQUAL_STRING("30_50_00_00-100-g7da1beb-PROD", testString2);
    char testString3[] = "v30_50_00_00-100-g7da1beb-PROD";
    version::stripLeadingV(testString3);
    TEST_ASSERT_EQUAL_STRING("30_50_00_00-100-g7da1beb-PROD", testString3);
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(test_initialize);
    RUN_TEST(test_isVersionEqualsToBeVersion);
    RUN_TEST(test_isValidToBeVersionString);
    RUN_TEST(test_setToBeVersionFromString);
    RUN_TEST(test_replaceDelimitorWithDot);
    RUN_TEST(test_stripLeadingV);
    UNITY_END();
}