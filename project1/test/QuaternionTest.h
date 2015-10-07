#include <cxxtest/TestSuite.h>

#include "Quaternion.h"

#define TH 0.0001

class QuaternionTest : public CxxTest::TestSuite
{
public:
  void test_Default(void)
  {
    Quaternion q;
    TS_ASSERT_EQUALS(q.getReal(), 1.0);
    TS_ASSERT_EQUALS(q.getI(), 0.0);
    TS_ASSERT_EQUALS(q.getJ(), 0.0);
    TS_ASSERT_EQUALS(q.getK(), 0.0);
  }

  void test_ConstructReal(void)
  {
    Quaternion q(5.0);
    TS_ASSERT_EQUALS(q.getReal(), 5.0);
    TS_ASSERT_EQUALS(q.getI(), 0.0);
    TS_ASSERT_EQUALS(q.getJ(), 0.0);
    TS_ASSERT_EQUALS(q.getK(), 0.0);
  }

  void test_ConstructRealInt(void)
  {
    int real = 5;
    Quaternion q(real);
    TS_ASSERT_EQUALS(q.getReal(), real);
    TS_ASSERT_EQUALS(q.getI(), 0.0);
    TS_ASSERT_EQUALS(q.getJ(), 0.0);
    TS_ASSERT_EQUALS(q.getK(), 0.0);
  }

  void test_ConstructImaginary(void)
  {
    Quaternion q(5.0, 2.0, 4.5, 8.9);
    TS_ASSERT_EQUALS(q.getReal(), 5.0);
    TS_ASSERT_EQUALS(q.getI(), 2.0);
    TS_ASSERT_EQUALS(q.getJ(), 4.5);
    TS_ASSERT_EQUALS(q.getK(), 8.9);
  }

  void test_Assignment(void)
  {
    Quaternion q1(5.0, 2.0, 4.5, 8.9);
    Quaternion q2(16.0, 2.5, 8.3, 6.7);
    q2 = q1;
    TS_ASSERT_EQUALS(q2.getReal(), 5.0);
    TS_ASSERT_EQUALS(q2.getI(), 2.0);
    TS_ASSERT_EQUALS(q2.getJ(), 4.5);
    TS_ASSERT_EQUALS(q2.getK(), 8.9);
  }

  void test_Equality(void)
  {
    Quaternion q1(5.0, 2.0, 4.5, 8.9);
    Quaternion q2(16.0, 2.5, 8.3, 6.7);
    Quaternion q3(5.0, 2.0, 4.5, 8.9);
    TS_ASSERT_EQUALS(q1, q3);
    TS_ASSERT_DIFFERS(q1, q2);
  }

  void test_Magnitude(void)
  {
    Quaternion q(5.0, 2.0, 4.5, 8.9);
    TS_ASSERT_DELTA(q.magnitude(), 11.3340, TH);
  }

  void test_Addition(void)
  {
    Quaternion q1(5.0, 2.0, 4.5, 8.9);
    Quaternion q2(16.0, 2.5, 8.3, 6.7);
    Quaternion q3 = q1 + q2;
    TS_ASSERT_DELTA(q3.getReal(), 21.0, TH);
    TS_ASSERT_DELTA(q3.getI(), 4.5, TH);
    TS_ASSERT_DELTA(q3.getJ(), 12.8, TH);
    TS_ASSERT_DELTA(q3.getK(), 15.6, TH);
  }

  void test_Subtraction(void)
  {
    Quaternion q1(5.0, 2.0, 4.5, 8.9);
    Quaternion q2(16.0, 2.5, 8.3, 6.7);
    Quaternion q3 = q1 - q2;
    TS_ASSERT_DELTA(q3.getReal(), -11.0, TH);
    TS_ASSERT_DELTA(q3.getI(), -0.5, TH);
    TS_ASSERT_DELTA(q3.getJ(), -3.8, TH);
    TS_ASSERT_DELTA(q3.getK(), 2.2, TH);
  }

  void test_Multiplicaion(void)
  {
    Quaternion q1(5.0, 2.0, 4.5, 8.9);
    Quaternion q2(16.0, 2.5, 8.3, 6.7);
    Quaternion q3 = q1 * q2;
    TS_ASSERT_DELTA(q3.getReal(), -21.98, TH);
    TS_ASSERT_DELTA(q3.getI(), 0.78, TH);
    TS_ASSERT_DELTA(q3.getJ(), 122.35, TH);
    TS_ASSERT_DELTA(q3.getK(), 181.25, TH);
  }
};
