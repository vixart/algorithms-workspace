// Single translation unit that provides main() for the doctest test runner.
// Every subproject's *_test.cpp is compiled and linked together with this file,
// so individual test files only need to `#include "doctest.h"` (no main()).
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
