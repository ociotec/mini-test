#include <stdio.h>
#include "test.h"

DEFINE_TEST_CASE(AddPositives)
{
    CHECK_EQUAL(-4, 1 - 5);
    CHECK_EQUAL(4, 5 + 3);
    CHECK_EQUAL_UNSIGNEDS(4, 7 + 23);
}

DEFINE_TEST_CASE(AddNegatives)
{
    CHECK_EQUAL(-4, 5 - 2);
}

DEFINE_TEST_SUITE(Calculator, TEST_CASE(AddPositives), TEST_CASE(AddNegatives));

DEFINE_TEST_CASE(CompareTexts)
{
    CHECK_EQUAL_STRINGS("Text 1", "Other text");
}

DEFINE_TEST_SUITE(Dummy, TEST_CASE(CompareTexts));

int main(int argc, char **argv)
{
    RUN_TEST_SUITES(TEST_SUITE(Calculator), TEST_SUITE(Dummy));

    return ERRORS_COUNT;
}
