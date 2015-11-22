#ifndef __GEOMETRY_SHAPE_H_
#define __GEOMETRY_SHAPE_H_

#include "Vector2D.h"
#include "BoundingBox.h"

class Shape
{
public:
  Shape();
  Shape(const Shape &other);
  virtual ~Shape();

  Shape &operator=(const Shape &other);

  virtual BoundingBox getBoundingBox() const = 0;

  void setPosition(const Vector2D &position);
  void setPosition(const Vector2D &position, const BoundingBox &clamp);
  void offsetPositionBy(const Vector2D &offset);
  void offsetPositionBy(const Vector2D &offset, const BoundingBox &clamp);

  Vector2D getPosition() const;

protected:
  Vector2D m_position;
};

#endif
