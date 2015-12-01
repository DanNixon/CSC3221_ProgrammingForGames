#include <cxxtest/TestSuite.h>

#include "BoundingBox.h"
#include "Vector2D.h"
#include "Shape.h"

class FakeShape : public Shape
{
public:
  FakeShape()
      : Shape()
  {
  }

  FakeShape(const FakeShape &other)
      : Shape(other)
  {
  }

  ~FakeShape()
  {
  }

  BoundingBox getBoundingBox() const
  {
    Vector2D dimensions(0.5, 0.5);
    return BoundingBox(m_position - dimensions, m_position + dimensions);
  }

private:
  virtual bool compare(const Shape &other) const
  {
    (void)other;
    return true;
  }
};

class ShapeTest : public CxxTest::TestSuite
{
public:
  void test_Create(void)
  {
    FakeShape s;

    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(0.0, 0.0));
  }

  void test_CreateCopy(void)
  {
    FakeShape s1;
    s1.setPosition(Vector2D(5.0, 3.0));

    FakeShape s2(s1);

    TS_ASSERT_EQUALS(s2.getPosition(), Vector2D(5.0, 3.0));
  }

  void test_Assignment(void)
  {
    FakeShape s1;
    s1.setPosition(Vector2D(5.0, 3.0));

    FakeShape s2;

    s2 = s1;

    TS_ASSERT_EQUALS(s2.getPosition(), Vector2D(5.0, 3.0));
  }

  void test_Equality(void)
  {
    FakeShape s1;
    s1.setPosition(Vector2D(5.0, 3.0));
    FakeShape s2;
    s2.setPosition(Vector2D(5.0, 3.0));
    FakeShape s3;
    s3.setPosition(Vector2D(5.7, 2.0));

    TS_ASSERT(s1 == s2);
    TS_ASSERT(!(s1 == s3));
  }

  void test_Inequality(void)
  {
    FakeShape s1;
    s1.setPosition(Vector2D(5.0, 3.0));
    FakeShape s2;
    s2.setPosition(Vector2D(5.0, 3.0));
    FakeShape s3;
    s3.setPosition(Vector2D(5.7, 2.0));

    TS_ASSERT(!(s1 != s2));
    TS_ASSERT(s1 != s3);
  }

  void test_SetPosition(void)
  {
    FakeShape s;
    s.setPosition(Vector2D(5.7, 2.1));

    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(5.7, 2.1));
  }

  void test_SetPositionClampingSet(void)
  {
    BoundingBox box(0.0, 0.0, 3.0, 4.0);
    FakeShape s;

    TS_ASSERT(s.setPosition(Vector2D(1.5, 2.5), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.5, 2.5));
  }

  void test_SetPositionClampingActive(void)
  {
    BoundingBox box(0.5, 0.75, 3.0, 4.0);
    FakeShape s;

    /* Set initial position */
    TS_ASSERT(s.setPosition(Vector2D(1.5, 2.5), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.5, 2.5));

    /* Above X and Y on upper right */
    TS_ASSERT(!s.setPosition(Vector2D(3.1, 4.1), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.5, 2.5));

    /* Above X on upper right */
    TS_ASSERT(!s.setPosition(Vector2D(3.1, 3.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.5, 2.5));

    /* Above Y on upper right */
    TS_ASSERT(!s.setPosition(Vector2D(2.0, 4.1), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.5, 2.5));

    /* Below X and Y on lower left */
    TS_ASSERT(!s.setPosition(Vector2D(-0.5, -0.5), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.5, 2.5));

    /* Below X on lower left */
    TS_ASSERT(!s.setPosition(Vector2D(-0.5, 2.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.5, 2.5));

    /* Below Y on lower left */
    TS_ASSERT(!s.setPosition(Vector2D(2.0, -0.5), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.5, 2.5));
  }

  void test_OffsetPosition(void)
  {
    FakeShape s;
    s.setPosition(Vector2D(1.0, 2.0));
    s.offsetPositionBy(Vector2D(0.4, 0.9));

    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.4, 2.9));
  }

  void test_OffsetPositionClampingSet(void)
  {
    BoundingBox box(6.0, 4.0, 10.0, 8.0);
    FakeShape s;

    TS_ASSERT(s.setPosition(Vector2D(8.0, 6.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));

    TS_ASSERT(s.offsetPositionBy(Vector2D(0.4, 0.9), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.4, 6.9));
  }

  void test_OffsetPositionClampingActive_OverXYUpperRight(void)
  {
    BoundingBox box(6.0, 4.0, 10.0, 8.0);
    FakeShape s;

    /* Set to centre of bounding box */
    TS_ASSERT(s.setPosition(Vector2D(8.0, 6.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));

    /* Above X and Y on upper right */
    TS_ASSERT(!s.offsetPositionBy(Vector2D(2.1, 2.1), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));
  }

  void test_OffsetPositionClampingActive_OverXUpperRight(void)
  {
    BoundingBox box(6.0, 4.0, 10.0, 8.0);
    FakeShape s;

    /* Set to centre of bounding box */
    TS_ASSERT(s.setPosition(Vector2D(8.0, 6.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));

    /* Above X on upper right */
    TS_ASSERT(!s.offsetPositionBy(Vector2D(2.1, 0.5), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));
  }

  void test_OffsetPositionClampingActive_OverYUpperRight(void)
  {
    BoundingBox box(6.0, 4.0, 10.0, 8.0);
    FakeShape s;

    /* Set to centre of bounding box */
    TS_ASSERT(s.setPosition(Vector2D(8.0, 6.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));

    /* Above Y on upper right */
    TS_ASSERT(!s.offsetPositionBy(Vector2D(0.5, 2.1), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));
  }

  void test_OffsetPositionClampingActive_UnderXYLowerLeft(void)
  {
    BoundingBox box(6.0, 4.0, 10.0, 8.0);
    FakeShape s;

    /* Set to centre of bounding box */
    TS_ASSERT(s.setPosition(Vector2D(8.0, 6.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));

    /* Below X and Y on lower left */
    TS_ASSERT(!s.offsetPositionBy(Vector2D(-2.1, -2.1), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));
  }

  void test_OffsetPositionClampingActive_UnderXLowerLeft(void)
  {
    BoundingBox box(6.0, 4.0, 10.0, 8.0);
    FakeShape s;

    /* Set to centre of bounding box */
    TS_ASSERT(s.setPosition(Vector2D(8.0, 6.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));

    /* Below X on lower left */
    TS_ASSERT(!s.offsetPositionBy(Vector2D(-2.1, -0.5), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));
  }

  void test_OffsetPositionClampingActive_UnderYLowerLeft(void)
  {
    BoundingBox box(6.0, 4.0, 10.0, 8.0);
    FakeShape s;

    /* Set to centre of bounding box */
    TS_ASSERT(s.setPosition(Vector2D(8.0, 6.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));

    /* Below Y on lower left */
    TS_ASSERT(!s.offsetPositionBy(Vector2D(-0.5, -2.1), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(8.0, 6.0));
  }
};
