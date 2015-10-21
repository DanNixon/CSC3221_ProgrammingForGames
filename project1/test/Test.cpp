#include <cstdlib>
#include <iostream>

#include <sstream>
#include <stdexcept>

#include "Vector3DStack.h"
#include "Quaternion.h"

#define TH 0.0001

size_t g_testsCount = 0;
size_t g_testsPassed = 0;

/* Macro for testing that an expression is true. */
#define TS_ASSERT(expr)                                                        \
  {                                                                            \
    g_testsCount++;                                                            \
    if (expr)                                                                  \
      g_testsPassed++;                                                         \
  }

/* Macro for testing that two values are equal to each other. */
#define TS_ASSERT_EQUALS(a, b)                                                 \
  {                                                                            \
    g_testsCount++;                                                            \
    if (a == b)                                                                \
      g_testsPassed++;                                                         \
  }

/* Macro for testing that two values are not equal to each other. */
#define TS_ASSERT_DIFFERS(a, b)                                                \
  {                                                                            \
    g_testsCount++;                                                            \
    if (!(a == b))                                                             \
      g_testsPassed++;                                                         \
  }

/* Macro for testing two numerical values are close to each other within a */
/* tolerance. */
#define TS_ASSERT_DELTA(a, b, th)                                              \
  {                                                                            \
    g_testsCount++;                                                            \
    if (abs(a - b) <= th)                                                      \
      g_testsPassed++;                                                         \
  }

/* Macro for testing an expression throws a certain type of exception. */
#define TS_ASSERT_THROWS(expr, type)                                           \
  {                                                                            \
    g_testsCount++;                                                            \
    try                                                                        \
    {                                                                          \
      expr;                                                                    \
    }                                                                          \
    catch (type &)                                                             \
    {                                                                          \
      g_testsPassed++;                                                         \
    }                                                                          \
    catch (...)                                                                \
    {                                                                          \
    }                                                                          \
  }

/* Test Function */
void test_Vector3DStack_Default(void)
{
  Vector3DStack v;
  TS_ASSERT_EQUALS(v.getX(), 0.0);
  TS_ASSERT_EQUALS(v.getY(), 0.0);
  TS_ASSERT_EQUALS(v.getZ(), 0.0);
}

void test_Vector3DStack_CreateWithValues(void)
{
  Vector3DStack v(1.0, 6.0, 3.0);
  TS_ASSERT_EQUALS(v.getX(), 1.0);
  TS_ASSERT_EQUALS(v.getY(), 6.0);
  TS_ASSERT_EQUALS(v.getZ(), 3.0);
}

void test_Vector3DStack_CreateCopyConstructior(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(v1);

  TS_ASSERT_EQUALS(v2.getX(), 1.0);
  TS_ASSERT_EQUALS(v2.getY(), 6.0);
  TS_ASSERT_EQUALS(v2.getZ(), 3.0);
}

void test_Vector3DStack_Assignment(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(3.0, 6.0, 8.0);

  v2 = v1;

  TS_ASSERT_EQUALS(v2.getX(), 1.0);
  TS_ASSERT_EQUALS(v2.getY(), 6.0);
  TS_ASSERT_EQUALS(v2.getZ(), 3.0);
}

void test_Vector3DStack_Equality(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(3.0, 6.0, 8.0);
  Vector3DStack v3(1.0, 6.0, 3.0);

  TS_ASSERT(v1 == v3);
  TS_ASSERT(!(v1 == v2));
}

void test_Vector3DStack_Inquality(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(3.0, 6.0, 8.0);
  Vector3DStack v3(1.0, 6.0, 3.0);

  TS_ASSERT(!(v1 != v3));
  TS_ASSERT(v1 != v2);
}

void test_Vector3DStack_Addition(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(5.0, 2.0, 9.0);
  Vector3DStack v3 = v1 + v2;
  TS_ASSERT_EQUALS(v3.getX(), 6.0);
  TS_ASSERT_EQUALS(v3.getY(), 8.0);
  TS_ASSERT_EQUALS(v3.getZ(), 12.0);
}

