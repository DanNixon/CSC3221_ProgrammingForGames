/** \file */

#include "Shape.h"

#include <algorithm>
#include <stdexcept>
#include <typeinfo>

#include "Square.h"
#include "Circle.h"

/**
 * \brief Creates a new shape with its position at origin.
 */
Shape::Shape()
    : m_position()
{
}

/**
 * \brief Creates a new shape with its position copied from an existing Shape.
 *
 * \param other Shape to copy
 */
Shape::Shape(const Shape &other)
    : m_position(other.m_position)
{
}

Shape::~Shape()
{
}

/**
 * \brief Assigns the position of another shape to this one.
 *
 * \param other Shape to copy
 * \return this
 */
Shape &Shape::operator=(const Shape &other)
{
  m_position = other.m_position;

  return *this;
}

/**
 * \brief Tests for equality between this shape and another.
 *
 * \param other Other shape
 * \return True if shapes are equal
 */
bool Shape::operator==(const Shape &other) const
{
  return (m_position == other.m_position) && this->compare(other) &&
         other.compare(*this);
}

/**
 * \brief Tests for inequality between this shape and another.
 *
 * \param other Other shape
 * \return True if shapes are not equal
 */
bool Shape::operator!=(const Shape &other) const
{
  return !(this->operator==(other));
}

/**
 * \brief Sets the position of the shape.
 *
 * \param position Vector defining new position.
 */
void Shape::setPosition(const Vector2D &position)
{
  m_position = position;
}

/**
 * \brief Sets the position of the shape, checking that the shape remains
 *        within a BoundingBox.
 *
 * \param position Vector defining new position.
 * \param clamp BoundingBox to clamp within
 * \return True if the position is valid and was set
 */
bool Shape::setPosition(const Vector2D &position, const BoundingBox &clamp)
{
  BoundingBox currentBox = getBoundingBox();
  bool enclosed = clamp.encloses(currentBox + (position - m_position));

  if (enclosed)
    m_position = position;

  return enclosed;
}

/**
 * \brief Adds an offset to the current position vector.
 *
 * \param offset Vector defining offset to add
 */
void Shape::offsetPositionBy(const Vector2D &offset)
{
  m_position += offset;
}

/**
 * \brief Adds an offset to the current position vector, checking that the
 *        shape remains within a BoundingBox.
 *
 * \param offset Vector defining offset to add
 * \param clamp BoundingBox to clamp within
 * \return True if the offset is valid and was set
 */
bool Shape::offsetPositionBy(const Vector2D &offset, const BoundingBox &clamp)
{
  Vector2D newPos = m_position + offset;
  return setPosition(newPos, clamp);
}

/**
 * \brief Returns a vector describing the position of this shape.
 *
 * \return Position vector.
 */
Vector2D Shape::getPosition() const
{
  return m_position;
}

/**
 * \brief Tests for basic intersection between two shapes.
 *
 * Also returns true of one shape is fully enclosed by the other.
 *
 * Tests by testing for intersection between the bounding boxes.
 *
 * This is performed as the first step for all intersection tests as this is a
 * very inexpensive test.
 *
 * \param other Shape to test intersection with
 * \return True if shapes intersect
 */
bool Shape::intersects(const Shape &other) const
{
  const BoundingBox &thisBox = getBoundingBox();
  const BoundingBox &otherBox = other.getBoundingBox();

  return thisBox.intersects(otherBox);
}


/**
 * \brief Outputs a Shape to a stream.
 *
 * \param stream Reference to the output stream
 * \param s Square to output
 * \return Reference to the output stream
 */
std::ostream &operator<<(std::ostream &stream, const Shape &s)
{
  const std::type_info &instanceType = typeid(s);

  if (instanceType == typeid(Square))
    stream << *((Square *) &s);
  else if (instanceType == typeid(Circle))
    stream << *((Circle *) &s);

  return stream;
}
