#ifndef __GEOMETRY_CIRCLE_H_
#define __GEOMETRY_CIRCLE_H_

#include <iostream>
#include "Shape.h"

class Circle : public Shape
{
public:
  Circle();
  Circle(double radius);
  Circle(const Circle &other);
  ~Circle();

  void operator=(const Circle &other);

  virtual BoundingBox getBoundingBox() const;

  double getRadius() const;

  friend std::ostream &operator<<(std::ostream &stream, const Circle &c);

private:
  double m_radius;
};

std::istream &operator>>(std::istream &stream, Circle &c);

#endif
