#include <cxxtest/TestSuite.h>

#include "Vector3DStack.h"

class Vector3DStackTest : public CxxTest::TestSuite
{
public:
  void test_Default(void)
  {
    Vector3DStack v;
    TS_ASSERT_EQUALS(v.getX(), 0);
    TS_ASSERT_EQUALS(v.getY(), 0);
    TS_ASSERT_EQUALS(v.getZ(), 0);
  }

  void test_CreateWithValues(void)
  {
    Vector3DStack v(1, 6, 3);
    TS_ASSERT_EQUALS(v.getX(), 1);
    TS_ASSERT_EQUALS(v.getY(), 6);
    TS_ASSERT_EQUALS(v.getZ(), 3);
  }
};
