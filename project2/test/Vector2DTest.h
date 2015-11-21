#include <cxxtest/TestSuite.h>

#include "Vector2D.h"

#define TH 0.000001

class Vector2DTest : public CxxTest::TestSuite
{
public:
  void test_Create(void)
  {
    Vector2D v;

    TS_ASSERT_EQUALS(v.getX(), 0.0);
    TS_ASSERT_EQUALS(v.getY(), 0.0);
  }

  void test_CreateValues(void)
  {
    Vector2D v(2.5, 8.6);

    TS_ASSERT_EQUALS(v.getX(), 2.5);
    TS_ASSERT_EQUALS(v.getY(), 8.6);
  }

  void test_CreateCopy(void)
  {
    Vector2D v1(2.5, 8.6);
    Vector2D v2(v1);

    TS_ASSERT_EQUALS(v2.getX(), 2.5);
    TS_ASSERT_EQUALS(v2.getY(), 8.6);
  }

  void test_CreatePointerCopy(void)
  {
    Vector2D *v1 = new Vector2D(2.5, 8.6);
    Vector2D v2(v1);

    TS_ASSERT_EQUALS(v2.getX(), 2.5);
    TS_ASSERT_EQUALS(v2.getY(), 8.6);
  }

  void test_Assignment(void)
  {
    Vector2D v1;
    Vector2D v2(2.5, 8.6);

    TS_ASSERT_EQUALS(v1.getX(), 0.0);
    TS_ASSERT_EQUALS(v1.getY(), 0.0);

    v1 = v2;

    TS_ASSERT_EQUALS(v1.getX(), 2.5);
    TS_ASSERT_EQUALS(v1.getY(), 8.6);
  }

  void test_Equality(void)
  {
    Vector2D v1(9.7, 6.3);
    Vector2D v2(2.5, 8.6);
    Vector2D v3(2.5, 8.6);

    TS_ASSERT(!(v1 == v2));
    TS_ASSERT(v2 == v3);
  }

  void test_Inequality(void)
  {
    Vector2D v1(9.7, 6.3);
    Vector2D v2(2.5, 8.6);
    Vector2D v3(2.5, 8.6);

    TS_ASSERT(v1 != v2);
    TS_ASSERT(!(v2 != v3));
  }

  void test_AdditionOperators(void)
  {
    Vector2D v1(9.7, 6.3);
    Vector2D v2(2.5, 8.6);

    Vector2D v3 = v1 + v2;

    TS_ASSERT_DELTA(v3.getX(), 12.2, TH);
    TS_ASSERT_DELTA(v3.getY(), 14.9, TH);

    v2 += v1;

    TS_ASSERT_DELTA(v2.getX(), 12.2, TH);
    TS_ASSERT_DELTA(v2.getY(), 14.9, TH);
  }

  void test_SubtractionOperators(void)
  {
    Vector2D v1(9.7, 6.3);
    Vector2D v2(2.5, 8.6);

    Vector2D v3 = v1 - v2;

    TS_ASSERT_DELTA(v3.getX(), 7.2, TH);
    TS_ASSERT_DELTA(v3.getY(), -2.3, TH);

    v1 -= v2;

    TS_ASSERT_DELTA(v1.getX(), 7.2, TH);
    TS_ASSERT_DELTA(v1.getY(), -2.3, TH);
  }

  void test_MultiplicationOperators(void)
  {
    Vector2D v1(9.7, 6.3);

    Vector2D v2 = v1 * 7;

    TS_ASSERT_DELTA(v2.getX(), 67.9, TH);
    TS_ASSERT_DELTA(v2.getY(), 44.1, TH);

    v1 *= 7;

    TS_ASSERT_DELTA(v1.getX(), 67.9, TH);
    TS_ASSERT_DELTA(v1.getY(), 44.1, TH);
  }

  void test_DivisionOperators(void)
  {
    Vector2D v1(9.7, 6.3);

    Vector2D v2 = v1 / 3.2;

    TS_ASSERT_DELTA(v2.getX(), 3.03125, TH);
    TS_ASSERT_DELTA(v2.getY(), 1.96875, TH);

    v1 /= 3.2;

    TS_ASSERT_DELTA(v1.getX(), 3.03125, TH);
    TS_ASSERT_DELTA(v1.getY(), 1.96875, TH);
  }

  void test_GetByIndex(void)
  {
    Vector2D v(2.5, 8.6);

    TS_ASSERT_EQUALS(v[0], 2.5);
    TS_ASSERT_EQUALS(v[1], 8.6);
  }

  void test_GetByIndexOutOfRange(void)
  {
    Vector2D v(2.5, 8.6);

    TS_ASSERT_THROWS(v[3], std::runtime_error);
  }

  void test_StreamOutput(void)
  {
    Vector2D v(2.5, 8.6);

    std::stringstream stream;
    stream << v;

    TS_ASSERT_EQUALS(stream.str(), "[2.5,8.6]");
  }

  void test_StreamInput(void)
  {
    std::stringstream stream;
    stream << "[2.5,8.6]";

    Vector2D v;
    stream >> v;

    TS_ASSERT_EQUALS(v.getX(), 2.5);
    TS_ASSERT_EQUALS(v.getY(), 8.6);
  }
};
