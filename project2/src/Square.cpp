/** \file */

#include "Square.h"

#include <stdexcept>
#include <typeinfo>
#include "Circle.h"

/**
 * \brief Create a new square of zero area.
 */
Square::Square()
    : Shape()
    , m_width(0.0)
    , m_height(0.0)
{
}

/**
 * \brief Create a new square of given dimensions.
 *
 * \param width WIdth of square
 * \param height Height of square
 */
Square::Square(double width, double height)
    : Shape()
    , m_width(width)
    , m_height(height)
{
}

/**
 * \brief Creates a copy of an existing square.
 *
 * \param other Square to copy from
 */
Square::Square(const Square &other)
    : Shape(other)
    , m_width(other.m_width)
    , m_height(other.m_height)
{
}

Square::~Square()
{
}

/**
 * \copydoc Shape::operator=()
 */
Square &Square::operator=(const Square &other)
{
  Shape::operator=(other);

  m_width = other.m_width;
  m_height = other.m_height;

  return *this;
}

/**
 * \brief Returns the width of the square.
 *
 * \return Width
 */
double Square::getWidth() const
{
  return m_width;
}

/**
 * \brief Returns the height of the square.
 *
 * \return Height
 */
double Square::getHeight() const
{
  return m_height;
}

/**
 * \copydoc Shape::getBoundingBox()
 */
BoundingBox Square::getBoundingBox() const
{
  Vector2D dimensions(m_width, m_height);
  dimensions /= 2;
  return BoundingBox(m_position - dimensions, m_position + dimensions);
}

/**
 * \copydoc Shape::intersects()
 */
bool Square::intersects(const Shape &other) const
{
  if (!Shape::intersects(other))
    return false;

  const std::type_info &otherType = typeid(other);

  if (otherType == typeid(*this))
  {
    // The bunding box test in Shape::intersects is sufficient to test
    // intersection of two squares
    return true;
  }
  else if (otherType == typeid(Circle))
  {
    // Use the implmentaton from Circle
    const Circle * otherCircle = static_cast<const Circle *>(&other);
    return otherCircle->intersects(*this);
  }
  else
  {
    throw std::runtime_error("Cannot check intersection with " +
                             std::string(otherType.name()));
  }
}

/**
 * \brief Checks for equality between two Square objects.
 *
 * Always returns false for a Shape other than a Circle.
 *
 * \param other Other square
 * \return True if squares are equal
 */
bool Square::compare(const Shape &other) const
{
  const Square *s = dynamic_cast<const Square *>(&other);
  if (s == NULL)
    return false;

  return (m_width == s->m_width) && (m_height == s->m_height);
}

/**
 * \brief Outputs a Square to a stream
 *
 * In format "[[x,y],w,h]" where x and y denote the position, w denotes the
 * width and h denotes the height.
 *
 * \param stream Reference to the output stream
 * \param s Square to output
 * \return Reference to the output stream
 */
std::ostream &operator<<(std::ostream &stream, const Square &s)
{
  stream << "SQUARE[" << s.m_position << "," << s.m_width << "," << s.m_height
         << "]";
  return stream;
}

/**
 * \brief Creates a Square from input from a stream.
 *
 * In format "SQUARE[[x,y],w,h]" where x and y denote the position, w denotes
 * the width and h denotes the height.
 *
 * \param stream Reference to the input stream
 * \param s Reference to Square to be created
 * \return Reference to the input stream
 */
std::istream &operator>>(std::istream &stream, Square &s)
{
  const int n = 100;

  Vector2D p;
  double w, h;

  stream.ignore(n, '[');
  stream >> p;

  stream.ignore(n, ',');
  stream >> w;

  stream.ignore(n, ',');
  stream >> h;

  stream.ignore(n, ']');

  s = Square(w, h);
  s.setPosition(p);
  return stream;
}