void test_Vector3DStack_Subtraction(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(5.0, 2.0, 9.0);
  Vector3DStack v3 = v1 - v2;
  TS_ASSERT_EQUALS(v3.getX(), -4.0);
  TS_ASSERT_EQUALS(v3.getY(), 4.0);
  TS_ASSERT_EQUALS(v3.getZ(), -6.0);
}

void test_Vector3DStack_ScalarMultiplication(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2 = v1 * 6.0;
  TS_ASSERT_EQUALS(v2.getX(), 6.0);
  TS_ASSERT_EQUALS(v2.getY(), 36.0);
  TS_ASSERT_EQUALS(v2.getZ(), 18.0);
}

void test_Vector3DStack_ScalarDivision(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2 = v1 / 2.0;
  TS_ASSERT_EQUALS(v2.getX(), 0.5);
  TS_ASSERT_EQUALS(v2.getY(), 3.0);
  TS_ASSERT_EQUALS(v2.getZ(), 1.5);
}

void test_Vector3DStack_ScalarDivisionByZero(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  TS_ASSERT_THROWS(Vector3DStack v2 = v1 / 0.0,
                   std::runtime_error);
}

void test_Vector3DStack_Magnitude(void)
{
  Vector3DStack v(1.0, 6.0, 3.0);
  TS_ASSERT_DELTA(v.magnitude(), 6.7823, TH);
}

void test_Vector3DStack_DotProduct(void)
{
  Vector3DStack v1(1, 6, 3);
  Vector3DStack v2(5, 2, 9);
  double dotProd = v1 * v2;
  TS_ASSERT_EQUALS(dotProd, 44);
}

void test_Vector3DStack_CrossProduct(void)
{
  Vector3DStack v1(1.0, 6.0, 3.0);
  Vector3DStack v2(5.0, 2.0, 9.0);
  Vector3DStack v3 = v1 % v2;
  TS_ASSERT_EQUALS(v3.getX(), 48.0);
  TS_ASSERT_EQUALS(v3.getY(), 6.0);
  TS_ASSERT_EQUALS(v3.getZ(), -28.0);
}

void test_Vector3DStack_UnitVector(void)
{
  Vector3DStack v(1.0, 6.0, 3.0);
  Vector3DStack unit = v.getUnitVector();

  TS_ASSERT_EQUALS(unit.magnitude(), 1.0);
  TS_ASSERT_DELTA(unit.getX(), 0.1474, TH);
  TS_ASSERT_DELTA(unit.getY(), 0.8846, TH);
  TS_ASSERT_DELTA(unit.getZ(), 0.4423, TH);
}

void test_Vector3DStack_StreamOutput(void)
{
  Vector3DStack v(1.0, 6.0, 3.0);
  std::stringstream stream;
  stream << v;
  TS_ASSERT_EQUALS(stream.str(), "[1,6,3]");
}

void test_Vector3DStack_StreamInput(void)
{
  // Create stream with valid string
  std::stringstream stream;
  stream << "[1.0,6.0,3.0]";

  // Read the stream
  Vector3DStack v;
  stream >> v;

  // Validate results
  TS_ASSERT_EQUALS(v.getX(), 1.0);
  TS_ASSERT_EQUALS(v.getY(), 6.0);
  TS_ASSERT_EQUALS(v.getZ(), 3.0);
}

void test_Quaternion_Default(void)
{
  Quaternion q;
  TS_ASSERT_EQUALS(q.getReal(), 1.0);
  TS_ASSERT_EQUALS(q.getI(), 0.0);
  TS_ASSERT_EQUALS(q.getJ(), 0.0);
  TS_ASSERT_EQUALS(q.getK(), 0.0);
}

void test_Quaternion_ConstructReal(void)
{
  Quaternion q(5.0);
  TS_ASSERT_EQUALS(q.getReal(), 5.0);
  TS_ASSERT_EQUALS(q.getI(), 0.0);
  TS_ASSERT_EQUALS(q.getJ(), 0.0);
  TS_ASSERT_EQUALS(q.getK(), 0.0);
}

void test_Quaternion_ConstructRealInt(void)
{
  int real = 5;
  Quaternion q(real);
  TS_ASSERT_EQUALS(q.getReal(), real);
  TS_ASSERT_EQUALS(q.getI(), 0.0);
  TS_ASSERT_EQUALS(q.getJ(), 0.0);
  TS_ASSERT_EQUALS(q.getK(), 0.0);
}

