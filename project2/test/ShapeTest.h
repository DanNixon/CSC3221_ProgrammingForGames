#include <cxxtest/TestSuite.h>

#include "BoundingBox.h"
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
};

class ShapeTest : public CxxTest::TestSuite
{
public:
  void test_Create(void)
  {
    FakeShape s;

    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(0.0, 0.0));
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
    s.setPosition(Vector2D(2.5, 3.5), box);

    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(2.5, 3.5));
  }

  void test_SetPositionClampingActive(void)
  {
    BoundingBox box(0.0, 0.0, 3.0, 4.0);

    FakeShape s;

    TS_ASSERT_THROWS_NOTHING(s.setPosition(Vector2D(3.1, 4.1), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(3.0, 4.0));

    TS_ASSERT_THROWS_NOTHING(s.setPosition(Vector2D(2.0, 4.1), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(2.0, 4.0));

    TS_ASSERT_THROWS_NOTHING(s.setPosition(Vector2D(3.1, 3.0), box));
    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(3.0, 3.0));
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
    FakeShape s;
    s.setPosition(Vector2D(1.0, 2.0));
    s.offsetPositionBy(Vector2D(0.4, 0.9));

    TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.4, 2.9));
  }

  void test_OffsetPositionClampingActive(void)
  {
    FakeShape s;
    s.setPosition(Vector2D(1.0, 2.0));

    //TODO
    /* s.offsetPositionBy(Vector2D(0.4, 0.9)); */
    /* TS_ASSERT_EQUALS(s.getPosition(), Vector2D(1.4, 2.9)); */
  }
};
