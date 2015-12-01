#include <cxxtest/TestSuite.h>

#include "Circle.h"
#include "Square.h"

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

  void test_Intersection_Square_Out_LowerLeft(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(7.0, 7.0));

    TS_ASSERT(!c.intersects(s));
    TS_ASSERT(!s.intersects(c));
  }

  void test_Intersection_Square_Out_UpperRight(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(33.0, 33.0));

    TS_ASSERT(!c.intersects(s));
    TS_ASSERT(!s.intersects(c));
  }

  void test_Intersection_Square_Out_UpperLeft(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(7.0, 33.0));

    TS_ASSERT(!c.intersects(s));
    TS_ASSERT(!s.intersects(c));
  }

  void test_Intersection_Square_Out_LowerRight(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(33.0, 7.0));

    TS_ASSERT(!c.intersects(s));
    TS_ASSERT(!s.intersects(c));
  }

  void test_Intersection_Square_Equal_LowerLeft(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(7.9289, 7.9289));

    TS_ASSERT(!c.intersects(s));
    TS_ASSERT(!s.intersects(c));
  }

  void test_Intersection_Square_Equal_UpperRight(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(32.0711, 32.0711));

    TS_ASSERT(!c.intersects(s));
    TS_ASSERT(!s.intersects(c));
  }

  void test_Intersection_Square_Equal_UpperLeft(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(7.9289, 32.0711));

    TS_ASSERT(!c.intersects(s));
    TS_ASSERT(!s.intersects(c));
  }

  void test_Intersection_Square_Equal_LowerRight(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(32.0711, 7.9289));

    TS_ASSERT(!c.intersects(s));
    TS_ASSERT(!s.intersects(c));
  }

  void test_Intersection_Square_In_LowerLeft(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(9.0, 9.0));

    TS_ASSERT(c.intersects(s));
    TS_ASSERT(s.intersects(c));
  }

  void test_Intersection_Square_In_UpperRight(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(31.0, 31.0));

    TS_ASSERT(c.intersects(s));
    TS_ASSERT(s.intersects(c));
  }

  void test_Intersection_Square_In_UpperLeft(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(9.0, 31.0));

    TS_ASSERT(c.intersects(s));
    TS_ASSERT(s.intersects(c));
  }

  void test_Intersection_Square_In_LowerRight(void)
  {
    Circle c(10.0);
    c.setPosition(Vector2D(20.0, 20.0));

    Square s(10.0, 10.0);
    s.setPosition(Vector2D(31.0, 9.0));

    TS_ASSERT(c.intersects(s));
    TS_ASSERT(s.intersects(c));
  }

  void test_Intersection_Square_In_Centre(void)
  {
    Circle c(5.0);
    c.setPosition(Vector2D(15.0, 15.0));

    Square s(5.0, 6.0);
    s.setPosition(Vector2D(15.0, 15.0));

    TS_ASSERT(c.intersects(s));
    TS_ASSERT(s.intersects(c));
  }

  void test_StreamOutput(void)
  {
    Circle c(12.7);
    c.setPosition(Vector2D(54.8, 83.9));

    std::stringstream stream;
    stream << c;

    TS_ASSERT_EQUALS(stream.str(), "CIRCLE[[54.8,83.9],12.7]");
  }

  void test_StreamInput(void)
  {
    std::stringstream stream;
    stream << "CIRCLE[[54.8,83.9],12.7]";

    Circle c;
    stream >> c;

    TS_ASSERT_EQUALS(c.getRadius(), 12.7);
    TS_ASSERT_EQUALS(c.getPosition(), Vector2D(54.8, 83.9));
  }

  void test_StreamOutput_Multiple(void)
  {
    Circle c1(12.7);
    c1.setPosition(Vector2D(54.8, 83.9));

    Circle c2(15.8);
    c2.setPosition(Vector2D(92.7, 34.3));

    std::stringstream stream;
    stream << c1 << c2;

    TS_ASSERT_EQUALS(stream.str(), "CIRCLE[[54.8,83.9],12.7]CIRCLE[[92.7,34.3],15.8]");
  }

  void test_StreamInput_Multiple(void)
  {
    std::stringstream stream;
    stream << "CIRCLE[[54.8,83.9],12.7]CIRCLE[[92.7,34.3],15.8]";

    Circle c1;
    Circle c2;
    stream >> c1 >> c2;

    TS_ASSERT_EQUALS(c1.getRadius(), 12.7);
    TS_ASSERT_EQUALS(c1.getPosition(), Vector2D(54.8, 83.9));

    TS_ASSERT_EQUALS(c2.getRadius(), 15.8);
    TS_ASSERT_EQUALS(c2.getPosition(), Vector2D(92.7, 34.3));
  }
};
