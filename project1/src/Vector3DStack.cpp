#include "Vector3DStack.h"

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
  return 0;
}

Vector3DStack Vector3DStack::getUnitVector() const
{
  return Vector3DStack();
}

Vector3DStack Vector3DStack::operator+(const Vector3DStack &rhs)
{
  return Vector3DStack();
}

Vector3DStack Vector3DStack::operator-(const Vector3DStack &rhs)
{
  return Vector3DStack();
}

Vector3DStack Vector3DStack::operator*(const int rhs)
{
  return Vector3DStack();
}

Vector3DStack Vector3DStack::operator/(const int rhs)
{
  return Vector3DStack();
}

Vector3DStack Vector3DStack::operator*(const Vector3DStack &rhs)
{
  return Vector3DStack();
}

Vector3DStack Vector3DStack::operator%(const Vector3DStack &rhs)
{
  return Vector3DStack();
}
