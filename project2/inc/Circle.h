/** \file */

#ifndef __GEOMETRY_CIRCLE_H_
#define __GEOMETRY_CIRCLE_H_

#include <iostream>
#include "Shape.h"

/**
 * \class Circle
 * \brief Class to represent a circle.
 *
 * Note that the position denotes the centre of the circle.
 */
class Circle : public Shape
{
public:
  Circle();
  Circle(double radius);
  Circle(const Circle &other);
  ~Circle();

  Circle &operator=(const Circle &other);

  double getRadius() const;

  virtual BoundingBox getBoundingBox() const;

  virtual bool intersects(const Shape &other) const;

  friend std::ostream &operator<<(std::ostream &stream, const Circle &c);

private:
  virtual bool compare(const Shape &other) const;

  double m_radius; //!< Radius of the circle
};

std::istream &operator>>(std::istream &stream, Circle &c);

#endif
