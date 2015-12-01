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

    TS_ASSERT_EQUALS(b.getLowerLeft().getX(), 0.0);
    TS_ASSERT_EQUALS(b.getLowerLeft().getY(), 0.0);
    TS_ASSERT_EQUALS(b.getUpperRight().getX(), 0.0);
    TS_ASSERT_EQUALS(b.getUpperRight().getY(), 0.0);
  }

  void test_CreateVectors(void)
  {
    Vector2D lowerRight(2.5, 3.5);
    Vector2D upperLeft(8.7, 9.2);

    BoundingBox b(lowerRight, upperLeft);

    TS_ASSERT_EQUALS(b.getLowerLeft().getX(), 2.5);
    TS_ASSERT_EQUALS(b.getLowerLeft().getY(), 3.5);
    TS_ASSERT_EQUALS(b.getUpperRight().getX(), 8.7);
    TS_ASSERT_EQUALS(b.getUpperRight().getY(), 9.2);
  }

  void test_CreateVectorsBadOrder(void)
  {
    Vector2D lowerRight(2.5, 3.5);
    Vector2D upperLeft(8.7, 9.2);

    BoundingBox b(upperLeft, lowerRight);

    TS_ASSERT_EQUALS(b.getLowerLeft().getX(), 2.5);
    TS_ASSERT_EQUALS(b.getLowerLeft().getY(), 3.5);
    TS_ASSERT_EQUALS(b.getUpperRight().getX(), 8.7);
    TS_ASSERT_EQUALS(b.getUpperRight().getY(), 9.2);
  }

  void test_CreateValues(void)
  {
    BoundingBox b(2.5, 3.5, 8.7, 9.2);

    TS_ASSERT_EQUALS(b.getLowerLeft().getX(), 2.5);
    TS_ASSERT_EQUALS(b.getLowerLeft().getY(), 3.5);
    TS_ASSERT_EQUALS(b.getUpperRight().getX(), 8.7);
    TS_ASSERT_EQUALS(b.getUpperRight().getY(), 9.2);
  }

  void test_CreateValuesBadOrder(void)
  {
    BoundingBox b(8.7, 9.2, 2.5, 3.5);

    TS_ASSERT_EQUALS(b.getLowerLeft().getX(), 2.5);
    TS_ASSERT_EQUALS(b.getLowerLeft().getY(), 3.5);
    TS_ASSERT_EQUALS(b.getUpperRight().getX(), 8.7);
    TS_ASSERT_EQUALS(b.getUpperRight().getY(), 9.2);
  }

  void test_CreateCopy(void)
  {
    BoundingBox b1(2.5, 3.5, 8.7, 9.2);
    BoundingBox b2(b1);

    TS_ASSERT_EQUALS(b2.getLowerLeft().getX(), 2.5);
    TS_ASSERT_EQUALS(b2.getLowerLeft().getY(), 3.5);
    TS_ASSERT_EQUALS(b2.getUpperRight().getX(), 8.7);
    TS_ASSERT_EQUALS(b2.getUpperRight().getY(), 9.2);
  }

  void test_Assignment(void)
  {
    BoundingBox b1(0.0, 0.0, 0.0, 0.0);
    BoundingBox b2(2.5, 3.5, 8.7, 9.2);

    TS_ASSERT_EQUALS(b1.getLowerLeft().getX(), 0.0);
    TS_ASSERT_EQUALS(b1.getLowerLeft().getY(), 0.0);
    TS_ASSERT_EQUALS(b1.getUpperRight().getX(), 0.0);
    TS_ASSERT_EQUALS(b1.getUpperRight().getY(), 0.0);

    b1 = b2;

    TS_ASSERT_EQUALS(b1.getLowerLeft().getX(), 2.5);
    TS_ASSERT_EQUALS(b1.getLowerLeft().getY(), 3.5);
    TS_ASSERT_EQUALS(b1.getUpperRight().getX(), 8.7);
    TS_ASSERT_EQUALS(b1.getUpperRight().getY(), 9.2);
  }

  void test_SelfAssignment(void)
  {
    BoundingBox b(2.5, 3.5, 8.7, 9.2);

    b = b;

    TS_ASSERT_EQUALS(b.getLowerLeft().getX(), 2.5);
    TS_ASSERT_EQUALS(b.getLowerLeft().getY(), 3.5);
    TS_ASSERT_EQUALS(b.getUpperRight().getX(), 8.7);
    TS_ASSERT_EQUALS(b.getUpperRight().getY(), 9.2);
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
    BoundingBox b1(2.5, 3.5, 8.7, 9.2);
    Vector2D offset(0.5, 0.2);

    BoundingBox b2 = b1 + offset;

    TS_ASSERT_DELTA(b2.getLowerLeft().getX(), 3.0, TH);
    TS_ASSERT_DELTA(b2.getLowerLeft().getY(), 3.7, TH);
    TS_ASSERT_DELTA(b2.getUpperRight().getX(), 9.2, TH);
    TS_ASSERT_DELTA(b2.getUpperRight().getY(), 9.4, TH);

    b1 += offset;

    TS_ASSERT_DELTA(b1.getLowerLeft().getX(), 3.0, TH);
    TS_ASSERT_DELTA(b1.getLowerLeft().getY(), 3.7, TH);
    TS_ASSERT_DELTA(b1.getUpperRight().getX(), 9.2, TH);
    TS_ASSERT_DELTA(b1.getUpperRight().getY(), 9.4, TH);
  }

  void test_SubtractionOperators(void)
  {
    BoundingBox b1(2.5, 3.5, 8.7, 9.2);
    Vector2D offset(0.5, 0.2);

    BoundingBox b2 = b1 - offset;

    TS_ASSERT_DELTA(b2.getLowerLeft().getX(), 2.0, TH);
    TS_ASSERT_DELTA(b2.getLowerLeft().getY(), 3.3, TH);
    TS_ASSERT_DELTA(b2.getUpperRight().getX(), 8.2, TH);
    TS_ASSERT_DELTA(b2.getUpperRight().getY(), 9.0, TH);

    b1 -= offset;

    TS_ASSERT_DELTA(b1.getLowerLeft().getX(), 2.0, TH);
    TS_ASSERT_DELTA(b1.getLowerLeft().getY(), 3.3, TH);
    TS_ASSERT_DELTA(b1.getUpperRight().getX(), 8.2, TH);
    TS_ASSERT_DELTA(b1.getUpperRight().getY(), 9.0, TH);
  }

  void test_Size(void)
  {
    BoundingBox b(2.5, 3.5, 8.7, 9.2);
    Vector2D size = b.size();

    TS_ASSERT_DELTA(size.getX(), 6.2, TH);
    TS_ASSERT_DELTA(size.getY(), 5.7, TH);
  }

  void test_UpperLeft(void)
  {
    BoundingBox b(1.0, 2.0, 9.0, 10.0);
    Vector2D upperLeft = b.getUpperLeft();

    TS_ASSERT_EQUALS(upperLeft.getX(), 1.0);
    TS_ASSERT_EQUALS(upperLeft.getY(), 10.0);
  }

  void test_LowerRight(void)
  {
    BoundingBox b(1.0, 2.0, 9.0, 10.0);
    Vector2D lowerRight = b.getLowerRight();

    TS_ASSERT_EQUALS(lowerRight.getX(), 9.0);
    TS_ASSERT_EQUALS(lowerRight.getY(), 2.0);
  }

  void test_Centre(void)
  {
    BoundingBox b(1.0, 2.0, 9.0, 10.0);
    Vector2D centre = b.getCentre();

    TS_ASSERT_EQUALS(centre.getX(), 5.0);
    TS_ASSERT_EQUALS(centre.getY(), 6.0);
  }

  void test_RelativePosition_UpperRight(void)
  {
    BoundingBox b1(-1.0, -1.0, 1.0, 1.0);
    BoundingBox b2(0.0, 0.0, 2.1, 2.1);

    TS_ASSERT_EQUALS(b1.getRelativePosition(b2), D_UPPERRIGHT);
  }

  void test_RelativePosition_LowerRight(void)
  {
    BoundingBox b1(-1.0, -1.0, 1.0, 1.0);
    BoundingBox b2(0.0, -2.1, 2.1, 0.0);

    TS_ASSERT_EQUALS(b1.getRelativePosition(b2), D_LOWERRIGHT);
  }

  void test_RelativePosition_UpperLeft(void)
  {
    BoundingBox b1(-1.0, -1.0, 1.0, 1.0);
    BoundingBox b2(-2.1, 0.0, 0.0, 2.1);

    TS_ASSERT_EQUALS(b1.getRelativePosition(b2), D_UPPERLEFT);
  }

  void test_RelativePosition_LowerLeft(void)
  {
    BoundingBox b1(-1.0, -1.0, 1.0, 1.0);
    BoundingBox b2(-2.1, -2.1, 0.0, 0.0);

    TS_ASSERT_EQUALS(b1.getRelativePosition(b2), D_LOWERLEFT);
  }

  void test_BoundingBoxEnclosed_Fully(void)
  {
    BoundingBox b1(0.0, 0.0, 1.0, 1.0);
    BoundingBox b2(0.25, 0.25, 0.75, 0.75);

    TS_ASSERT(b1.encloses(b2));
  }

  void test_BoundingBoxEnclosed_PartiallyLowerLeft(void)
  {
    BoundingBox b1(0.0, 0.0, 1.0, 1.0);
    BoundingBox b2(-0.25, -0.25, 0.25, 0.25);

    TS_ASSERT(!b1.encloses(b2));
  }

  void test_BoundingBoxEnclosed_PartiallyUpperRight(void)
  {
    BoundingBox b1(0.0, 0.0, 1.0, 1.0);
    BoundingBox b2(0.75, 0.75, 1.25, 1.25);

    TS_ASSERT(!b1.encloses(b2));
  }

  void test_BoundingBoxEnclosed_Larger(void)
  {
    BoundingBox b1(0.0, 0.0, 1.0, 1.0);
    BoundingBox b2(-0.25, -0.25, 1.25, 1.25);

    TS_ASSERT(!b1.encloses(b2));
  }

  void test_Intersects_Fully(void)
  {
    BoundingBox b1(0.0, 0.0, 1.0, 1.0);
    BoundingBox b2(0.1, 0.1, 0.9, 0.9);

    TS_ASSERT(b1.intersects(b2));
    TS_ASSERT(b2.intersects(b1));
  }

  void test_StreamOutput(void)
  {
    BoundingBox b(2.5, 3.5, 8.7, 9.2);

    std::stringstream stream;
    stream << b;

    TS_ASSERT_EQUALS(stream.str(),
                     "BoundingBox[LowerLeft[2.5,3.5],UpperRight[8.7,9.2]]");
  }

  void test_StreamInput(void)
  {
    std::stringstream stream;
    stream << "BoundingBox[LowerLeft[2.5,3.5],UpperRight[8.7,9.2]]";

    BoundingBox b;
    stream >> b;

    TS_ASSERT_EQUALS(b.getLowerLeft().getX(), 2.5);
    TS_ASSERT_EQUALS(b.getLowerLeft().getY(), 3.5);
    TS_ASSERT_EQUALS(b.getUpperRight().getX(), 8.7);
    TS_ASSERT_EQUALS(b.getUpperRight().getY(), 9.2);
  }
};
