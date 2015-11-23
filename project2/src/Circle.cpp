#include "Circle.h"

Circle::Circle()
    : Shape()
    , m_radius(0.0)
{
}

Circle::Circle(double radius)
    : Shape()
    , m_radius(radius)
{
}

Circle::Circle(const Circle &other)
    : Shape(other)
    , m_radius(other.m_radius)
{
}

Circle::~Circle()
{
}

Circle &Circle::operator=(const Circle &other)
{
  Shape::operator=(other);

  m_radius = other.m_radius;

  return *this;
}

BoundingBox Circle::getBoundingBox() const
{
  Vector2D dimensions(m_radius, m_radius);
  dimensions /= 2;
  return BoundingBox(m_position - dimensions, m_position + dimensions);
}

double Circle::getRadius() const
{
  return m_radius;
}

bool Circle::compare(const Shape &other) const
{
  const Circle *c = dynamic_cast<const Circle *>(&other);
  if (c == NULL)
    return false;

  return m_radius == c->m_radius;
}

std::ostream &operator<<(std::ostream &stream, const Circle &c)
{
  stream << "[" << c.m_position << "," << c.m_radius << "]";
  return stream;
}

std::istream &operator>>(std::istream &stream, Circle &c)
{
  Vector2D p;
  double r;
  char delim;
  stream >> delim >> p >> delim >> r >> delim;
  c = Circle(r);
  c.setPosition(p);
  return stream;
}
