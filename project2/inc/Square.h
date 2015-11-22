#ifndef __GEOMETRY_SQUARE_H_
#define __GEOMETRY_SQUARE_H_

#include <iostream>
#include "Shape.h"

class Square : public Shape
{
public:
  Square();
  Square(double width, double height);
  Square(const Square &other);
  ~Square();

  virtual Square &operator=(const Square &other);

  virtual BoundingBox getBoundingBox() const;

  double getWidth() const;
  double getHeight() const;

  friend std::ostream &operator<<(std::ostream &stream, const Square &s);

private:
  double m_width;
  double m_height;
};

std::istream &operator>>(std::istream &stream, Square &s);

#endif
