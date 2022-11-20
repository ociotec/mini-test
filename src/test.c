#include <stdio.h>
#include "test.h"

/** Report an error inside a test case.
    @param format Format text to print the expected & actual values.
    @note This macro expects these variables to exist @c errorCount, @c fileName,
    @c line, @c function, @expected, @value. */
#define REPORT_ERROR(format) \
    { \
        errorCount++; \
        fprintf(GetReportFile(), \
                "        <failure message=\"Test case check failure\">\n" \
                "            File \"%s\", line %u, on function %s\n" \
                "            Value " format " was expected instead of " format "\n" \
                "        <failure/>\n", \
                fileName, line, function, expected, value); \
    }

/** Count of errors inside the test cases. */
static unsigned int errorCount = 0;
/** File descriptor for the report file (standard output by default). */
static FILE *reportFile = NULL;

/** Returns the file descriptor for the XML report.
    @return Returns the file descriptor for the XML report. */
static FILE *GetReportFile()
{
    if (NULL == reportFile)
    {
        reportFile = stdout;
    }
    
    return reportFile;
}

/** Run & report a test case.
    @param testCase Test case to run & report. */
static void RunTestCase(const TEST_CASE_INFO *testCase)
{
    if (NULL != testCase)
    {
        /* Write test case tag. */
        fprintf(GetReportFile(), "    <testcase name=\"\%s\">\n", testCase->name);
        /* Run the test case function. */
        testCase->function();
        fprintf(GetReportFile(), "    </testcase>\n");
    }
}

/** Run & report a test suite.
    @param testSuite Test suite to run & report. */
static void RunTestSuite(const TEST_SUITE_INFO *testSuite)
{
    unsigned int test;

    if (NULL != testSuite)
    {
        /* Write test suite tag. */
        fprintf(GetReportFile(), "<testsuite name=\"\%s\">\n", testSuite->name);
        /* Loop & report all the test cases inside the test suite. */
        for (test = 0; test < testSuite->testCasesCount; test++)
        {
            RunTestCase(&(testSuite->testCases[test]));
        }
        fprintf(GetReportFile(), "</testsuite>\n");
    }
}

void TestCheckEqualSignedIntegers(int expected, int value, const char *function,
                                  const char *fileName, unsigned int line)
{
    /* Check expected against the actual value & report if not equal. */
    if (expected != value) REPORT_ERROR("%d");
}

void TestCheckEqualUnsignedIntegers(unsigned int expected, unsigned int value, const char *function,
                                    const char *fileName, unsigned int line)
{
    /* Check expected against the actual value & report if not equal. */
    if (expected != value) REPORT_ERROR("%u");
}

void TestCheckEqualStrings(const char *expected, const char *value, const char *function,
                           const char *fileName, unsigned int line)
{
    /* Check expected against the actual value & report if not equal. */
    if (0 != strcmp(expected, value)) REPORT_ERROR("\"%s\"");
}

void RunTestSuites(const TEST_SUITE_INFO *testSuites, unsigned int testSuitesCount)
{
    unsigned int suite;

    if (NULL != testSuites)
    {
        /* Write the XML report header. */
        fprintf(GetReportFile(),
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        /* Loop & report all the test suites. */
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

void CreateReportFile(const char *fileName)
{
    /* Close previous report file only if it was opened & it's not an standard one. */
    CloseReportFile();
    
    if (NULL != fileName)
    {
        /* Take care of standard output & error files. */
        if (0 == strcmp(fileName, "stdout"))
        {
            reportFile = stdout;
        }
        else if (0 == strcmp(fileName, "stderr"))
        {
            reportFile = stderr;
        }
        /* Open regular file (if not empty). */
        else if ('\0' != fileName[0])
        {
            reportFile = fopen(fileName, "w");
        }
    }
}

void CloseReportFile()
{
    if ((NULL != reportFile) && (stdout != reportFile) && (stderr != reportFile))
    {
        fclose(reportFile);
    }
}
