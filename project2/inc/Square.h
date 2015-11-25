/** \file */

#ifndef __GEOMETRY_SQUARE_H_
#define __GEOMETRY_SQUARE_H_

#include <iostream>
#include "Shape.h"

/**
 * \class Square
 * \brief Class to represent a square.
 *
 * Note that the position denotes the centre of the square.
 */
class Square : public Shape
{
public:
  Square();
  Square(double width, double height);
  Square(const Square &other);
  ~Square();

  Square &operator=(const Square &other);

  double getWidth() const;
  double getHeight() const;

  virtual BoundingBox getBoundingBox() const;

  virtual bool intersects(const Shape &other) const;

  friend std::ostream &operator<<(std::ostream &stream, const Square &s);

private:
  virtual bool compare(const Shape &other) const;

  double m_width; //!< Width of square
  double m_height; //!< Height of square
};

std::istream &operator>>(std::istream &stream, Square &s);

#endif
