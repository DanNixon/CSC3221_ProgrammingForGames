#include "BoundingBox.h"

#include "Vector2D.h"

BoundingBox::BoundingBox()
    : m_lowerLeft(new Vector2D())
    , m_upperRight(new Vector2D())
{
}

BoundingBox::BoundingBox(const Vector2D &lowerRight, const Vector2D &upperLeft)
    : m_lowerLeft(new Vector2D(lowerRight))
    , m_upperRight(new Vector2D(upperLeft))
{
  if (*m_lowerLeft > *m_upperRight)
    std::swap(m_lowerLeft, m_upperRight);
}

BoundingBox::BoundingBox(double lowerRightX, double lowerRightY,
                         double upperLeftX, double upperLeftY)
    : m_lowerLeft(new Vector2D(lowerRightX, lowerRightY))
    , m_upperRight(new Vector2D(upperLeftX, upperLeftY))
{
  if (*m_lowerLeft > *m_upperRight)
    std::swap(m_lowerLeft, m_upperRight);
}

BoundingBox::BoundingBox(const BoundingBox &other)
    : m_lowerLeft(new Vector2D(other.m_lowerLeft))
    , m_upperRight(new Vector2D(other.m_upperRight))
{
}

BoundingBox::~BoundingBox()
{
  delete m_lowerLeft;
  delete m_upperRight;
}

void BoundingBox::operator=(const BoundingBox &other)
{
  delete m_lowerLeft;
  delete m_upperRight;

  m_lowerLeft = new Vector2D(other.m_lowerLeft);
  m_upperRight = new Vector2D(other.m_upperRight);
}

bool BoundingBox::operator==(const BoundingBox &other) const
{
  return (*m_lowerLeft == *(other.m_lowerLeft)) &&
         (*m_upperRight == *(other.m_upperRight));
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
  (*m_lowerLeft) += rhs;
  (*m_upperRight) += rhs;
}

BoundingBox BoundingBox::operator-(const Vector2D &rhs) const
{
  BoundingBox result(*this);
  result -= rhs;
  return result;
}

void BoundingBox::operator-=(const Vector2D &rhs)
{
  (*m_lowerLeft) -= rhs;
  (*m_upperRight) -= rhs;
}

Vector2D BoundingBox::size() const
{
  return *m_upperRight - *m_lowerLeft;
}

Vector2D BoundingBox::getLowerLeft() const
{
  return *m_lowerLeft;
}

Vector2D BoundingBox::getUpperRight() const
{
  return *m_upperRight;
}

BoxEnclosedState BoundingBox::boundingBoxEnclosed(const BoundingBox &other) const
{
  bool lowerLeft = (*(other.m_lowerLeft) >= *m_lowerLeft);
  bool upperRight = (*(other.m_upperRight) <= *m_upperRight);

  if (lowerLeft && upperRight)
    return BE_FULL;
  else if (lowerLeft && !upperRight)
    return BE_UPPERRIGHT_OUT;
  else if (!lowerLeft && upperRight)
    return BE_LOWERLEFT_OUT;
  else
    return BE_LARGER;
}

std::ostream &operator<<(std::ostream &stream, const BoundingBox &b)
{
  stream << "[" << *(b.m_lowerLeft) << "," << *(b.m_upperRight) << "]";
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
