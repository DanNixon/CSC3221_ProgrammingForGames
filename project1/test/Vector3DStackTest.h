#include <cxxtest/TestSuite.h>

#include "Vector3DStack.h"

class Vector3DStackTest : public CxxTest::TestSuite
{
public:
  void test_Default(void)
  {
    Vector3DStack v;
    TS_ASSERT_EQUALS(v.getX(), 0);
    TS_ASSERT_EQUALS(v.getY(), 0);
    TS_ASSERT_EQUALS(v.getZ(), 0);
  }

  void test_CreateWithValues(void)
  {
    Vector3DStack v(1, 6, 3);
    TS_ASSERT_EQUALS(v.getX(), 1);
    TS_ASSERT_EQUALS(v.getY(), 6);
    TS_ASSERT_EQUALS(v.getZ(), 3);
  }

  void test_Addition(void)
  {
    Vector3DStack v1(1, 6, 3);
    Vector3DStack v2(5, 2, 9);
    Vector3DStack v3 = v1 + v2;
    TS_ASSERT_EQUALS(v3.getX(), 6);
    TS_ASSERT_EQUALS(v3.getY(), 8);
    TS_ASSERT_EQUALS(v3.getZ(), 12);
  }

  void test_Subtraction(void)
  {
    Vector3DStack v1(1, 6, 3);
    Vector3DStack v2(5, 2, 9);
    Vector3DStack v3 = v1 - v2;
    TS_ASSERT_EQUALS(v3.getX(), -4);
    TS_ASSERT_EQUALS(v3.getY(), 4);
    TS_ASSERT_EQUALS(v3.getZ(), -6);
  }

  void test_ScalarMultiplication(void)
  {
    Vector3DStack v1(1, 6, 3);
    Vector3DStack v2 = v1 * 6;
    TS_ASSERT_EQUALS(v2.getX(), 6);
    TS_ASSERT_EQUALS(v2.getY(), 36);
    TS_ASSERT_EQUALS(v2.getZ(), 18);
  }

  void test_ScalarDivision(void)
  {
    Vector3DStack v1(2, 6, 4);
    Vector3DStack v2 = v1 / 2;
    TS_ASSERT_EQUALS(v2.getX(), 1);
    TS_ASSERT_EQUALS(v2.getY(), 3);
    TS_ASSERT_EQUALS(v2.getZ(), 2);
  }

  void test_Magnitude(void)
  {
    Vector3DStack v(1, 6, 3);
    TS_ASSERT_EQUALS(v.magnitude(), 6);
  }

  void test_DotProduct(void)
  {
    Vector3DStack v1(1, 6, 3);
    Vector3DStack v2(5, 2, 9);
    int dotProd = v1 * v2;
    TS_ASSERT_EQUALS(dotProd, 44);
  }

  void test_CrossProduct(void)
  {
    Vector3DStack v1(1, 6, 3);
    Vector3DStack v2(5, 2, 9);
    Vector3DStack v3 = v1 % v2;
    TS_ASSERT_EQUALS(v3.getX(), 48);
    TS_ASSERT_EQUALS(v3.getY(), 6);
    TS_ASSERT_EQUALS(v3.getZ(), -28);
  }
};
