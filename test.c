#include <stdio.h>
#include "test.h"

#define REPORT_FILE stdout
#define REPORT_ERROR(format) \
    { \
        errorCount++; \
        fprintf(REPORT_FILE, \
                "        <failure message=\"Test case check failure\">\n" \
                "            File \"%s\", line %u, on function %s\n" \
                "            Value " format " was expected instead of " format "\n" \
                "        <failure/>\n", \
                fileName, line, function, expected, value); \
    }
#define COMPARE_SIMPLE_AND_REPORT(format) \
    if (expected != value) REPORT_ERROR(format)

static unsigned int errorCount = 0;

void TestCheckEqualSignedIntegers(int expected, int value, const char *function,
                                  const char *fileName, unsigned int line)
{
    if (expected != value) REPORT_ERROR("%d");
}

void TestCheckEqualUnsignedIntegers(unsigned int expected, unsigned int value, const char *function,
                                    const char *fileName, unsigned int line)
{
    if (expected != value) REPORT_ERROR("%u");
}

void TestCheckEqualStrings(const char *expected, const char *value, const char *function,
                           const char *fileName, unsigned int line)
{
    if (0 != strcmp(expected, value)) REPORT_ERROR("\"%s\"");
}

static void RunTestCase(const TEST_CASE_INFO *testCase)
{
    if (NULL != testCase)
    {
        fprintf(REPORT_FILE, "    <testcase name=\%s\">\n", testCase->name);
        testCase->function();
        fprintf(REPORT_FILE, "    </testcase>\n");
    }
}

static void RunTestSuite(const TEST_SUITE_INFO *testSuite)
{
    unsigned int test;

    if (NULL != testSuite)
    {
        fprintf(REPORT_FILE, "<testsuite name=\%s\">\n", testSuite->name);
        for (test = 0; test < testSuite->testCasesCount; test++)
        {
            RunTestCase(&(testSuite->testCases[test]));
        }
        fprintf(REPORT_FILE, "</testsuite>\n");
    }
}

void RunTestSuites(const TEST_SUITE_INFO *testSuites, unsigned int testSuitesCount)
{
    unsigned int suite;

    if (NULL != testSuites)
    {
        fprintf(REPORT_FILE,
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        for (suite = 0; suite < testSuitesCount; suite++)
        {
            RunTestSuite(&(testSuites[suite]));
        }
    }
}

unsigned int GetTestErrorsCount()
{
    return errorCount;
}
