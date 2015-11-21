#include "Shape.h"

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

void Shape::setPosition(Vector2D position)
{
  m_position = position;
}

void Shape::setPosition(Vector2D position, BoundingBox clamp)
{
  // TODO
}

void Shape::offsetPositionBy(Vector2D offset)
{
  m_position += offset;
}

void Shape::offsetPositionBy(Vector2D offset, BoundingBox clamp)
{
  // TODO
}

Vector2D Shape::getPosition() const
{
  return m_position;
}
