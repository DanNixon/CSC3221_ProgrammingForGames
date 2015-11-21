#include <cxxtest/TestSuite.h>

#include "BoundingBox.h"
#include "Vector2D.h"

#define TH 0.000001

class BoundingBoxTest : public CxxTest::TestSuite
{
public:
  void test_Create(void)
  {
    BoundingBox b;

    TS_ASSERT_EQUALS(b.getLowerRight().getX(), 0.0);
    TS_ASSERT_EQUALS(b.getLowerRight().getY(), 0.0);
    TS_ASSERT_EQUALS(b.getUpperLeft().getX(), 0.0);
    TS_ASSERT_EQUALS(b.getUpperLeft().getY(), 0.0);
  }

  void test_CreateVectors(void)
  {
    Vector2D lowerRight(2.5, 3.5);
    Vector2D upperLeft(8.7, 9.2);

    BoundingBox b(lowerRight, upperLeft);

    TS_ASSERT_EQUALS(b.getLowerRight().getX(), 2.5);
    TS_ASSERT_EQUALS(b.getLowerRight().getY(), 3.5);
    TS_ASSERT_EQUALS(b.getUpperLeft().getX(), 8.7);
    TS_ASSERT_EQUALS(b.getUpperLeft().getY(), 9.2);
  }

  void test_CreateValues(void)
  {
    BoundingBox b(2.5, 3.5, 8.7, 9.2);

    TS_ASSERT_EQUALS(b.getLowerRight().getX(), 2.5);
    TS_ASSERT_EQUALS(b.getLowerRight().getY(), 3.5);
    TS_ASSERT_EQUALS(b.getUpperLeft().getX(), 8.7);
    TS_ASSERT_EQUALS(b.getUpperLeft().getY(), 9.2);
  }

  void test_CreateCopy(void)
  {
    BoundingBox b1(2.5, 3.5, 8.7, 9.2);
    BoundingBox b2(b1);

    TS_ASSERT_EQUALS(b2.getLowerRight().getX(), 2.5);
    TS_ASSERT_EQUALS(b2.getLowerRight().getY(), 3.5);
    TS_ASSERT_EQUALS(b2.getUpperLeft().getX(), 8.7);
    TS_ASSERT_EQUALS(b2.getUpperLeft().getY(), 9.2);
  }

  void test_Assignment(void)
  {
    BoundingBox b1(0.0, 0.0, 0.0, 0.0);
    BoundingBox b2(2.5, 3.5, 8.7, 9.2);

    TS_ASSERT_EQUALS(b1.getLowerRight().getX(), 0.0);
    TS_ASSERT_EQUALS(b1.getLowerRight().getY(), 0.0);
    TS_ASSERT_EQUALS(b1.getUpperLeft().getX(), 0.0);
    TS_ASSERT_EQUALS(b1.getUpperLeft().getY(), 0.0);

    b1 = b2;

    TS_ASSERT_EQUALS(b1.getLowerRight().getX(), 2.5);
    TS_ASSERT_EQUALS(b1.getLowerRight().getY(), 3.5);
    TS_ASSERT_EQUALS(b1.getUpperLeft().getX(), 8.7);
    TS_ASSERT_EQUALS(b1.getUpperLeft().getY(), 9.2);
  }

  void testEquality(void)
  {
    BoundingBox b1(2.5, 3.5, 8.7, 9.2);
    BoundingBox b2(2.5, 3.5, 8.7, 9.2);
    BoundingBox b3(2.7, 3.8, 9.2, 7.1);

    TS_ASSERT(b1 == b2);
    TS_ASSERT(!(b1 == b3));
  }

  void testInequality(void)
  {
    BoundingBox b1(2.5, 3.5, 8.7, 9.2);
    BoundingBox b2(2.5, 3.5, 8.7, 9.2);
    BoundingBox b3(2.7, 3.8, 9.2, 7.1);

    TS_ASSERT(!(b1 != b2));
    TS_ASSERT(b1 != b3);
  }

  void test_AdditionOperators(void)
  {
  }

  void test_SubtractionOperators(void)
  {
  }

  void test_ShapeFullyEnclosed(void)
  {
    //TODO
  }

  void test_StreamOutput(void)
  {
    BoundingBox b(2.5, 3.5, 8.7, 9.2);

    std::stringstream stream;
    stream << b;

    TS_ASSERT_EQUALS(stream.str(), "[[2.5,3.5],[8.7,9.2]]");
  }

  void test_StreamInput(void)
  {
    std::stringstream stream;
    stream << "[[2.5,3.5],[8.7,9.2]]";

    BoundingBox b;
    stream >> b;

    TS_ASSERT_EQUALS(b.getLowerRight().getX(), 2.5);
    TS_ASSERT_EQUALS(b.getLowerRight().getY(), 3.5);
    TS_ASSERT_EQUALS(b.getUpperLeft().getX(), 8.7);
    TS_ASSERT_EQUALS(b.getUpperLeft().getY(), 9.2);
  }
};
