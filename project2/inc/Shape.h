#ifndef __GEOMETRY_SHAPE_H_
#define __GEOMETRY_SHAPE_H_

#include "Vector2D.h"
#include "BoundingBox.h"

enum Direction
{
  DIR_UP,
  DIR_DOWN,
  DIR_LEFT,
  DIR_RIGHT,
};

class Shape
{
public:
  Shape();
  Shape(const Shape &other);
  virtual ~Shape();

  void operator=(const Shape &other);

  virtual BoundingBox getBoundingBox() const = 0;

  void setPosition(Vector2D position);
  void setPosition(Vector2D position, BoundingBox clamp);
  void offsetPositionBy(Vector2D offset);
  void offsetPositionBy(Vector2D offset, BoundingBox clamp);

  Vector2D getPosition() const;

protected:
  Vector2D m_position;
};

#endif
