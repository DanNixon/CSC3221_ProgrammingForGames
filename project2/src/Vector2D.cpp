/** \file */

#include "Vector2D.h"

#include <cmath>
#include <stdexcept>

/**
 * \brief Creates a new Vector2D with zeros for all components.
 */
Vector2D::Vector2D()
    : m_x(0.0)
    , m_y(0.0)
{
}

/**
 * \brief Creates a new Vector2D with given values for components.
 *
 * \param x X component
 * \param y Y component
 */
Vector2D::Vector2D(double x, double y)
    : m_x(x)
    , m_y(y)
{
}

/**
 * \brief Creates a copy of an existing Vector2D.
 *
 * \param other Vector2D to copy
 */
Vector2D::Vector2D(const Vector2D &other)
    : m_x(other.m_x)
    , m_y(other.m_y)
{
}

/**
 * \brief Creates a copy of an existing Vector2D given a pointer.
 *
 * \param other Pointer to Vector2D to copy
 */
Vector2D::Vector2D(Vector2D *other)
    : m_x(other->m_x)
    , m_y(other->m_y)
{
}

Vector2D::~Vector2D()
{
}

/**
 * \brief Copy values of an existing Vector2D.
 *
 * \param other Vector2D to copy
 */
Vector2D &Vector2D::operator=(const Vector2D &other)
{
  m_x = other.m_x;
  m_y = other.m_y;

  return *this;
}

/**
 * \brief Tests for equality with another Vector2D.
 *
 * \param other Vector2D to compare to
 * \return True if all components match
 */
bool Vector2D::operator==(const Vector2D &other) const
{
  return (m_x == other.m_x) && (m_y == other.m_y);
}

/**
 * \brief Tests for inequality with another Vector2D.
 *
 * \param other Vector2D to compare to
 * \return True if any components differ
 */
bool Vector2D::operator!=(const Vector2D &other) const
{
  return !(this->operator==(other));
}

/**
 * \brief Adds the components of this vector and another.
 *
 * \param rhs Vector to add
 * \return This vector plus the RHS
 */
Vector2D Vector2D::operator+(const Vector2D &rhs) const
{
  Vector2D result(*this);
  result += rhs;
  return result;
}

/**
 * \brief Increments the components of this vector by those of another.
 *
 * \param rhs Vector to increment by
 */
void Vector2D::operator+=(const Vector2D &rhs)
{
  m_x += rhs.m_x;
  m_y += rhs.m_y;
}

/**
 * \brief Subtracts the components of another vector from this one.
 *
 * \param rhs Vector to subtract
 * \return This vector minus the RHS
 */
Vector2D Vector2D::operator-(const Vector2D &rhs) const
{
  Vector2D result(*this);
  result -= rhs;
  return result;
}

/**
 * \brief Decrements the components of this vector by those of another.
 *
 * \param rhs Vector to decrement by
 */
void Vector2D::operator-=(const Vector2D &rhs)
{
  m_x -= rhs.m_x;
  m_y -= rhs.m_y;
}

/**
 * \brief Multiplies the components of a vector by a scalar value.
 *
 * \param rhs Scalar to multiply by
 * \return Scalar prouduct
 */
Vector2D Vector2D::operator*(double rhs) const
{
  Vector2D result(*this);
  result *= rhs;
  return result;
}

/**
 * \brief Multiplies the components of this vector by a scalar value.
 *
 * \param rhs Scalar to multiply by
 */
void Vector2D::operator*=(double rhs)
{
  m_x *= rhs;
  m_y *= rhs;
}

/**
 * \brief Divides the components of a vector by a scalar value.
 *
 * \param rhs Scalar to divide by
 * \return Quotient
 */
Vector2D Vector2D::operator/(double rhs) const
{
  Vector2D result(*this);
  result /= rhs;
  return result;
}

/**
 * \brief Divides the components of this vector by a scalar value.
 *
 * \param rhs Scalar to divide by
 */
void Vector2D::operator/=(double rhs)
{
  m_x /= rhs;
  m_y /= rhs;
}

/**
 * \brief Test for each component of another vector being greater than
 *        components of this vector.
 *
 * \param other Other vector to test
 * \return True if this < other
 */
bool Vector2D::operator<(const Vector2D &other) const
{
  return (m_x < other.m_x) && (m_y < other.m_y);
}

/**
 * \brief Test for each component of another vector being greater than or equal
 *        to components of this vector.
 *
 * \param other Other vector to test
 * \return True if this <= other
 */
bool Vector2D::operator<=(const Vector2D &other) const
{
  return (m_x <= other.m_x) && (m_y <= other.m_y);
}

/**
 * \brief Test for each component of another vector being less than components
 *        of this vector.
 *
 * \param other Other vector to test
 * \return True if this > other
 */
bool Vector2D::operator>(const Vector2D &other) const
{
  return (m_x > other.m_x) && (m_y > other.m_y);
}

/**
 * \brief Test for each component of another vector being less than or equal
 *        to components of this vector.
 *
 * \param other Other vector to test
 * \return True if this >= other
 */
bool Vector2D::operator>=(const Vector2D &other) const
{
  return (m_x >= other.m_x) && (m_y >= other.m_y);
}

/**
 * \brief Returns the X component of the vector.
 *
 * \return X component
 */
double Vector2D::getX() const
{
  return m_x;
}

/**
 * \brief Returns the Y component of the vector.
 *
 * \return Y component
 */
double Vector2D::getY() const
{
  return m_y;
}

/**
 * \brief Returns the magnitude of the vector.
 *
 * \return Magnitude
 */
double Vector2D::length() const
{
  return sqrt(length2());
}

/**
 * \brief Returns the square of the magnitude of the vector.
 *
 * \return Magnitude squared
 */
double Vector2D::length2() const
{
  return (m_x * m_x) + (m_y * m_y);
}

/**
 * \brief Return elements of the vector by index operator.
 *
 * For reading and writing.
 *
 * \param index Index accessed
 * \return Vector component
 */
double Vector2D::operator[](const int index) const
{
  switch (index)
  {
  case 0:
    return m_x;
  case 1:
    return m_y;
  default:
    throw std::runtime_error("Vector index out of range");
  }
}

/**
 * \brief Outputs the component values of a vector to a strem in the format
 *        "[x,y]".
 *
 * \param stream The stream to output to
 * \param v The vector to output
 */
std::ostream &operator<<(std::ostream &stream, const Vector2D &v)
{
  stream << "[" << v.m_x << "," << v.m_y << "]";
  return stream;
}

/**
 * \brief Reads component values of a vector from a stream in format "[x,y]".
 *
 * \param stream Stream to read from
 * \param v Vector to store values in
 */
std::istream &operator>>(std::istream &stream, Vector2D &v)
{
  double x, y;
  char delim;
  stream >> delim >> x >> delim >> y >> delim;
  v = Vector2D(x, y);
  return stream;
}
