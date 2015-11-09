#include <cstdlib>
#include <iostream>

#include <sstream>
#include <stdexcept>
#include <cmath>

#include "Vector3DStack.h"
#include "Quaternion.h"

#define TH 0.0001

size_t g_testsCount = 0;
size_t g_assertionCount = 0;
size_t g_assertionPassed = 0;

/* Macro for incrementing the test count at the start of a test function */
#define TEST_FUNC g_testsCount++;

/* Macro for testing that an expression is true. */
#define TS_ASSERT(expr)                                                        \
  {                                                                            \
    g_assertionCount++;                                                            \
    if (expr)                                                                  \
      g_assertionPassed++;                                                         \
  }

/* Macro for testing that two values are equal to each other. */
#define TS_ASSERT_EQUALS(a, b)                                                 \
  {                                                                            \
    g_assertionCount++;                                                            \
    if (a == b)                                                                \
      g_assertionPassed++;                                                         \
  }

/* Macro for testing that two values are not equal to each other. */
#define TS_ASSERT_DIFFERS(a, b)                                                \
  {                                                                            \
    g_assertionCount++;                                                            \
    if (!(a == b))                                                             \
      g_assertionPassed++;                                                         \
  }

/* Macro for testing two numerical values are close to each other within a */
/* tolerance. */
#define TS_ASSERT_DELTA(a, b, th)                                              \
  {                                                                            \
    g_assertionCount++;                                                            \
    if (abs(a - b) <= th)                                                      \
      g_assertionPassed++;                                                         \
  }

/* Macro for testing an expression throws a certain type of exception. */
#define TS_ASSERT_THROWS(expr, type)                                           \
  {                                                                            \
    g_assertionCount++;                                                            \
    try                                                                        \
    {                                                                          \
      expr;                                                                    \
    }                                                                          \
    catch (type &)                                                             \
    {                                                                          \
      g_assertionPassed++;                                                         \
    }                                                                          \
    catch (...)                                                                \
    {                                                                          \
    }                                                                          \
  }

/* Test Functions */
void test_Vector3DStack_Default(void)
{
  TEST_FUNC

  Vector3DStack v;
  TS_ASSERT_EQUALS(v.getX(), 0.0);
  TS_ASSERT_EQUALS(v.getY(), 0.0);
  TS_ASSERT_EQUALS(v.getZ(), 0.0);
}

void test_Vector3DStack_CreateWithValues(void)
{
  TEST_FUNC

  Vector3DStack v(1.0, 6.0, 3.0);
  TS_ASSERT_EQUALS(v.getX(), 1.0);
  TS_ASSERT_EQUALS(v.getY(), 6.0);
  TS_ASSERT_EQUALS(v.getZ(), 3.0);
}

void test_Vector3DStack_CreateCopyConstructior(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(v1);

  TS_ASSERT_EQUALS(v2.getX(), 1.0);
  TS_ASSERT_EQUALS(v2.getY(), 6.0);
  TS_ASSERT_EQUALS(v2.getZ(), 3.0);
}

void test_Vector3DStack_Assignment(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(3.0, 6.0, 8.0);

  v2 = v1;

  TS_ASSERT_EQUALS(v2.getX(), 1.0);
  TS_ASSERT_EQUALS(v2.getY(), 6.0);
  TS_ASSERT_EQUALS(v2.getZ(), 3.0);
}

void test_Vector3DStack_Equality(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(3.0, 6.0, 8.0);
  Vector3DStack v3(1.0, 6.0, 3.0);

  TS_ASSERT(v1 == v3);
  TS_ASSERT(!(v1 == v2));
}

void test_Vector3DStack_Inquality(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(3.0, 6.0, 8.0);
  Vector3DStack v3(1.0, 6.0, 3.0);

  TS_ASSERT(!(v1 != v3));
  TS_ASSERT(v1 != v2);
}

void test_Vector3DStack_SetX(void)
{
  TEST_FUNC

  Vector3DStack v;
  v.setX(1.0);
  TS_ASSERT_EQUALS(v.getX(), 1.0);
  TS_ASSERT_EQUALS(v.getY(), 0.0);
  TS_ASSERT_EQUALS(v.getZ(), 0.0);
}

