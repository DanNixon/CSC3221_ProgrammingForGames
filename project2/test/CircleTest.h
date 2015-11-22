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

  void test_CreateGivenSize(void)
  {
    Circle c(10.0);

    TS_ASSERT_EQUALS(c.getRadius(), 10.0);
    TS_ASSERT_EQUALS(c.getPosition(), Vector2D(0.0, 0.0));
  }

  void test_CreateCopy(void)
  {
    Circle c1(10.0);
    c1.setPosition(Vector2D(30.0, 50.0));

    Circle c2(c1);

    TS_ASSERT_EQUALS(c2.getRadius(), 10.0);
    TS_ASSERT_EQUALS(c2.getPosition(), Vector2D(30.0, 50.0));
  }

  void test_Assignment(void)
  {
    Circle c1(10.0);
    c1.setPosition(Vector2D(30.0, 50.0));

    Circle c2;

    c2 = c1;

    TS_ASSERT_EQUALS(c2.getRadius(), 10.0);
    TS_ASSERT_EQUALS(c2.getPosition(), Vector2D(30.0, 50.0));
  }

  void test_Equality(void)
  {
    // TODO
  }

  void test_Inequality(void)
  {
    // TODO
  }

  void test_GetBoundingBox(void)
  {
    Circle c(10.0);

    TS_ASSERT_EQUALS(c.getBoundingBox(), BoundingBox(-5.0, -5.0, 5.0, 5.0));

    c.setPosition(Vector2D(30.0, 50.0));
    TS_ASSERT_EQUALS(c.getBoundingBox(), BoundingBox(25.0, 45.0, 35.0, 55.0));
  }

  void test_StreamOutput(void)
  {
    Circle c(12.7);
    c.setPosition(Vector2D(54.8, 83.9));

    std::stringstream stream;
    stream << c;

    TS_ASSERT_EQUALS(stream.str(), "[[54.8,83.9],12.7]");
  }

  void test_StreamInput(void)
  {
    std::stringstream stream;
    stream << "[[54.8,83.9],12.7]";

    Circle c;
    stream >> c;

    TS_ASSERT_EQUALS(c.getRadius(), 12.7);
    TS_ASSERT_EQUALS(c.getPosition(), Vector2D(54.8, 83.9));
  }
};
