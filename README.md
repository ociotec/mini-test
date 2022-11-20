# mini-test

Minimalistic unit testing framework for C language (no dependencies).

## Build

Just include [`test.h`](src/test.h) & [`test.c`](src/test.h) in your building, the only needed system included file is `stdio.h` (`fprintf` & `strcmp`).

If you want to run this library with the given example (in [`main.c`](samples/main.c)), just run `gcc`:

```
gcc main.c test.c
```

## Example of usage

The file [`main.c`](samples/main.c) is just an example of usage, it's not needed at all to define your own tests.

### Defining test cases

To create a test case, just include [`test.h`](src/test.h) & define it with the macro `DEFINE_TEST_CASE`, then use `CHECK_EQUAL` macros to add checks inside the test case:

```c
DEFINE_TEST_CASE(AddNumbers)
{
  CHECK_EQUAL(12, 4 + 8);
  CHECK_EQUAL(-7, 9 - 2);
}
```

You could also compare strings or unsigned numbers:

```c
DEFINE_TEST_CASE(OtherStuff)
{
  CHECK_EQUAL_UNSIGNEDS(8, 4 + 4);
  CHECK_EQUAL_STRINGS("Hello", "Hello");
}
```

### Defining test suites

Test cases are grouped into test suites with the macro `DEFINE_TEST_SUITE`:

```c
DEFINE_TEST_SUITE(TEST_CASE(AddNumbers), TEST_CASE(OtherStuff));
```

### Runing the tests

To run the tests, just call `RUN_TEST_SUITES` macro, `ERRORS_COUNT` will return the number of test errors:

```c
int main(int argc, char **argv)
{
  RUN_TEST_SUITES(TEST_SUITE(Calculator), TEST_SUITE(Dummy));
  return ERRORS_COUNT;
}
```

### Creating the XML report in a regular file

By default the XML report will be output in the standar output, but it could be also output in the standar error or even in a regular file.

Take a look to the following examples:

```c
int main(int argc, char **argv)
{
    CREATE_REPORT("stderr");
    RUN_TEST_SUITES(TEST_SUITE(Calculator), TEST_SUITE(Dummy));

    return ERRORS_COUNT;
}
```

Call `CREATE_REPORT` to create the report with `stdout` (default if you don't call the macro), `stderr` or the file name (relative or absolute path).

```c
int main(int argc, char **argv)
{
    CREATE_REPORT("report.xml");
    RUN_TEST_SUITES(TEST_SUITE(Calculator), TEST_SUITE(Dummy));
    CLOSE_REPORT();

    return ERRORS_COUNT;
}
```

Call `CLOSE_REPORT` when you call `CREATE_REPORT` with a regular file name, to close the report file properly.

## Report example

The test report follows standar JUNIT format, [this is an example of an XML test report](samples/report.xml), from the tests described in [`main.c`](src/main.c):

```xml
<?xml version="1.0" encoding="UTF-8"?>
<testsuite name="Calculator">
  <testcase name="AddPositives">
    <failure message="Test case check failure">
      File "main.c", line 7, on function AddPositivesTestCase
      Value 4 was expected instead of 8
    <failure/>
    <failure message="Test case check failure">
      File "main.c", line 8, on function AddPositivesTestCase
      Value 4 was expected instead of 30
    <failure/>
  </testcase>
  <testcase name="AddNegatives">
    <failure message="Test case check failure">
      File "main.c", line 13, on function AddNegativesTestCase
      Value -4 was expected instead of 3
    <failure/>
  </testcase>
</testsuite>
<testsuite name="Dummy">
  <testcase name="CompareTexts">
    <failure message="Test case check failure">
      File "main.c", line 20, on function CompareTextsTestCase
      Value "Text 1" was expected instead of "Other text"
    <failure/>
  </testcase>
</testsuite>
```

## Licence

This library is distributed with the MIT License (MIT), please read [LICENCE](LICENCE) for further details.