void test_Vector3DStack_SetY(void)
{
  TEST_FUNC

  Vector3DStack v;
  v.setY(1.0);
  TS_ASSERT_EQUALS(v.getX(), 0.0);
  TS_ASSERT_EQUALS(v.getY(), 1.0);
  TS_ASSERT_EQUALS(v.getZ(), 0.0);
}

void test_Vector3DStack_SetZ(void)
{
  TEST_FUNC

  Vector3DStack v;
  v.setZ(1.0);
  TS_ASSERT_EQUALS(v.getX(), 0.0);
  TS_ASSERT_EQUALS(v.getY(), 0.0);
  TS_ASSERT_EQUALS(v.getZ(), 1.0);
}

void test_Vector3DStack_Addition(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(5.0, 2.0, 9.0);
  Vector3DStack v3 = v1 + v2;
  TS_ASSERT_EQUALS(v3.getX(), 6.0);
  TS_ASSERT_EQUALS(v3.getY(), 8.0);
  TS_ASSERT_EQUALS(v3.getZ(), 12.0);
}

void test_Vector3DStack_Subtraction(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(5.0, 2.0, 9.0);
  Vector3DStack v3 = v1 - v2;
  TS_ASSERT_EQUALS(v3.getX(), -4.0);
  TS_ASSERT_EQUALS(v3.getY(), 4.0);
  TS_ASSERT_EQUALS(v3.getZ(), -6.0);
}

void test_Vector3DStack_ScalarMultiplication(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2 = v1 * 6.0;
  TS_ASSERT_EQUALS(v2.getX(), 6.0);
  TS_ASSERT_EQUALS(v2.getY(), 36.0);
  TS_ASSERT_EQUALS(v2.getZ(), 18.0);
}

void test_Vector3DStack_ScalarDivision(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2 = v1 / 2.0;
  TS_ASSERT_EQUALS(v2.getX(), 0.5);
  TS_ASSERT_EQUALS(v2.getY(), 3.0);
  TS_ASSERT_EQUALS(v2.getZ(), 1.5);
}

void test_Vector3DStack_ScalarDivisionByZero(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  TS_ASSERT_THROWS(Vector3DStack v2 = v1 / 0.0,
                   std::runtime_error);
}

void test_Vector3DStack_Magnitude(void)
{
  TEST_FUNC

  Vector3DStack v(1.0, 6.0, 3.0);
  TS_ASSERT_DELTA(v.magnitude(), 6.7823, TH);
}

void test_Vector3DStack_DotProduct(void)
{
  TEST_FUNC

  Vector3DStack v1(1, 6, 3);
  Vector3DStack v2(5, 2, 9);
  double dotProd = v1 * v2;
  TS_ASSERT_EQUALS(dotProd, 44);
}

void test_Vector3DStack_CrossProduct(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(5.0, 2.0, 9.0);
  Vector3DStack v3 = v1 % v2;
  TS_ASSERT_EQUALS(v3.getX(), 48.0);
  TS_ASSERT_EQUALS(v3.getY(), 6.0);
  TS_ASSERT_EQUALS(v3.getZ(), -28.0);
}

void test_Vector3DStack_UnitVector(void)
{
  TEST_FUNC

  Vector3DStack v(1.0, 6.0, 3.0);
  Vector3DStack unit = v.getUnitVector();

  TS_ASSERT_EQUALS(unit.magnitude(), 1.0);
  TS_ASSERT_DELTA(unit.getX(), 0.1474, TH);
  TS_ASSERT_DELTA(unit.getY(), 0.8846, TH);
  TS_ASSERT_DELTA(unit.getZ(), 0.4423, TH);
}

void test_Vector3DStack_OrthogonalUnitVector(void)
{
  TEST_FUNC

  Vector3DStack v1(1.0, 0.0, 1.0);
  Vector3DStack v2(0.0, 1.0, 1.0);
  Vector3DStack v3 = v1.getOrthogonalUnitVector(v2);

  TS_ASSERT_EQUALS(v3.magnitude(), 1.0);
  TS_ASSERT_DELTA(v3.getX(), -0.57735, TH);
  TS_ASSERT_DELTA(v3.getY(), -0.57735, TH);
  TS_ASSERT_DELTA(v3.getZ(), 0.57735, TH);
}

