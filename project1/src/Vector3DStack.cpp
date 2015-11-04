#include "Vector3DStack.h"

#include <cfloat>
#include <cmath>
#include <stdexcept>

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
 * Instantiate a new vector will all components set to zero.
 */
Vector3DStack::Vector3DStack()
    : m_x(0.0)
    , m_y(0.0)
    , m_z(0.0)
{
}

/**
 * Instantiate a new vector taking values from another.
 *
 * @param other Vector to copy values from
 */
Vector3DStack::Vector3DStack(const Vector3DStack &other)
    : m_x(other.m_x)
    , m_y(other.m_y)
    , m_z(other.m_z)
{
}

/**
 * Instantiate a new vector with given values.
 *
 * @param x Value of X component
 * @param y Value of Y component
 * @param z Value of Z component
 */
Vector3DStack::Vector3DStack(const double x, const double y, const double z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
{
}

/**
 * Destructor
 */
Vector3DStack::~Vector3DStack()
{
}

/**
 * Set the values of this vector to the values of another.
 *
 * @param other Vector to copy values from
 */
void Vector3DStack::operator=(const Vector3DStack &other)
{
  m_x = other.m_x;
  m_y = other.m_y;
  m_z = other.m_z;
}

/**
 * Check for equality between this vector and another.
 *
 * @param other Other vector
 * @return True if all component values are equal
 */
bool Vector3DStack::operator==(const Vector3DStack &other) const
{
  return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z);
}

/**
 * Check for inequality between this vector and another.
 *
 * @param other Other vector
 * @return True if at least one component value differs
 */
bool Vector3DStack::operator!=(const Vector3DStack &other) const
{
  return !operator==(other);
}

/**
 * Returns the X component of the vector.
 *
 * @return X component
 */
double Vector3DStack::getX() const
{
  return m_x;
}

/**
 * Returns the Y component of the vector.
 *
 * @return Y component
 */
double Vector3DStack::getY() const
{
  return m_y;
}

/**
 * Returns the Z component of the vector.
 *
 * @return Z component
 */
double Vector3DStack::getZ() const
{
  return m_z;
}

/**
 * Calculates the magnitude of the vector.
 *
 * @return Magnitude
 */
double Vector3DStack::magnitude() const
{
  return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

/**
 * Calculates the unit vector of this vector through scalar division by the
 * magnitude.
 *
 * @return Unit vector
 */
Vector3DStack Vector3DStack::getUnitVector() const
{
  return Vector3DStack(*this) / magnitude();
}

/**
 * Calculates a unit vector that is orthogonal to both this and another given
 * vector.
 *
 * @param other Other vector
 * @returns Orthogonal unit vector
 */
Vector3DStack
Vector3DStack::getOrthogonalUnitVector(const Vector3DStack &other) const
{
  Vector3DStack v = (*this) % other;
  return v.getUnitVector();
}

/**
 * Adds two vectors.
 *
 * @param rhs Right hand side vector
 * @return This vector plus the RHS
 */
Vector3DStack Vector3DStack::operator+(const Vector3DStack &rhs) const
{
  return Vector3DStack(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
}

/**
 * Subtract a vector from this vector.
 *
 * @param rhs Right hand side vector
 * @return This vector minus the RHS
 */
Vector3DStack Vector3DStack::operator-(const Vector3DStack &rhs) const
{
  return Vector3DStack(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z);
}

/**
 * Performs multiplication by a scalar.
 *
 * @param rhs Scalar to multiply by
 * @return Product vector
 */
Vector3DStack Vector3DStack::operator*(const double rhs) const
{
  return Vector3DStack(m_x * rhs, m_y * rhs, m_z * rhs);
}

/**
 * Performs division by a scalar.
 *
 * Note that this could be heavily optimised by removing the division by zero
 * checking, and in any real world application I would do this, but previous
 * students tell me they lost marks by omitting it.
 *
 * @param rhs Scalar to divide by
 * @return Quotient vector
 */
Vector3DStack Vector3DStack::operator/(const double rhs) const
{
  if (std::abs(rhs) < DBL_EPSILON)
    throw std::runtime_error("Division by zero");

  return Vector3DStack(m_x / rhs, m_y / rhs, m_z / rhs);
}

/**
 * Calculates dot (scalar) product of two vectors.
 *
 * @param rhs Right hand side vector
 * @return Dot product
 */
double Vector3DStack::operator*(const Vector3DStack &rhs) const
{
  return (m_x * rhs.m_x + m_y * rhs.m_y + m_z * rhs.m_z);
}

/**
 * Calculates the cross (vector) product of two vectors.
 *
 * @param rhs Right hand side vector
 * @return Cross product
 */
Vector3DStack Vector3DStack::operator%(const Vector3DStack &rhs) const
{
  return Vector3DStack(m_y * rhs.m_z - m_z * rhs.m_y,
                       m_z * rhs.m_x - m_x * rhs.m_z,
                       m_x * rhs.m_y - m_y * rhs.m_x);
}

/**
 * Return elements of the vector by index operator.
 *
 * @param index Index accessed
 * @param Vector component
 */
double Vector3DStack::operator[](const int index) const
{
  switch(index)
  {
    case 0:
      return m_x;
    case 1:
      return m_y;
    case 2:
      return m_z;
    default:
      throw std::runtime_error("Vector index out fo range");
  }
}

/**
 * Outputs the component values of a vector to a strem in the format "[x,y,z]".
 *
 * @param stream The stream to output to
 * @param v The vector to output
 */
std::ostream &operator<<(std::ostream &stream, const Vector3DStack &v)
{
  stream << "[" << v.m_x << "," << v.m_y << "," << v.m_z << "]";
  return stream;
}

/**
 * Reads component values of a vector from a stream in format "[x,y,z]".
 *
 * @param stream Stream to read from
 * @param v Vector to store values in
 */
std::istream &operator>>(std::istream &stream, Vector3DStack &v)
{
  double x, y, z;
  char delim;
  stream >> delim >> x >> delim >> y >> delim >> z >> delim;
  v = Vector3DStack(x, y, z);
  return stream;
}
