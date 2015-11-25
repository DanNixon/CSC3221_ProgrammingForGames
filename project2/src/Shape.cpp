/** \file */

#include "Shape.h"

#include <stdexcept>

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
 * \brief Sets the position of the shape, clamping to within a BoundingBox.
 *
 * \param position Vector defining new position.
 * \param clamp BoundingBox to clamp within
 */
void Shape::setPosition(const Vector2D &position, const BoundingBox &clamp)
{
  BoundingBox currentBox = getBoundingBox();
  BoxEnclosedState state =
      clamp.boundingBoxEnclosed(currentBox + (position - m_position));

  switch (state)
  {
  case BE_FULL:
    m_position = position;
    break;
  case BE_LOWERLEFT_OUT:
  {
    Vector2D lowerLeftClamp = clamp.getLowerLeft() + (currentBox.size() / 2.0);
    m_position = Vector2D(std::max(position.getX(), lowerLeftClamp.getX()),
                          std::max(position.getY(), lowerLeftClamp.getY()));
    break;
  }
  case BE_UPPERRIGHT_OUT:
  {
    Vector2D upperRightClamp =
        clamp.getUpperRight() - (currentBox.size() / 2.0);
    m_position = Vector2D(std::min(position.getX(), upperRightClamp.getX()),
                          std::min(position.getY(), upperRightClamp.getY()));
    break;
  }
  case BE_LARGER:
    throw std::runtime_error("Shape is larger than bounding box");
    break;
  default:
    throw std::runtime_error("Invalid state");
  }
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
 * \brief Adds an offset to the current position vector, clamping the position
 *        to within a BoundingBox.
 *
 * \param offset Vector defining offset to add
 * \param clamp BoundingBox to clamp within
 */
void Shape::offsetPositionBy(const Vector2D &offset, const BoundingBox &clamp)
{
  Vector2D newPos = m_position + offset;
  setPosition(newPos, clamp);
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
