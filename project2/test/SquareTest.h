#include <cxxtest/TestSuite.h>

#include "Square.h"

class SquareTest : public CxxTest::TestSuite
{
public:
  void test_Create(void)
  {
    Square s;

    TS_ASSERT_EQUALS(s.getWidth(), 0.0);
    TS_ASSERT_EQUALS(s.getHeight(), 0.0);
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(0.0, 0.0));
  }
};
