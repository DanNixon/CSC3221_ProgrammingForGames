#include <cxxtest/TestSuite.h>

#include "Circle.h"

class CircleTest : public CxxTest::TestSuite
{
public:
  void test_Create(void)
  {
    Circle c;

    TS_ASSERT_EQUALS(c.getRadius(), 0.0);
    TS_ASSERT_EQUALS(c.getPosition(), Vector2D(0.0, 0.0));
  }
};
