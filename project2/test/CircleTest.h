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
    Circle c1(10.0);
    c1.setPosition(Vector2D(5.0, 3.0));
    Circle c2(10.0);
    c2.setPosition(Vector2D(5.0, 3.0));
    Circle c3(10.0);
    c3.setPosition(Vector2D(5.7, 2.0));
    Circle c4(12.0);
    c4.setPosition(Vector2D(5.0, 3.0));

    TS_ASSERT(c1 == c2);
    TS_ASSERT(!(c1 == c3));
    TS_ASSERT(!(c1 == c4));
  }

  void test_Inequality(void)
  {
    Circle c1(10.0);
    c1.setPosition(Vector2D(5.0, 3.0));
    Circle c2(10.0);
    c2.setPosition(Vector2D(5.0, 3.0));
    Circle c3(10.0);
    c3.setPosition(Vector2D(5.7, 2.0));
    Circle c4(12.0);
    c4.setPosition(Vector2D(5.0, 3.0));

    TS_ASSERT(!(c1 != c2));
    TS_ASSERT(c1 != c3);
    TS_ASSERT(c1 != c4);
  }

  void test_GetBoundingBox(void)
  {
    Circle c(5.0);

    TS_ASSERT_EQUALS(c.getBoundingBox(), BoundingBox(-5.0, -5.0, 5.0, 5.0));

    c.setPosition(Vector2D(30.0, 50.0));
    TS_ASSERT_EQUALS(c.getBoundingBox(), BoundingBox(25.0, 45.0, 35.0, 55.0));
  }

  void test_Intersection_Circle_Out(void)
  {
    Circle c1(5.0);
    c1.setPosition(Vector2D(-5.0, -5.0));

    Circle c2(5.0);
    c2.setPosition(Vector2D(5.0, 5.0));

    TS_ASSERT(!c1.intersects(c2));
    TS_ASSERT(!c2.intersects(c1));
  }

  void test_Intersection_Circle_Equal(void)
  {
    Circle c1(5.0);
    c1.setPosition(Vector2D(0.0, 0.0));

    Circle c2(5.0);
    c2.setPosition(Vector2D(0.0, 10.0));

    TS_ASSERT(!c1.intersects(c2));
    TS_ASSERT(!c2.intersects(c1));

    Circle c3(5.0);
    c3.setPosition(Vector2D(10.0, 0.0));

    TS_ASSERT(!c1.intersects(c3));
    TS_ASSERT(!c3.intersects(c1));
  }

  void test_Intersection_Circle_In(void)
  {
    Circle c1(5.0);
    c1.setPosition(Vector2D(-5.0, -5.0));

    Circle c2(5.0);
    c2.setPosition(Vector2D(1.0, 1.0));

    TS_ASSERT(c1.intersects(c2));
    TS_ASSERT(c2.intersects(c1));
  }

  void test_Intersection_Circle_Near(void)
  {
    Circle c1(5.0);
    c1.setPosition(Vector2D(0.0, 0.0));

    Circle c2(5.0);
    c2.setPosition(Vector2D(9.0, 9.0));

    TS_ASSERT(c1.getBoundingBox().intersects(c2.getBoundingBox()));

    TS_ASSERT(!c1.intersects(c2));
    TS_ASSERT(!c2.intersects(c1));
  }

  void test_Intersection_Square_Out(void)
  {
    // TODO
  }

  void test_Intersection_Square_Equal(void)
  {
    // TODO
  }

  void test_Intersection_Square_In(void)
  {
    // TODO
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