void test_Quaternion_ConstructImaginary(void)
{
  Quaternion q(5.0, 2.0, 4.5, 8.9);
  TS_ASSERT_EQUALS(q.getReal(), 5.0);
  TS_ASSERT_EQUALS(q.getI(), 2.0);
  TS_ASSERT_EQUALS(q.getJ(), 4.5);
  TS_ASSERT_EQUALS(q.getK(), 8.9);
}

void test_Quaternion_Assignment(void)
{
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
  Quaternion q1(5.0, 2.0, 4.5, 8.9);
  Quaternion q2(16.0, 2.5, 8.3, 6.7);
  Quaternion q3(5.0, 2.0, 4.5, 8.9);

  TS_ASSERT(q1 == q3);
  TS_ASSERT(!(q1 == q2));
}

void test_Quaternion_Inequality(void)
{
  Quaternion q1(5.0, 2.0, 4.5, 8.9);
  Quaternion q2(16.0, 2.5, 8.3, 6.7);
  Quaternion q3(5.0, 2.0, 4.5, 8.9);

  TS_ASSERT(!(q1 != q3));
  TS_ASSERT(q1 != q2);
}

void test_Quaternion_Magnitude(void)
{
  Quaternion q(5.0, 2.0, 4.5, 8.9);
  TS_ASSERT_DELTA(q.magnitude(), 11.3340, TH);
}

void test_Quaternion_Addition(void)
{
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
  Quaternion q1(5.0, 2.0, 4.5, 8.9);
  Quaternion q2(16.0, 2.5, 8.3, 6.7);
  Quaternion q3 = q1 * q2;
  TS_ASSERT_DELTA(q3.getReal(), -21.98, TH);
  TS_ASSERT_DELTA(q3.getI(), 0.78, TH);
  TS_ASSERT_DELTA(q3.getJ(), 122.35, TH);
  TS_ASSERT_DELTA(q3.getK(), 181.25, TH);
}

void test_Quaternion_StreamOutput(void)
{
  Quaternion q(5.0, 2.0, 4.5, 8.9);
  std::stringstream stream;
  stream << q;
  TS_ASSERT_EQUALS(stream.str(), "[5,2,4.5,8.9]");
}

void test_Quaternion_StreamInput(void)
{
  // Create stream with valid string
  std::stringstream stream;
  stream << "[5.0,2.0,4.5,8.9]";

  // Read the stream
  Quaternion q;
  stream >> q;

  // Validate results
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
  test_Vector3DStack_Addition();
  test_Vector3DStack_Subtraction();
  test_Vector3DStack_ScalarMultiplication();
  test_Vector3DStack_ScalarDivision();
  test_Vector3DStack_ScalarDivisionByZero();
  test_Vector3DStack_Magnitude();
  test_Vector3DStack_DotProduct();
  test_Vector3DStack_CrossProduct();
  test_Vector3DStack_UnitVector();
  test_Vector3DStack_StreamOutput();
  test_Vector3DStack_StreamInput();
  test_Quaternion_Default();
  test_Quaternion_ConstructReal();
  test_Quaternion_ConstructRealInt();
  test_Quaternion_ConstructImaginary();
  test_Quaternion_Assignment();
  test_Quaternion_Equality();
  test_Quaternion_Inequality();
  test_Quaternion_Magnitude();
  test_Quaternion_Addition();
  test_Quaternion_Subtraction();
  test_Quaternion_Multiplicaion();
  test_Quaternion_StreamOutput();
  test_Quaternion_StreamInput();

  /* Output the test results */
  std::cout << "Test assertions passed: " << g_testsPassed << "/"
            << g_testsCount << " (" << ((100 * g_testsPassed) / g_testsCount)
            << "%)" << std::endl;

  /* Warn on failure */
  if (g_testsPassed < g_testsCount)
    std::cout << "There are test failures!" << std::endl;

  /* Return 0 for no failed tests, or 1 if at least one test failed */
  return (g_testsPassed != g_testsCount);
}
