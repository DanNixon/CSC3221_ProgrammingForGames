#include "Vector2D.h"

#include <stdexcept>

Vector2D::Vector2D()
    : m_x(0.0)
    , m_y(0.0)
{
}

Vector2D::Vector2D(double x, double y)
    : m_x(x)
    , m_y(y)
{
}

Vector2D::Vector2D(const Vector2D &other)
    : m_x(other.m_x)
    , m_y(other.m_y)
{
}

Vector2D::Vector2D(Vector2D *other)
    : m_x(other->m_x)
    , m_y(other->m_y)
{
}

Vector2D &Vector2D::operator=(const Vector2D &other)
{
  m_x = other.m_x;
  m_y = other.m_y;

  return *this;
}

bool Vector2D::operator==(const Vector2D &other) const
{
  return (m_x == other.m_x) && (m_y == other.m_y);
}

bool Vector2D::operator!=(const Vector2D &other) const
{
  return !(this->operator==(other));
}

Vector2D Vector2D::operator+(const Vector2D &rhs) const
{
  Vector2D result(*this);
  result += rhs;
  return result;
}

void Vector2D::operator+=(const Vector2D &rhs)
{
  m_x += rhs.m_x;
  m_y += rhs.m_y;
}

Vector2D Vector2D::operator-(const Vector2D &rhs) const
{
  Vector2D result(*this);
  result -= rhs;
  return result;
}

void Vector2D::operator-=(const Vector2D &rhs)
{
  m_x -= rhs.m_x;
  m_y -= rhs.m_y;
}

Vector2D Vector2D::operator*(double rhs) const
{
  Vector2D result(*this);
  result *= rhs;
  return result;
}

void Vector2D::operator*=(double rhs)
{
  m_x *= rhs;
  m_y *= rhs;
}

Vector2D Vector2D::operator/(double rhs) const
{
  Vector2D result(*this);
  result /= rhs;
  return result;
}

void Vector2D::operator/=(double rhs)
{
  m_x /= rhs;
  m_y /= rhs;
}

bool Vector2D::operator<(const Vector2D &other) const
{
  return (m_x < other.m_x) && (m_y < other.m_y);
}

bool Vector2D::operator<=(const Vector2D &other) const
{
  return (m_x <= other.m_x) && (m_y <= other.m_y);
}

bool Vector2D::operator>(const Vector2D &other) const
{
  return (m_x > other.m_x) && (m_y > other.m_y);
}

bool Vector2D::operator>=(const Vector2D &other) const
{
  return (m_x >= other.m_x) && (m_y >= other.m_y);
}

/**
 * Returns the X component of the vector.
 *
 * @return X component
 */
double Vector2D::getX() const
{
  return m_x;
}

/**
 * Returns the Y component of the vector.
 *
 * @return Y component
 */
double Vector2D::getY() const
{
  return m_y;
}

/**
 * Return elements of the vector by index operator.
 *
 * For reading and writing.
 *
 * @param index Index accessed
 * @param Vector component
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
 * Outputs the component values of a vector to a strem in the format "[x,y]".
 *
 * @param stream The stream to output to
 * @param v The vector to output
 */
std::ostream &operator<<(std::ostream &stream, const Vector2D &v)
{
  stream << "[" << v.m_x << "," << v.m_y << "]";
  return stream;
}

/**
 * Reads component values of a vector from a stream in format "[x,y]".
 *
 * @param stream Stream to read from
 * @param v Vector to store values in
 */
std::istream &operator>>(std::istream &stream, Vector2D &v)
{
  double x, y;
  char delim;
  stream >> delim >> x >> delim >> y >> delim;
  v = Vector2D(x, y);
  return stream;
}
