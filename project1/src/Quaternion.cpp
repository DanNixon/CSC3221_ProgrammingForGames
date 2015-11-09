#include "Quaternion.h"

#include <cmath>
#include <stdexcept>
#include "Vector3DStack.h"

/*
 * Optimisation notes
 *
 * All non primitive types are passed by const reference to avoid unnecessary
 * copying (i.e. reference) but still avoid changing the original (i.e. const).
 *
 * Passing by reference is not done for primitive types as this causes aliasing
 * which prevents the compiler optimisation doing the full extent of
 * optimisation.
 */

/**
 * Construct a quaternion with a default value of 1.
 */
Quaternion::Quaternion()
    : m_w(1.0)
    , m_i(0.0)
    , m_j(0.0)
    , m_k(0.0)
{
}

/**
 * Construct a real valued quaternion.
 *
 * Note: casting from integer to double is implicity, so this constructor
 * covers the fourth bullet point in the spec.
 *
 * @param w Real value
 */
Quaternion::Quaternion(const double w)
    : m_w(w)
    , m_i(0.0)
    , m_j(0.0)
    , m_k(0.0)
{
}

/**
 * Construct an imaginary valued quaternion.
 *
 * @param w Real value
 * @param i Coefficient of i
 * @param j Coefficient of j
 * @param k Coefficient of k
 */
Quaternion::Quaternion(const double w, const double i, const double j,
                       const double k)
    : m_w(w)
    , m_i(i)
    , m_j(j)
    , m_k(k)
{
}

/**
 * Construct a quaternion to represent a rotation in a given axis.
 *
 * @param angle Angle in degrees.
 * @param axis Vector defining axit to rotate in
 */
Quaternion::Quaternion(const double angle, const Vector3DStack &axis)
{
  const double DEG_2_RAD = 3.1415 / 180.0;
  m_w = cos(0.5 * angle * DEG_2_RAD);
  const double s = sin(0.5 * angle * DEG_2_RAD);
  Vector3DStack temp = axis.getUnitVector();
  m_i = s * temp.getX();
  m_j = s * temp.getY();
  m_k = s * temp.getZ();
}

/**
 * Construct a quaternion using the values of another.
 *
 * @param rhs Quaternion from which to take values
 */
Quaternion::Quaternion(const Quaternion &other)
    : m_w(other.m_w)
    , m_i(other.m_i)
    , m_j(other.m_j)
    , m_k(other.m_k)
{
}

/**
 * Destructor
 */
Quaternion::~Quaternion()
{
}

/**
 * Assign this quaternion the values of another.
 *
 * @param rhs Quaternion from which to take values
 */
void Quaternion::operator=(const Quaternion &rhs)
{
  m_w = rhs.m_w;
  m_i = rhs.m_i;
  m_j = rhs.m_j;
  m_k = rhs.m_k;
}

/**
 * Check for equality between this quaternion and another.
 *
 * @param rhs Other quaternion to compare to
 * @return True of values are equal
 */
bool Quaternion::operator==(const Quaternion &rhs) const
{
  return (m_w == rhs.m_w && m_i == rhs.m_i && m_j == rhs.m_j && m_k == rhs.m_k);
}

/**
 * Check for inequality between this quaternion and another.
 *
 * @param rhs Other quaternion to compare to
 * @return True if values are not equal
 */
bool Quaternion::operator!=(const Quaternion &rhs) const
{
  return !operator==(rhs);
}

/**
 * Sets the real part of the quaternion.
 *
 * @param w Real part
 */
void Quaternion::setReal(double w)
{
  m_w = w;
}

/**
 * Return the real part of the quaternion.
 *
 * @param Real part
 */
double Quaternion::getReal() const
{
  return m_w;
}

/**
 * Sets the i imaginary part of the quaternion.
 *
 * @param i Imaginary part
 */
void Quaternion::setI(double i)
{
  m_i = i;
}

/**
 * Return the i imaginary part of the quaternion.
 *
 * @return Coefficient of i
 */
double Quaternion::getI() const
{
  return m_i;
}

/**
 * Sets the j imaginary part of the quaternion.
 *
 * @param j Imaginary part
 */
void Quaternion::setJ(double j)
{
  m_j = j;
}

/**
 * Return the j imaginary part of the quaternion.
 *
 * @return Coefficient of j
 */
double Quaternion::getJ() const
{
  return m_j;
}

/**
 * Sets the k imaginary part of the quaternion.
 *
 * @param k Imaginary part
 */
void Quaternion::setK(double k)
{
  m_k = k;
}

/**
 * Return the k imaginary part of the quaternion.
 *
 * @return Coefficient of k
 */
double Quaternion::getK() const
{
  return m_k;
}