void test_Vector3DStack_IndexOperator(void)
{
  TEST_FUNC

  Vector3DStack v(1.0, 6.0, 3.0);
  TS_ASSERT_DELTA(v[0], 1.0, TH);
  TS_ASSERT_DELTA(v[1], 6.0, TH);
  TS_ASSERT_DELTA(v[2], 3.0, TH);
}

void test_Vector3DStack_IndexOperatorOutOfRange(void)
{
  TEST_FUNC

  Vector3DStack v(1.0, 6.0, 3.0);
  TS_ASSERT_THROWS(v[3], std::runtime_error);
}

void test_Vector3DStack_IndexOperatorSet(void)
{
  TEST_FUNC

  Vector3DStack v;
  v[0] = 1.0;
  v[1] = 6.0;
  v[2] = 3.0;
  TS_ASSERT_DELTA(v[0], 1.0, TH);
  TS_ASSERT_DELTA(v[1], 6.0, TH);
  TS_ASSERT_DELTA(v[2], 3.0, TH);
}

void test_Vector3DStack_IndexOperatorSetOutOfRange(void)
{
  TEST_FUNC

  Vector3DStack v(1.0, 6.0, 3.0);
  TS_ASSERT_THROWS(v[3] = 12.0, std::runtime_error);
  /* Values should not change */
  TS_ASSERT_DELTA(v.getX(), 1.0, TH);
  TS_ASSERT_DELTA(v.getY(), 6.0, TH);
  TS_ASSERT_DELTA(v.getZ(), 3.0, TH);
}

void test_Vector3DStack_StreamOutput(void)
{
  TEST_FUNC

  Vector3DStack v(1.0, 6.0, 3.0);
  std::stringstream stream;
  stream << v;
  TS_ASSERT_EQUALS(stream.str(), "[1,6,3]");
}

void test_Vector3DStack_StreamInput(void)
{
  TEST_FUNC

  /* Create stream with valid string */
  std::stringstream stream;
  stream << "[1.0,6.0,3.0]";

  /* Read the stream */
  Vector3DStack v;
  stream >> v;

  /* Validate results */
  TS_ASSERT_EQUALS(v.getX(), 1.0);
  TS_ASSERT_EQUALS(v.getY(), 6.0);
  TS_ASSERT_EQUALS(v.getZ(), 3.0);
}

void test_Quaternion_Default(void)
{
  TEST_FUNC

  Quaternion q;
  TS_ASSERT_EQUALS(q.getReal(), 1.0);
  TS_ASSERT_EQUALS(q.getI(), 0.0);
  TS_ASSERT_EQUALS(q.getJ(), 0.0);
  TS_ASSERT_EQUALS(q.getK(), 0.0);
}

void test_Quaternion_ConstructReal(void)
{
  TEST_FUNC

  Quaternion q(5.0);
  TS_ASSERT_EQUALS(q.getReal(), 5.0);
  TS_ASSERT_EQUALS(q.getI(), 0.0);
  TS_ASSERT_EQUALS(q.getJ(), 0.0);
  TS_ASSERT_EQUALS(q.getK(), 0.0);
}

void test_Quaternion_ConstructRealInt(void)
{
  TEST_FUNC

  int real = 5;
  Quaternion q(real);
  TS_ASSERT_EQUALS(q.getReal(), real);
  TS_ASSERT_EQUALS(q.getI(), 0.0);
  TS_ASSERT_EQUALS(q.getJ(), 0.0);
  TS_ASSERT_EQUALS(q.getK(), 0.0);
}

void test_Quaternion_ConstructImaginary(void)
{
  TEST_FUNC

  Quaternion q(5.0, 2.0, 4.5, 8.9);
  TS_ASSERT_EQUALS(q.getReal(), 5.0);
  TS_ASSERT_EQUALS(q.getI(), 2.0);
  TS_ASSERT_EQUALS(q.getJ(), 4.5);
  TS_ASSERT_EQUALS(q.getK(), 8.9);
}

void test_Quaternion_ConstructRotation(void)
{
  TEST_FUNC

  Vector3DStack axis(1.0, 1.0, 1.0);
  Quaternion q(90.0, axis);
  double c = 1.0 / sqrt(2.0);
  double s = c / sqrt(3.0);
  TS_ASSERT_DELTA(q.getReal(), c, TH);
  TS_ASSERT_DELTA(q.getI(), s, TH);
  TS_ASSERT_DELTA(q.getJ(), s, TH);
  TS_ASSERT_DELTA(q.getK(), s, TH);
}

