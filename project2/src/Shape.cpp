#include "Shape.h"

#include <stdexcept>

Shape::Shape()
    : m_position()
{
}

Shape::Shape(const Shape &other)
    : m_position(other.m_position)
{
}

Shape::~Shape()
{
}

Shape &Shape::operator=(const Shape &other)
{
  m_position = other.m_position;

  return *this;
}

bool Shape::operator==(const Shape &other) const
{
  return (m_position == other.m_position) && this->compare(other) &&
         other.compare(*this);
}

bool Shape::operator!=(const Shape &other) const
{
  return !(this->operator==(other));
}

void Shape::setPosition(const Vector2D &position)
{
  m_position = position;
}

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

void Shape::offsetPositionBy(const Vector2D &offset)
{
  m_position += offset;
}

void Shape::offsetPositionBy(const Vector2D &offset, const BoundingBox &clamp)
{
  Vector2D newPos = m_position + offset;
  setPosition(newPos, clamp);
}

Vector2D Shape::getPosition() const
{
  return m_position;
}
