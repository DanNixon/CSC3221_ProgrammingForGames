#include "Square.h"

#include <stdexcept>
#include <typeinfo>
#include "Circle.h"

Square::Square()
    : Shape()
    , m_width(0.0)
    , m_height(0.0)
{
}

Square::Square(double width, double height)
    : Shape()
    , m_width(width)
    , m_height(height)
{
}

Square::Square(const Square &other)
    : Shape(other)
    , m_width(other.m_width)
    , m_height(other.m_height)
{
}

Square::~Square()
{
}

Square &Square::operator=(const Square &other)
{
  Shape::operator=(other);

  m_width = other.m_width;
  m_height = other.m_height;

  return *this;
}

BoundingBox Square::getBoundingBox() const
{
  Vector2D dimensions(m_width, m_height);
  dimensions /= 2;
  return BoundingBox(m_position - dimensions, m_position + dimensions);
}

double Square::getWidth() const
{
  return m_width;
}

double Square::getHeight() const
{
  return m_height;
}

bool Square::intersects(const Shape &other) const
{
  const std::type_info &otherType = typeid(other);

  if (otherType == typeid(*this))
  {
    // TODO
  }
  else if (otherType == typeid(Circle))
  {
    // TODO
  }
  else
  {
    throw std::runtime_error("Cannot check intersection with " +
                             std::string(otherType.name()));
  }
}

bool Square::compare(const Shape &other) const
{
  const Square *s = dynamic_cast<const Square *>(&other);
  if (s == NULL)
    return false;

  return (m_width == s->m_width) && (m_height == s->m_height);
}

std::ostream &operator<<(std::ostream &stream, const Square &s)
{
  stream << "[" << s.m_position << "," << s.m_width << "," << s.m_height << "]";
  return stream;
}

std::istream &operator>>(std::istream &stream, Square &s)
{
  Vector2D p;
  double w, h;
  char delim;
  stream >> delim >> p >> delim >> w >> delim >> h >> delim;
  s = Square(w, h);
  s.setPosition(p);
  return stream;
}
