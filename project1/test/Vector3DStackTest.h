#include <cxxtest/TestSuite.h>

#include "Vector3DStack.h"

#define TH 0.0001

class Vector3DStackTest : public CxxTest::TestSuite
{
public:
  void test_Default(void)
  {
    Vector3DStack v;
    TS_ASSERT_EQUALS(v.getX(), 0.0);
    TS_ASSERT_EQUALS(v.getY(), 0.0);
    TS_ASSERT_EQUALS(v.getZ(), 0.0);
  }

  void test_CreateWithValues(void)
  {
    Vector3DStack v(1.0, 6.0, 3.0);
    TS_ASSERT_EQUALS(v.getX(), 1.0);
    TS_ASSERT_EQUALS(v.getY(), 6.0);
    TS_ASSERT_EQUALS(v.getZ(), 3.0);
  }

  void test_CreateCopyConstructior(void)
  {
    Vector3DStack v1(1.0, 6.0, 3.0);
    Vector3DStack v2(v1);

    TS_ASSERT_EQUALS(v2.getX(), 1.0);
    TS_ASSERT_EQUALS(v2.getY(), 6.0);
    TS_ASSERT_EQUALS(v2.getZ(), 3.0);
  }

  void test_Assignment(void)
  {
    Vector3DStack v1(1.0, 6.0, 3.0);
    Vector3DStack v2(3.0, 6.0, 8.0);

    v2 = v1;

    TS_ASSERT_EQUALS(v2.getX(), 1.0);
    TS_ASSERT_EQUALS(v2.getY(), 6.0);
    TS_ASSERT_EQUALS(v2.getZ(), 3.0);
  }

  void test_Equality(void)
  {
    Vector3DStack v1(1.0, 6.0, 3.0);
    Vector3DStack v2(3.0, 6.0, 8.0);
    Vector3DStack v3(1.0, 6.0, 3.0);

    TS_ASSERT_DIFFERS(v1, v2);
    TS_ASSERT_EQUALS(v1, v3);
  }

  void test_Addition(void)
  {
    Vector3DStack v1(1.0, 6.0, 3.0);
    Vector3DStack v2(5.0, 2.0, 9.0);
    Vector3DStack v3 = v1 + v2;
    TS_ASSERT_EQUALS(v3.getX(), 6.0);
    TS_ASSERT_EQUALS(v3.getY(), 8.0);
    TS_ASSERT_EQUALS(v3.getZ(), 12.0);
  }

  void test_Subtraction(void)
  {
    Vector3DStack v1(1.0, 6.0, 3.0);
    Vector3DStack v2(5.0, 2.0, 9.0);
    Vector3DStack v3 = v1 - v2;
    TS_ASSERT_EQUALS(v3.getX(), -4.0);
    TS_ASSERT_EQUALS(v3.getY(), 4.0);
    TS_ASSERT_EQUALS(v3.getZ(), -6.0);
  }

  void test_ScalarMultiplication(void)
  {
    Vector3DStack v1(1.0, 6.0, 3.0);
    Vector3DStack v2 = v1 * 6.0;
    TS_ASSERT_EQUALS(v2.getX(), 6.0);
    TS_ASSERT_EQUALS(v2.getY(), 36.0);
    TS_ASSERT_EQUALS(v2.getZ(), 18.0);
  }

  void test_ScalarDivision(void)
  {
    Vector3DStack v1(1.0, 6.0, 3.0);
    Vector3DStack v2 = v1 / 2.0;
    TS_ASSERT_EQUALS(v2.getX(), 0.5);
    TS_ASSERT_EQUALS(v2.getY(), 3.0);
    TS_ASSERT_EQUALS(v2.getZ(), 1.5);
  }

  void test_Magnitude(void)
  {
    Vector3DStack v(1.0, 6.0, 3.0);
    TS_ASSERT_DELTA(v.magnitude(), 6.7823, TH);
  }

  void test_DotProduct(void)
  {
    Vector3DStack v1(1, 6, 3);
    Vector3DStack v2(5, 2, 9);
    double dotProd = v1 * v2;
    TS_ASSERT_EQUALS(dotProd, 44);
  }

  void test_CrossProduct(void)
  {
    Vector3DStack v1(1.0, 6.0, 3.0);
    Vector3DStack v2(5.0, 2.0, 9.0);
    Vector3DStack v3 = v1 % v2;
    TS_ASSERT_EQUALS(v3.getX(), 48.0);
    TS_ASSERT_EQUALS(v3.getY(), 6.0);
    TS_ASSERT_EQUALS(v3.getZ(), -28.0);
  }

  void test_UnitVector(void)
  {
    Vector3DStack v(1.0, 6.0, 3.0);
    Vector3DStack unit = v.getUnitVector();

    TS_ASSERT_EQUALS(unit.magnitude(), 1.0);
    TS_ASSERT_DELTA(unit.getX(), 0.1474, TH);
    TS_ASSERT_DELTA(unit.getY(), 0.8846, TH);
    TS_ASSERT_DELTA(unit.getZ(), 0.4423, TH);
  }
};
