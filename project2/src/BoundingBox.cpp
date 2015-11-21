#include "BoundingBox.h"

#include "Vector2D.h"

BoundingBox::BoundingBox()
    : m_lowerRight(new Vector2D())
    , m_upperLeft(new Vector2D())
{
}

BoundingBox::BoundingBox(const Vector2D &lowerRight, const Vector2D &upperLeft)
    : m_lowerRight(new Vector2D(lowerRight))
    , m_upperLeft(new Vector2D(upperLeft))
{
}

BoundingBox::BoundingBox(double lowerRightX, double lowerRightY,
                         double upperLeftX, double upperLeftY)
    : m_lowerRight(new Vector2D(lowerRightX, lowerRightY))
    , m_upperLeft(new Vector2D(upperLeftX, upperLeftY))
{
}

BoundingBox::BoundingBox(const BoundingBox &other)
    : m_lowerRight(new Vector2D(other.m_lowerRight))
    , m_upperLeft(new Vector2D(other.m_upperLeft))
{
}

BoundingBox::~BoundingBox()
{
  delete m_lowerRight;
  delete m_upperLeft;
}

void BoundingBox::operator=(const BoundingBox &other)
{
  delete m_lowerRight;
  delete m_upperLeft;

  m_lowerRight = new Vector2D(other.m_lowerRight);
  m_upperLeft = new Vector2D(other.m_upperLeft);
}

bool BoundingBox::operator==(const BoundingBox &other) const
{
  return (*m_lowerRight == *(other.m_lowerRight)) &&
         (*m_upperLeft == *(other.m_upperLeft));
}

bool BoundingBox::operator!=(const BoundingBox &other) const
{
  return !(this->operator==(other));
}

BoundingBox BoundingBox::operator+(const Vector2D &rhs) const
{
  BoundingBox result(*this);
  result += rhs;
  return result;
}

void BoundingBox::operator+=(const Vector2D &rhs)
{
  (*m_lowerRight) += rhs;
  (*m_upperLeft) += rhs;
}

BoundingBox BoundingBox::operator-(const Vector2D &rhs) const
{
  BoundingBox result(*this);
  result -= rhs;
  return result;
}

void BoundingBox::operator-=(const Vector2D &rhs)
{
  (*m_lowerRight) -= rhs;
  (*m_upperLeft) -= rhs;
}

Vector2D BoundingBox::getLowerRight() const
{
  return *m_lowerRight;
}

Vector2D BoundingBox::getUpperLeft() const
{
  return *m_upperLeft;
}

bool BoundingBox::shapeFullyEnclosed(const Shape &shape) const
{
  // TODO
  return false;
}

std::ostream &operator<<(std::ostream &stream, const BoundingBox &b)
{
  stream << "[" << *(b.m_lowerRight) << "," << *(b.m_upperLeft) << "]";
  return stream;
}

std::istream &operator>>(std::istream &stream, BoundingBox &b)
{
  Vector2D lowerRight, upperLeft;
  char delim;
  stream >> delim >> lowerRight >> delim >> upperLeft >> delim;
  b = BoundingBox(lowerRight, upperLeft);
  return stream;
}
