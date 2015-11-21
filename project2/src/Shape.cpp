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

void Shape::operator=(const Shape &other)
{
  m_position = other.m_position;
}

void Shape::setPosition(const Vector2D &position)
{
  m_position = position;
}

void Shape::setPosition(const Vector2D &position, const BoundingBox &clamp)
{
  BoxEnclosedState state =
      clamp.boundingBoxEnclosed(getBoundingBox() + (position - m_position));

  switch (state)
  {
  case BE_FULL:
    m_position = position;
    break;
  case BE_LOWERRIGHT_OUT:
    // TODO
    break;
  case BE_UPPERLEFT_OUT:
    // TODO
    break;
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
