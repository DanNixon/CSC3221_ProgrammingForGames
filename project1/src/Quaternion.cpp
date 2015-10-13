#include "Quaternion.h"

#include <cmath>

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
 * Construct a quaternion using the values of another.
 *
 * @param rhs Quaternion from which to take values
 */
Quaternion::Quaternion(const Quaternion &other)
    : m_w(other.getReal())
    , m_i(other.getI())
    , m_j(other.getJ())
    , m_k(other.getK())
{
}

/**
 * Assign this quaternion the values of another.
 *
 * @param rhs Quaternion from which to take values
 */
void Quaternion::operator=(const Quaternion &rhs)
{
  m_w = rhs.getReal();
  m_i = rhs.getI();
  m_j = rhs.getJ();
  m_k = rhs.getK();
}

/**
 * Check for equality between this quaternion and another.
 *
 * @param rhs Other quaternion to compare to
 * @return True of values are equal
 */
bool Quaternion::operator==(const Quaternion &rhs) const
{
  return (m_w == rhs.getReal() && m_i == rhs.getI() && m_j == rhs.getJ() &&
          m_k == rhs.getK());
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
 * Return the i imaginary part of the quaternion.
 *
 * @return Coefficient of i
 */
double Quaternion::getI() const
{
  return m_i;
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
  return Quaternion(m_w + rhs.getReal(), m_i + rhs.getI(), m_j + rhs.getJ(),
                    m_k + rhs.getK());
}

/**
 * Subtract two quaternions.
 *
 * @param rhs Quaternion to subtract from the LHS
 * @return Subtraction of quaternions
 */
Quaternion Quaternion::operator-(const Quaternion &rhs) const
{
  return Quaternion(m_w - rhs.getReal(), m_i - rhs.getI(), m_j - rhs.getJ(),
                    m_k - rhs.getK());
}

/**
 * Calculate the product of two quaternions.
 *
 * @param rhs Quaternion to multiply by
 * @return Product of quaternions
 */
Quaternion Quaternion::operator*(const Quaternion &rhs) const
{
  double w = m_w * rhs.getReal() - m_i * rhs.getI() - m_j * rhs.getJ() -
             m_k * rhs.getK();
  double i = m_w * rhs.getI() + rhs.getReal() * m_i + m_j * rhs.getK() -
             rhs.getJ() * m_k;
  double j = m_w * rhs.getJ() + rhs.getReal() * m_j - m_i * rhs.getK() +
             m_k * rhs.getI();
  double k = m_w * rhs.getK() + rhs.getReal() * m_k + m_i * rhs.getJ() -
             rhs.getI() * m_j;

  return Quaternion(w, i, j, k);
}

std::ostream &operator<<(std::ostream &stream, const Quaternion &q)
{
  stream << "[" << q.getReal() << "," << q.getI() << "," << q.getJ() << ","
         << q.getK() << "]";
  return stream;
}

std::istream &operator>>(std::istream &stream, Quaternion &q)
{
  double w, i, j, k;
  char delim;
  stream >> delim >> w >> delim >> i >> delim >> j >> delim >> k >> delim;
  q = Quaternion(w, i, j, k);
  return stream;
}
