#ifndef TEST_H
#define TEST_H

#define CHECK_EQUAL(expected, value) \
    TestCheckEqualSignedIntegers(expected, value, __FUNCTION__, __FILE__, __LINE__)
#define CHECK_EQUAL_UNSIGNEDS(expected, value) \
    TestCheckEqualUnsignedIntegers(expected, value, __FUNCTION__, __FILE__, __LINE__)
#define CHECK_EQUAL_STRINGS(expected, value) \
    TestCheckEqualStrings(expected, value, __FUNCTION__, __FILE__, __LINE__)

#define DEFINE_TEST_CASE(testCaseName) \
    void testCaseName##TestCase()
#define TEST_CASE(testCaseName) \
    { \
        .name = #testCaseName, \
        .function = testCaseName##TestCase \
    }

#define DEFINE_TEST_SUITE(testSuiteName, ...) \
    static TEST_CASE_INFO testSuiteName##TestCases[] = {__VA_ARGS__}; \
    static TEST_SUITE_INFO testSuiteName##TestSuite = \
    { \
        .name = #testSuiteName, \
        .testCases = testSuiteName##TestCases, \
        .testCasesCount = sizeof(testSuiteName##TestCases) / sizeof(TEST_CASE_INFO) \
    }
#define TEST_SUITE(testSuiteName) \
    testSuiteName##TestSuite

#define RUN_TEST_SUITES(...) \
    TEST_SUITE_INFO testSuites[] = {__VA_ARGS__}; \
    RunTestSuites(testSuites, sizeof(testSuites) / sizeof(TEST_SUITE_INFO))

#define ERRORS_COUNT GetTestErrorsCount()
    
typedef void (* TEST_CASE_FUNCTION)();
typedef struct
{
    const char *name;
    const TEST_CASE_FUNCTION function;
} TEST_CASE_INFO;
typedef struct
{
    const char *name;
    const TEST_CASE_INFO *testCases;
    unsigned int testCasesCount;
} TEST_SUITE_INFO;

void TestCheckEqualSignedIntegers(int expected, int value, const char *function,
                                  const char *fileName, unsigned int line);
void TestCheckEqualUnsignedIntegers(unsigned int expected, unsigned int value, const char *function,
                                    const char *fileName, unsigned int line);
void TestCheckEqualStrings(const char *expected, const char *value, const char *function,
                           const char *fileName, unsigned int line);
void RunTestSuites(const TEST_SUITE_INFO *testSuites, unsigned int testSuitesCount);
unsigned int GetTestErrorsCount();

#endif
