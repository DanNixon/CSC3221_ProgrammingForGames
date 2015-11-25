/** \file */

#include "Circle.h"

#include <cmath>
#include <stdexcept>
#include <typeinfo>
#include "Square.h"

/**
 * \brief Creates a new circle of zero area.
 */
Circle::Circle()
    : Shape()
    , m_radius(0.0)
{
}

/**
 * \brief Creates a new circle with a given radius.
 *
 * \param radius Radius of circle
 */
Circle::Circle(double radius)
    : Shape()
    , m_radius(radius)
{
}

/**
 * \brief Creates a copy of an existing circle.
 *
 * \param other Circle to copy
 */
Circle::Circle(const Circle &other)
    : Shape(other)
    , m_radius(other.m_radius)
{
}

Circle::~Circle()
{
}

/**
 * \copydoc Shape::operator=()
 */
Circle &Circle::operator=(const Circle &other)
{
  Shape::operator=(other);

  m_radius = other.m_radius;

  return *this;
}

/**
 * \brief Returns the radius of the circle
 *
 * \return Radius
 */
double Circle::getRadius() const
{
  return m_radius;
}

/**
 * \copydoc Shape::getBoundingBox()
 */
BoundingBox Circle::getBoundingBox() const
{
  Vector2D dimensions(m_radius, m_radius);
  return BoundingBox(m_position - dimensions, m_position + dimensions);
}

/**
 * \copydoc Shape::intersects()
 */
bool Circle::intersects(const Shape &other) const
{
  if (!Shape::intersects(other))
    return false;

  const std::type_info &otherType = typeid(other);

  if (otherType == typeid(*this))
  {
    const Circle * otherCircle = dynamic_cast<const Circle *>(&other);
    const double r = pow(m_radius + otherCircle->m_radius, 2);
    const double l = pow(m_position[0] - otherCircle->m_position[0], 2) +
                     pow(m_position[1] - otherCircle->m_position[1], 2);
    std::cout << l << "<" << r << std::endl;
    return l < r;
  }
  else if (otherType == typeid(Square))
  {
    // TODO
    return true;
  }
  else
  {
    throw std::runtime_error("Cannot check intersection with " +
                             std::string(otherType.name()));
  }
}

/**
 * \brief Checks for equality between two Circle objects.
 *
 * Always returns false for a Shape other than a Circle.
 *
 * \param other Other circle
 * \return True if circles are equal
 */
bool Circle::compare(const Shape &other) const
{
  const Circle *c = dynamic_cast<const Circle *>(&other);
  if (c == NULL)
    return false;

  return m_radius == c->m_radius;
}

/**
 * \brief Outputs a Circle to a stream
 *
 * In format "[[x,y],r]" where x and y denote the position and r denotes the
 * radius.
 *
 * \param stream Reference to the output stream
 * \param c Circle to output
 * \return Reference to the output stream
 */
std::ostream &operator<<(std::ostream &stream, const Circle &c)
{
  stream << "[" << c.m_position << "," << c.m_radius << "]";
  return stream;
}

/**
 * \brief Creates a Circle from input from a stream.
 *
 * In format "[[x,y],r]" where x and y denote the position and r denotes the
 * radius.
 *
 * \param stream Reference to the input stream
 * \param c Reference to Circle to be created
 * \return Reference to the input stream
 */
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
