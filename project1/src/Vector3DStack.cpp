#include "Vector3DStack.h"

#include <cmath>

Vector3DStack::Vector3DStack()
    : m_x(0)
    , m_y(0)
    , m_z(0)
{
}

Vector3DStack::Vector3DStack(int x, int y, int z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
{
}

int Vector3DStack::getX() const
{
  return m_x;
}

int Vector3DStack::getY() const
{
  return m_y;
}

int Vector3DStack::getZ() const
{
  return m_z;
}

int Vector3DStack::magnitude() const
{
  return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector3DStack Vector3DStack::getUnitVector() const
{
  //TODO
  return Vector3DStack();
}

Vector3DStack Vector3DStack::operator+(const Vector3DStack &rhs)
{
  return Vector3DStack(m_x + rhs.getX(), m_y + rhs.getY(), m_z + rhs.getZ());
}

Vector3DStack Vector3DStack::operator-(const Vector3DStack &rhs)
{
  return Vector3DStack(m_x - rhs.getX(), m_y - rhs.getY(), m_z - rhs.getZ());
}

Vector3DStack Vector3DStack::operator*(const int rhs)
{
  return Vector3DStack(m_x * rhs, m_y * rhs, m_z * rhs);
}

Vector3DStack Vector3DStack::operator/(const int rhs)
{
  return Vector3DStack(m_x / rhs, m_y / rhs, m_z / rhs);
}

/**
 * Dot (scalar) product
 */
int Vector3DStack::operator*(const Vector3DStack &rhs)
{
  return (m_x * rhs.getX() + m_y * rhs.getY() + m_z * rhs.getZ());
}

/**
 * Cross (vector) product
 */
Vector3DStack Vector3DStack::operator%(const Vector3DStack &rhs)
{
  return Vector3DStack(m_y * rhs.getZ() - m_z * rhs.getY(),
                       m_z * rhs.getX() - m_x * rhs.getZ(),
                       m_x * rhs.getY() - m_y * rhs.getX());
}
