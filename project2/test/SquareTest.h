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

  void test_CreateGivenSize(void)
  {
    Square s(10.0, 12.0);

    TS_ASSERT_EQUALS(s.getWidth(), 10.0);
    TS_ASSERT_EQUALS(s.getHeight(), 12.0);
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(0.0, 0.0));
  }

  void test_CreateCopy(void)
  {
    Square s1(10.0, 12.0);
    s1.setPosition(Vector2D(7.0, 15.0));

    Square s2(s1);

    TS_ASSERT_EQUALS(s2.getWidth(), 10.0);
    TS_ASSERT_EQUALS(s2.getHeight(), 12.0);
    TS_ASSERT_EQUALS(s2.getPosition(), Vector2D(7.0, 15.0));
  }

  void test_Assignment(void)
  {
    Square s1(10.0, 12.0);
    s1.setPosition(Vector2D(7.0, 15.0));

    Square s2;

    s2 = s1;

    TS_ASSERT_EQUALS(s2.getWidth(), 10.0);
    TS_ASSERT_EQUALS(s2.getHeight(), 12.0);
    TS_ASSERT_EQUALS(s2.getPosition(), Vector2D(7.0, 15.0));
  }

  void test_Equality(void)
  {
    Square s1(10.0, 5.0);
    s1.setPosition(Vector2D(5.0, 3.0));
    Square s2(10.0, 5.0);
    s2.setPosition(Vector2D(5.0, 3.0));
    Square s3(10.0, 5.0);
    s3.setPosition(Vector2D(5.7, 2.0));
    Square s4(12.0, 6.0);
    s4.setPosition(Vector2D(5.0, 3.0));
    Square s5(10.0, 6.0);
    s5.setPosition(Vector2D(5.0, 3.0));

    TS_ASSERT(s1 == s2);
    TS_ASSERT(!(s1 == s3));
    TS_ASSERT(!(s1 == s4));
    TS_ASSERT(!(s1 == s5));
  }

  void test_Inequality(void)
  {
    Square s1(10.0, 5.0);
    s1.setPosition(Vector2D(5.0, 3.0));
    Square s2(10.0, 5.0);
    s2.setPosition(Vector2D(5.0, 3.0));
    Square s3(10.0, 5.0);
    s3.setPosition(Vector2D(5.7, 2.0));
    Square s4(12.0, 5.0);
    s4.setPosition(Vector2D(5.0, 3.0));
    Square s5(10.0, 6.0);
    s5.setPosition(Vector2D(5.0, 3.0));

    TS_ASSERT(!(s1 != s2));
    TS_ASSERT(s1 != s3);
    TS_ASSERT(s1 != s4);
    TS_ASSERT(s1 != s5);
  }

  void test_GetBoundingBox(void)
  {
    Square s(10.0, 12.0);

    TS_ASSERT_EQUALS(s.getBoundingBox(), BoundingBox(-5.0, -6.0, 5.0, 6.0));

    s.setPosition(Vector2D(30.0, 50.0));
    TS_ASSERT_EQUALS(s.getBoundingBox(), BoundingBox(25.0, 44.0, 35.0, 56.0));
  }

  void test_Intersection_Square_Out_Top(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(10, 0.0));

    TS_ASSERT(!s1.intersects(s2));
    TS_ASSERT(!s2.intersects(s1));
  }

  void test_Intersection_Square_Out_Bottom(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(-10.0, 0.0));

    TS_ASSERT(!s1.intersects(s2));
    TS_ASSERT(!s2.intersects(s1));
  }

  void test_Intersection_Square_Out_Left(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(0.0, -10.0));

    TS_ASSERT(!s1.intersects(s2));
    TS_ASSERT(!s2.intersects(s1));
  }

  void test_Intersection_Square_Out_Right(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(0.0, 10.0));

    TS_ASSERT(!s1.intersects(s2));
    TS_ASSERT(!s2.intersects(s1));
  }

  void test_Intersection_Square_Equal_Top(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(7.5, 0.0));

    TS_ASSERT(!s1.intersects(s2));
    TS_ASSERT(!s2.intersects(s1));
  }

  void test_Intersection_Square_Equal_Bottom(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(-7.5, 0.0));

    TS_ASSERT(!s1.intersects(s2));
    TS_ASSERT(!s2.intersects(s1));
  }

  void test_Intersection_Square_Equal_Left(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(0.0, -7.5));

    TS_ASSERT(!s1.intersects(s2));
    TS_ASSERT(!s2.intersects(s1));
  }

  void test_Intersection_Square_Equal_Right(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(0.0, 7.5));

    TS_ASSERT(!s1.intersects(s2));
    TS_ASSERT(!s2.intersects(s1));
  }

  void test_Intersection_Square_In_Top(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(6.5, 0.0));

    TS_ASSERT(s1.intersects(s2));
    TS_ASSERT(s2.intersects(s1));
  }

  void test_Intersection_Square_In_Botton(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(-6.5, 0.0));

    TS_ASSERT(s1.intersects(s2));
    TS_ASSERT(s2.intersects(s1));
  }

  void test_Intersection_Square_In_Left(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(0.0, -6.5));

    TS_ASSERT(s1.intersects(s2));
    TS_ASSERT(s2.intersects(s1));
  }

  void test_Intersection_Square_In_Right(void)
  {
    Square s1(10.0, 10.0);

    Square s2(5.0, 5.0);
    s2.setPosition(Vector2D(0.0, 6.5));

    TS_ASSERT(s1.intersects(s2));
    TS_ASSERT(s2.intersects(s1));
  }

  void test_StreamOutput(void)
  {
    Square s(12.7, 18.35);
    s.setPosition(Vector2D(54.8, 83.9));

    std::stringstream stream;
    stream << s;

    TS_ASSERT_EQUALS(stream.str(), "SQUARE[[54.8,83.9],12.7,18.35]");
  }

  void test_StreamInput(void)
  {
    std::stringstream stream;
    stream << "SQUARE[[54.8,83.9],12.7,18.35]";

    Square s;
    stream >> s;

    TS_ASSERT_EQUALS(s.getWidth(), 12.7);
    TS_ASSERT_EQUALS(s.getHeight(), 18.35);
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(54.8, 83.9));
  }

  void test_StreamOutput_Multiple(void)
  {
    Square s1(12.7, 18.35);
    s1.setPosition(Vector2D(54.8, 83.9));

    Square s2(15.8, 19.7);
    s2.setPosition(Vector2D(92.7, 34.3));

    std::stringstream stream;
    stream << s1 << s2;

    TS_ASSERT_EQUALS(stream.str(),
                     "SQUARE[[54.8,83.9],12.7,18.35]SQUARE[[92.7,34.3],15.8,19.7]");
  }

  void test_StreamInput_Multiple(void)
  {
    std::stringstream stream;
    stream << "SQUARE[[54.8,83.9],12.7,18.35]SQUARE[[92.7,34.3],15.8,19.7]";

    Square s1;
    Square s2;
    stream >> s1 >> s2;

    TS_ASSERT_EQUALS(s1.getWidth(), 12.7);
    TS_ASSERT_EQUALS(s1.getHeight(), 18.35);
    TS_ASSERT_EQUALS(s1.getPosition(), Vector2D(54.8, 83.9));

    TS_ASSERT_EQUALS(s2.getWidth(), 15.8);
    TS_ASSERT_EQUALS(s2.getHeight(), 19.7);
    TS_ASSERT_EQUALS(s2.getPosition(), Vector2D(92.7, 34.3));
  }
};
