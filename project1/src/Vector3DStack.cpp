#include "Vector3DStack.h"

#include <cmath>

Vector3DStack::Vector3DStack()
    : m_x(0)
    , m_y(0)
    , m_z(0)
{
}

Vector3DStack::Vector3DStack(const Vector3DStack &other)
    : m_x(other.getX())
    , m_y(other.getY())
    , m_z(other.getZ())
{
}

Vector3DStack::Vector3DStack(const double x, const double y, const double z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
{
}

bool Vector3DStack::operator==(const Vector3DStack &other) const
{
  return (m_x == other.getX() && m_y == other.getY() && m_z == other.getZ());
}

void Vector3DStack::operator=(const Vector3DStack &other)
{
  m_x = other.getX();
  m_y = other.getY();
  m_z = other.getZ();
}

double Vector3DStack::getX() const
{
  return m_x;
}

double Vector3DStack::getY() const
{
  return m_y;
}

double Vector3DStack::getZ() const
{
  return m_z;
}

double Vector3DStack::magnitude() const
{
  return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector3DStack Vector3DStack::getUnitVector() const
{
  return Vector3DStack(*this) / magnitude();
}

Vector3DStack Vector3DStack::operator+(const Vector3DStack &rhs) const
{
  return Vector3DStack(m_x + rhs.getX(), m_y + rhs.getY(), m_z + rhs.getZ());
}

Vector3DStack Vector3DStack::operator-(const Vector3DStack &rhs) const
{
  return Vector3DStack(m_x - rhs.getX(), m_y - rhs.getY(), m_z - rhs.getZ());
}

Vector3DStack Vector3DStack::operator*(const double rhs) const
{
  return Vector3DStack(m_x * rhs, m_y * rhs, m_z * rhs);
}

Vector3DStack Vector3DStack::operator/(const double rhs) const
{
  return Vector3DStack(m_x / rhs, m_y / rhs, m_z / rhs);
}

/**
 * Dot (scalar) product
 */
double Vector3DStack::operator*(const Vector3DStack &rhs) const
{
  return (m_x * rhs.getX() + m_y * rhs.getY() + m_z * rhs.getZ());
}

/**
 * Cross (vector) product
 */
Vector3DStack Vector3DStack::operator%(const Vector3DStack &rhs) const
{
  return Vector3DStack(m_y * rhs.getZ() - m_z * rhs.getY(),
                       m_z * rhs.getX() - m_x * rhs.getZ(),
                       m_x * rhs.getY() - m_y * rhs.getX());
}
