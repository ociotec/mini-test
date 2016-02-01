# mini-test

Minimalistic unit testing framework for C language (no dependencies).

## Build

Just include `test.h` & `test.c` in your building, the only needed system included file is `stdio.h` (`fprintf` & `strcmp`).

If you want to run this library with the given example (in `main.c`), just run `gcc`:

```
gcc main.c test.c
```

## Example of usage

The file `main.c` is just an example of usage, it's not needed at all to define your own tests.

### Defining test cases

To create a test case, just include `test.h` & define it with the macro `DEFINE_TEST_CASE`, then use `CHECK_EQUAL` macros to add checks inside the test case:

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

## Report example

The test report follows standar JUNIT format, this is an example of a test report (from the tests described in `main.c`):

```xml
```

## Licence

This library is distributed with the MIT License (MIT), please read [LICENCE](LICENCE) for further details.