void test_Quaternion_Assignment(void)
{
  TEST_FUNC

  Quaternion q1(5.0, 2.0, 4.5, 8.9);
  Quaternion q2(16.0, 2.5, 8.3, 6.7);
  q2 = q1;
  TS_ASSERT_EQUALS(q2.getReal(), 5.0);
  TS_ASSERT_EQUALS(q2.getI(), 2.0);
  TS_ASSERT_EQUALS(q2.getJ(), 4.5);
  TS_ASSERT_EQUALS(q2.getK(), 8.9);
}

void test_Quaternion_Equality(void)
{
  TEST_FUNC

  Quaternion q1(5.0, 2.0, 4.5, 8.9);
  Quaternion q2(16.0, 2.5, 8.3, 6.7);
  Quaternion q3(5.0, 2.0, 4.5, 8.9);

  TS_ASSERT(q1 == q3);
  TS_ASSERT(!(q1 == q2));
}

void test_Quaternion_Inequality(void)
{
  TEST_FUNC

  Quaternion q1(5.0, 2.0, 4.5, 8.9);
  Quaternion q2(16.0, 2.5, 8.3, 6.7);
  Quaternion q3(5.0, 2.0, 4.5, 8.9);

  TS_ASSERT(!(q1 != q3));
  TS_ASSERT(q1 != q2);
}

void test_Quaternion_SetReal(void)
{
  TEST_FUNC

  Quaternion q;
  q.setReal(10.0);
  TS_ASSERT_DELTA(q.getReal(), 10.0, TH);
  TS_ASSERT_DELTA(q.getI(), 0.0, TH);
  TS_ASSERT_DELTA(q.getJ(), 0.0, TH);
  TS_ASSERT_DELTA(q.getK(), 0.0, TH);
}

void test_Quaternion_SetI(void)
{
  TEST_FUNC

  Quaternion q;
  q.setI(1.0);
  TS_ASSERT_DELTA(q.getReal(), 1.0, TH);
  TS_ASSERT_DELTA(q.getI(), 1.0, TH);
  TS_ASSERT_DELTA(q.getJ(), 0.0, TH);
  TS_ASSERT_DELTA(q.getK(), 0.0, TH);
}

void test_Quaternion_SetJ(void)
{
  TEST_FUNC

  Quaternion q;
  q.setJ(1.0);
  TS_ASSERT_DELTA(q.getReal(), 1.0, TH);
  TS_ASSERT_DELTA(q.getI(), 0.0, TH);
  TS_ASSERT_DELTA(q.getJ(), 1.0, TH);
  TS_ASSERT_DELTA(q.getK(), 0.0, TH);
}

void test_Quaternion_SetK(void)
{
  TEST_FUNC

  Quaternion q;
  q.setK(1.0);
  TS_ASSERT_DELTA(q.getReal(), 1.0, TH);
  TS_ASSERT_DELTA(q.getI(), 0.0, TH);
  TS_ASSERT_DELTA(q.getJ(), 0.0, TH);
  TS_ASSERT_DELTA(q.getK(), 1.0, TH);
}

void test_Quaternion_Magnitude(void)
{
  TEST_FUNC

  Quaternion q(5.0, 2.0, 4.5, 8.9);
  TS_ASSERT_DELTA(q.magnitude(), 11.3340, TH);
}

void test_Quaternion_Addition(void)
{
  TEST_FUNC

  Quaternion q1(5.0, 2.0, 4.5, 8.9);
  Quaternion q2(16.0, 2.5, 8.3, 6.7);
  Quaternion q3 = q1 + q2;
  TS_ASSERT_DELTA(q3.getReal(), 21.0, TH);
  TS_ASSERT_DELTA(q3.getI(), 4.5, TH);
  TS_ASSERT_DELTA(q3.getJ(), 12.8, TH);
  TS_ASSERT_DELTA(q3.getK(), 15.6, TH);
}

