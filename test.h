#ifndef TEST_H
#define TEST_H

/** Compare two signed integer numbers and log an failure if not equal. It should be
    called inside a test case.
    @param expected Expected value.
    @param value Actual value.
    @see DEFINE_TEST_CASE */
#define CHECK_EQUAL(expected, value) \
    TestCheckEqualSignedIntegers(expected, value, __FUNCTION__, __FILE__, __LINE__)
/** Compare two unsigned integer numbers and log an failure if not equal. It should be
    called inside a test case.
    @param expected Expected value.
    @param value Actual value.
    @see DEFINE_TEST_CASE */
#define CHECK_EQUAL_UNSIGNEDS(expected, value) \
    TestCheckEqualUnsignedIntegers(expected, value, __FUNCTION__, __FILE__, __LINE__)
/** Compare two strings (case sentitive) and log an failure if not equal. It should be
    called inside a test case.
    @param expected Expected value.
    @param value Actual value.
    @see DEFINE_TEST_CASE */
#define CHECK_EQUAL_STRINGS(expected, value) \
    TestCheckEqualStrings(expected, value, __FUNCTION__, __FILE__, __LINE__)

/** Define a test case function.
    @param testCaseName Name of the test case, it's used as part of the test case
    function name, so it should follow C language identifiers rules.
    @see CHECK_EQUAL, CHECK_EQUAL_UNSIGNEDS, CHECK_EQUAL_STRINGS */
#define DEFINE_TEST_CASE(testCaseName) \
    void testCaseName##TestCase()
/** This macro creates a test case instance to be used inside a test suite definition.
    @param testCaseName Name of the test case, it's used as part of the test case
    function name, so it should follow C language identifiers rules.
    @see DEFINE_TEST_SUITE */
#define TEST_CASE(testCaseName) \
    { \
        .name = #testCaseName, \
        .function = testCaseName##TestCase \
    }

/** Define a test suite & allocates the needed variables for the test suite & its
    test cases.
    @param testSuiteName Test suite name, it's used as part of the test case
    function name, so it should follow C language identifiers rules.
    @param ... Variable list of parameters containing the list of test cases instances
    of this test suite.
    @see TEST_CASE */
#define DEFINE_TEST_SUITE(testSuiteName, ...) \
    static TEST_CASE_INFO testSuiteName##TestCases[] = {__VA_ARGS__}; \
    static TEST_SUITE_INFO testSuiteName##TestSuite = \
    { \
        .name = #testSuiteName, \
        .testCases = testSuiteName##TestCases, \
        .testCasesCount = sizeof(testSuiteName##TestCases) / sizeof(TEST_CASE_INFO) \
    }
/** This macro references to a test suite variable. It's used to reference it & run it.
    @param testSuiteName Test suite name, it's used as part of the test case
    function name, so it should follow C language identifiers rules.
    @see RUN_TEST_SUITES */
#define TEST_SUITE(testSuiteName) \
    testSuiteName##TestSuite

/** Run test suites.
    @param ... Variable list of parameters containing the list of test suites instances.
    @see TEST_SUITE, ERRORS_COUNT */
#define RUN_TEST_SUITES(...) \
    TEST_SUITE_INFO testSuites[] = {__VA_ARGS__}; \
    RunTestSuites(testSuites, sizeof(testSuites) / sizeof(TEST_SUITE_INFO))
/** Returns the count of errors of the test cases inside the test suites after run them.
    Each test case can fail several times (one per failed check).
    @see RUN_TEST_SUITES */
#define ERRORS_COUNT GetTestErrorsCount()

/** Pointer to a test case function. */    
typedef void (* TEST_CASE_FUNCTION)();
/** Test case information structure. */
typedef struct
{
    /** Test case name. */
    const char *name;
    /** Test case function. */
    const TEST_CASE_FUNCTION function;
} TEST_CASE_INFO;
/** Test suite information structure. */
typedef struct
{
    /** Test suite name. */
    const char *name;
    /** Array of test cases. */
    const TEST_CASE_INFO *testCases;
    /** Count of elements in the test cases array. */
    unsigned int testCasesCount;
} TEST_SUITE_INFO;

/** Compare two signed integer numbers and log an failure if not equal. It should be
    called inside a test case.
    @param expected Expected value.
    @param value Actual value.
    @param function Calling function name.
    @param fileName Calling file name.
    @param line Calling line of code.
    @see CHECK_EQUAL
    @warning Don't call this function, use macro instead. */
void TestCheckEqualSignedIntegers(int expected, int value, const char *function,
                                  const char *fileName, unsigned int line);
/** Compare two unsigned integer numbers and log an failure if not equal. It should be
    called inside a test case.
    @param expected Expected value.
    @param value Actual value.
    @param function Calling function name.
    @param fileName Calling file name.
    @param line Calling line of code.
    @see CHECK_EQUAL_UNSIGNEDS
    @warning Don't call this function, use macro instead. */
void TestCheckEqualUnsignedIntegers(unsigned int expected, unsigned int value, const char *function,
                                    const char *fileName, unsigned int line);
/** Compare two strings (case sentitive) and log an failure if not equal. It should be
    called inside a test case.
    @param expected Expected value.
    @param value Actual value.
    @param function Calling function name.
    @param fileName Calling file name.
    @param line Calling line of code.
    @see CHECK_EQUAL_STRINGS
    @warning Don't call this function, use macro instead. */
void TestCheckEqualStrings(const char *expected, const char *value, const char *function,
                           const char *fileName, unsigned int line);
/** Run test suites.
    @param testSuites Array of test suites instances to run.
    @param testSuitesCount Count of elements of the array of test suites.
    @see RUN_TEST_SUITES
    @warning Don't call this function, use macro instead. */
void RunTestSuites(const TEST_SUITE_INFO *testSuites, unsigned int testSuitesCount);
/** Returns the count of errors of the test cases inside the test suites after run them.
    Each test case can fail several times (one per failed check).
    @see ERRORS_COUNT
    @warning Don't call this function, use macro instead. */
unsigned int GetTestErrorsCount();

#endif