/**
 * Calculate the magnitude (length) of the quaternion.
 *
 * @return Magnitude
 */
double Quaternion::magnitude() const
{
  return sqrt(m_w * m_w + m_i * m_i + m_j * m_j + m_k * m_k);
}

/**
 * Calculate the sum of two quaternions.
 *
 * @param rhs Quaternion to add to the LHS
 * @return Sum of quaternions
 */
Quaternion Quaternion::operator+(const Quaternion &rhs) const
{
  return Quaternion(m_w + rhs.m_w, m_i + rhs.m_i, m_j + rhs.m_j, m_k + rhs.m_k);
}

/**
 * Subtract two quaternions.
 *
 * @param rhs Quaternion to subtract from the LHS
 * @return Subtraction of quaternions
 */
Quaternion Quaternion::operator-(const Quaternion &rhs) const
{
  return Quaternion(m_w - rhs.m_w, m_i - rhs.m_i, m_j - rhs.m_j, m_k - rhs.m_k);
}

/**
 * Calculate the product of two quaternions.
 *
 * @param rhs Quaternion to multiply by
 * @return Product of quaternions
 */
Quaternion Quaternion::operator*(const Quaternion &rhs) const
{
  double w = m_w * rhs.m_w - m_i * rhs.m_i - m_j * rhs.m_j - m_k * rhs.m_k;
  double i = m_w * rhs.m_i + rhs.m_w * m_i + m_j * rhs.m_k - rhs.m_j * m_k;
  double j = m_w * rhs.m_j + rhs.m_w * m_j - m_i * rhs.m_k + m_k * rhs.m_i;
  double k = m_w * rhs.m_k + rhs.m_w * m_k + m_i * rhs.m_j - rhs.m_i * m_j;

  return Quaternion(w, i, j, k);
}

/**
 * Return elements of the quaternion by index operator.
 *
 * For reading only.
 *
 * @param index Index accessed
 * @param Quaternion component
 */
double Quaternion::operator[](const int index) const
{
  switch(index)
  {
    case 0:
      return m_w;
    case 1:
      return m_i;
    case 2:
      return m_j;
    case 3:
      return m_k;
    default:
      throw std::runtime_error("Quaternion index out of range");
  }
}

/**
 * Return elements of the quaternion by index operator.
 *
 * For reading and writing.
 *
 * @param index Index accessed
 * @param Quaternion component
 */
double &Quaternion::operator[](const int index)
{
  switch(index)
  {
    case 0:
      return m_w;
    case 1:
      return m_i;
    case 2:
      return m_j;
    case 3:
      return m_k;
    default:
      throw std::runtime_error("Quaternion index out of range");
  }
}

/**
 * Returns the complex conjugate of this quaternion.
 *
 * @return Complex conjugate
 */
Quaternion Quaternion::conjugate() const
{
  return Quaternion(m_w, -m_i, -m_j, -m_k);
}

/**
 * Compute the inverse of this quaternion.
 *
 * @return Inverse quaternion
 */
Quaternion Quaternion::inverse() const
{
  Quaternion q = conjugate();

  double m = q.magnitude();
  m *= m;

  if (m == 0.0)
    m = 1.0;
  else
    m = 1.0 / m;

  return Quaternion(q.m_w * m, q.m_i * m, q.m_j * m, q.m_k * m);
}

/**
 * Rotates a given vector using this quaternion.
 *
 * @param vector Vector to rotate
 * @return Rotated vector
 */
Vector3DStack Quaternion::rotateVector(const Vector3DStack &vector) const
{
  const Quaternion inv = inverse();
  Quaternion pos(0.0, vector.getX(), vector.getY(), vector.getZ());
  pos = pos * inv;
  pos = (*this) * pos;
  return Vector3DStack(pos.getI(), pos.getJ(), pos.getK());
}

/**
 * Outputs the component values of a quaternion to a strem in the format
 * "[w,i,j,k]".
 *
 * @param stream The stream to output to
 * @param q The quaternion to output
 */
std::ostream &operator<<(std::ostream &stream, const Quaternion &q)
{
  stream << "[" << q.m_w << "," << q.m_i << "," << q.m_j << "," << q.m_k << "]";
  return stream;
}

/**
 * Reads component values of a quaternion from a stream in format "[w,i,j,k]".
 *
 * @param stream Stream to read from
 * @param q Quaternion to store values in
 */
std::istream &operator>>(std::istream &stream, Quaternion &q)
{
  double w, i, j, k;
  char delim;
  stream >> delim >> w >> delim >> i >> delim >> j >> delim >> k >> delim;
  q = Quaternion(w, i, j, k);
  return stream;
}