void test_Quaternion_Subtraction(void)
{
  TEST_FUNC

  Quaternion q1(5.0, 2.0, 4.5, 8.9);
  Quaternion q2(16.0, 2.5, 8.3, 6.7);
  Quaternion q3 = q1 - q2;
  TS_ASSERT_DELTA(q3.getReal(), -11.0, TH);
  TS_ASSERT_DELTA(q3.getI(), -0.5, TH);
  TS_ASSERT_DELTA(q3.getJ(), -3.8, TH);
  TS_ASSERT_DELTA(q3.getK(), 2.2, TH);
}

void test_Quaternion_Multiplicaion(void)
{
  TEST_FUNC

  Quaternion q1(5.0, 2.0, 4.5, 8.9);
  Quaternion q2(16.0, 2.5, 8.3, 6.7);
  Quaternion q3 = q1 * q2;
  TS_ASSERT_DELTA(q3.getReal(), -21.98, TH);
  TS_ASSERT_DELTA(q3.getI(), 0.78, TH);
  TS_ASSERT_DELTA(q3.getJ(), 122.35, TH);
  TS_ASSERT_DELTA(q3.getK(), 181.25, TH);
}

void test_Quaternion_Conjugate(void)
{
  TEST_FUNC

  Quaternion q(5.0, 2.0, 4.5, 8.9);
  Quaternion conj = q.conjugate();
  TS_ASSERT_DELTA(conj.getReal(), 5.0, TH);
  TS_ASSERT_DELTA(conj.getI(), -2.0, TH);
  TS_ASSERT_DELTA(conj.getJ(), -4.5, TH);
  TS_ASSERT_DELTA(conj.getK(), -8.9, TH);
}

void test_Quaternion_Inverse(void)
{
  TEST_FUNC

  Quaternion q(5.0, 2.0, 4.5, 8.9);
  Quaternion inv = q.inverse();

  Quaternion r = q * inv;

  TS_ASSERT_DELTA(r.getReal(), 1.0, TH);
  TS_ASSERT_DELTA(r.getI(), 0.0, TH);
  TS_ASSERT_DELTA(r.getJ(), 0.0, TH);
  TS_ASSERT_DELTA(r.getK(), 0.0, TH);
}

void test_Quaternion_Rotation90DegY(void)
{
  TEST_FUNC

  Quaternion q(90.0, Vector3DStack(0.0, 1.0, 0.0));
  Vector3DStack v(1.0, 0.0, 0.0);
  v = q.rotateVector(v);
  TS_ASSERT_DELTA(v.getX(), 0.0, TH);
  TS_ASSERT_DELTA(v.getY(), 0.0, TH);
  TS_ASSERT_DELTA(v.getZ(), -1.0, TH);
}

void test_Quaternion_Rotation45DegZ(void)
{
  TEST_FUNC

  Quaternion q(45.0, Vector3DStack(0.0, 0.0, 1.0));
  Vector3DStack v(1.0, 0.0, 0.0);
  v = q.rotateVector(v);
  const double h = sqrt(2.0) / 2;
  TS_ASSERT_DELTA(v.getX(), h, TH);
  TS_ASSERT_DELTA(v.getY(), h, TH);
  TS_ASSERT_DELTA(v.getZ(), 0.0, TH);
}

void test_Quaternion_IndexOperator(void)
{
  TEST_FUNC

  Quaternion q(5.0, 2.0, 4.5, 8.9);
  TS_ASSERT_DELTA(q[0], 5.0, TH);
  TS_ASSERT_DELTA(q[1], 2.0, TH);
  TS_ASSERT_DELTA(q[2], 4.5, TH);
  TS_ASSERT_DELTA(q[3], 8.9, TH);
}

void test_Quaternion_IndexOperatorOutOfRange(void)
{
  TEST_FUNC

  Quaternion q(5.0, 2.0, 4.5, 8.9);
  TS_ASSERT_THROWS(q[4], std::runtime_error);
}

void test_Quaternion_IndexOperatorSet(void)
{
  TEST_FUNC

  Quaternion q;
  q[0] = 5.0;
  q[1] = 2.0;
  q[2] = 4.5;
  q[3] = 8.9;
  TS_ASSERT_DELTA(q[0], 5.0, TH);
  TS_ASSERT_DELTA(q[1], 2.0, TH);
  TS_ASSERT_DELTA(q[2], 4.5, TH);
  TS_ASSERT_DELTA(q[3], 8.9, TH);
}

