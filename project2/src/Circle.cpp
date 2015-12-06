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
    const Circle * otherCircle = static_cast<const Circle *>(&other);

    /* Compare distance between centres of both circles to the sum of their
     * radii */
    const double r = pow(m_radius + otherCircle->m_radius, 2);
    const double l = pow(m_position[0] - otherCircle->m_position[0], 2) +
                     pow(m_position[1] - otherCircle->m_position[1], 2);
    return l < r;
  }
  else if (otherType == typeid(Square))
  {
    const Square * otherSquare = static_cast<const Square *>(&other);
    const BoundingBox &squareBounds = otherSquare->getBoundingBox();

    /* Determine the vertex of the square that is closest to the centre of the
     * circle */
    Direction pos = squareBounds.getRelativePosition(getBoundingBox());

    const double r2 = m_radius * m_radius;

    /* Compare the distance between the centre of the circle and the closest
     * vertex of the square with the circle radius */
    switch (pos)
    {
    case D_LOWERLEFT:
      if ((squareBounds.getLowerLeft() - m_position).length2() < r2)
        return true;
      break;
    case D_LOWERRIGHT:
      if ((squareBounds.getLowerRight() - m_position).length2() < r2)
        return true;
      break;
    case D_UPPERLEFT:
      if ((squareBounds.getUpperLeft() - m_position).length2() < r2)
        return true;
      break;
    case D_UPPERRIGHT:
      if ((squareBounds.getUpperRight() - m_position).length2() < r2)
        return true;
      break;
    case D_UNDEFINED:
      return true;
    default:
      return false;
    }

    /* Need both the default and this return to avoid compiler warning. */
    return false;
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
 * In format "CIRCLE[[x,y],r]" where x and y denote the position and r denotes
 * the radius.
 *
 * \param stream Reference to the output stream
 * \param c Circle to output
 * \return Reference to the output stream
 */
std::ostream &operator<<(std::ostream &stream, const Circle &c)
{
  stream << "CIRCLE[" << c.m_position << "," << c.m_radius << "]";
  return stream;
}

/**
 * \brief Creates a Circle from input from a stream.
 *
 * In format "CIRCLE[[x,y],r]" where x and y denote the position and r denotes
 * the radius.
 *
 * \param stream Reference to the input stream
 * \param c Reference to Circle to be created
 * \return Reference to the input stream
 */
std::istream &operator>>(std::istream &stream, Circle &c)
{
  const int n = 100;

  Vector2D p;
  double r;

  stream.ignore(n, '[');
  stream >> p;

  stream.ignore(n, ',');
  stream >> r;

  stream.ignore(n, ']');

  c = Circle(r);
  c.setPosition(p);
  return stream;
}
