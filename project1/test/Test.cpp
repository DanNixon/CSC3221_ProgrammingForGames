#include <cstdlib>
#include <iostream>

#include "Vector3DStack.h"
#include "Quaternion.h"

#define TH 0.0001

size_t g_testsCount = 0;
size_t g_testsPassed = 0;

// Macro for testing that two values are equal to each other.
#define TS_ASSERT_EQUALS(a, b)                                                 \
  {                                                                            \
    g_testsCount++;                                                            \
    if (a == b)                                                                \
      g_testsPassed++;                                                         \
  }

// Macro for testing that two values are not equal to each other.
#define TS_ASSERT_DIFFERS(a, b)                                                \
  {                                                                            \
    g_testsCount++;                                                            \
    if (!(a == b))                                                             \
      g_testsPassed++;                                                         \
  }

// Macro for testing two numerical values are close to each other within a
// tolerance.
#define TS_ASSERT_DELTA(a, b, th)                                              \
  {                                                                            \
    g_testsCount++;                                                            \
    if (abs(a - b) <= th)                                                      \
      g_testsPassed++;                                                         \
  }

// TODO: Test functions

int main()
{
  // TODO: Test function calls
  TS_ASSERT_EQUALS(true, true);
  TS_ASSERT_EQUALS(true, true);
  TS_ASSERT_EQUALS(true, false);

  // Output the test results
  std::cout << "Tests passed: " << g_testsPassed << "/" << g_testsCount << " ("
            << ((100 * g_testsPassed) / g_testsCount) << "%)" << std::endl;

  // Return 0 for no failed tests, or 1 if at least one test failed
  return (g_testsPassed != g_testsCount);
}