void test_Quaternion_IndexOperatorSetOutOfRange(void)
{
  TEST_FUNC

  Quaternion q(5.0, 2.0, 4.5, 8.9);
  TS_ASSERT_THROWS(q[4] = 6.0, std::runtime_error);
  /* Values should not change */
  TS_ASSERT_DELTA(q.getReal(), 5.0, TH);
  TS_ASSERT_DELTA(q.getI(), 2.0, TH);
  TS_ASSERT_DELTA(q.getJ(), 4.5, TH);
  TS_ASSERT_DELTA(q.getK(), 8.9, TH);
}

void test_Quaternion_StreamOutput(void)
{
  TEST_FUNC

  Quaternion q(5.0, 2.0, 4.5, 8.9);
  std::stringstream stream;
  stream << q;
  TS_ASSERT_EQUALS(stream.str(), "[5,2,4.5,8.9]");
}

void test_Quaternion_StreamInput(void)
{
  TEST_FUNC

  /* Create stream with valid string */
  std::stringstream stream;
  stream << "[5.0,2.0,4.5,8.9]";

  /* Read the stream */
  Quaternion q;
  stream >> q;

  /* Validate results */
  TS_ASSERT_EQUALS(q.getReal(), 5.0);
  TS_ASSERT_EQUALS(q.getI(), 2.0);
  TS_ASSERT_EQUALS(q.getJ(), 4.5);
  TS_ASSERT_EQUALS(q.getK(), 8.9);
}
/* End of test functions */

int main()
{
  /* Test function calls */
  test_Vector3DStack_Default();
  test_Vector3DStack_CreateWithValues();
  test_Vector3DStack_CreateCopyConstructior();
  test_Vector3DStack_Assignment();
  test_Vector3DStack_Equality();
  test_Vector3DStack_Inquality();
  test_Vector3DStack_SetX();
  test_Vector3DStack_SetY();
  test_Vector3DStack_SetZ();
  test_Vector3DStack_Addition();
  test_Vector3DStack_Subtraction();
  test_Vector3DStack_ScalarMultiplication();
  test_Vector3DStack_ScalarDivision();
  test_Vector3DStack_ScalarDivisionByZero();
  test_Vector3DStack_Magnitude();
  test_Vector3DStack_DotProduct();
  test_Vector3DStack_CrossProduct();
  test_Vector3DStack_UnitVector();
  test_Vector3DStack_OrthogonalUnitVector();
  test_Vector3DStack_IndexOperator();
  test_Vector3DStack_IndexOperatorOutOfRange();
  test_Vector3DStack_IndexOperatorSet();
  test_Vector3DStack_IndexOperatorSetOutOfRange();
  test_Vector3DStack_StreamOutput();
  test_Vector3DStack_StreamInput();
  test_Quaternion_Default();
  test_Quaternion_ConstructReal();
  test_Quaternion_ConstructRealInt();
  test_Quaternion_ConstructImaginary();
  test_Quaternion_ConstructRotation();
  test_Quaternion_Assignment();
  test_Quaternion_Equality();
  test_Quaternion_Inequality();
  test_Quaternion_SetReal();
  test_Quaternion_SetI();
  test_Quaternion_SetJ();
  test_Quaternion_SetK();
  test_Quaternion_Magnitude();
  test_Quaternion_Addition();
  test_Quaternion_Subtraction();
  test_Quaternion_Multiplicaion();
  test_Quaternion_Conjugate();
  test_Quaternion_IndexOperator();
  test_Quaternion_IndexOperatorOutOfRange();
  test_Quaternion_IndexOperatorSet();
  test_Quaternion_IndexOperatorSetOutOfRange();
  test_Quaternion_Inverse();
  test_Quaternion_Rotation90DegY();
  test_Quaternion_Rotation45DegZ();
  test_Quaternion_StreamOutput();
  test_Quaternion_StreamInput();

  /* Output the test results */
  std::cout << "Number of test functions: " << g_testsCount << std::endl
            << "Test assertions passed: " << g_assertionPassed << "/"
            << g_assertionCount << " (" << ((100 * g_assertionPassed) / g_assertionCount)
            << "%)" << std::endl;

  /* Warn on failure */
  if (g_assertionPassed < g_assertionCount)
    std::cout << "There are test failures!" << std::endl;

  /* Return 0 for no failed tests, or 1 if at least one test failed */
  return (g_assertionPassed != g_assertionCount);
}
