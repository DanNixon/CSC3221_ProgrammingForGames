#ifndef __GEOMETRY_BOUNDINGBOX_H_
#define __GEOMETRY_BOUNDINGBOX_H_

#include <iostream>

class Vector2D;

enum BoxEnclosedState
{
  BE_FULL,
  BE_UPPERLEFT_OUT,
  BE_LOWERRIGHT_OUT,
  BE_LARGER
};

class BoundingBox
{
public:
  BoundingBox();
  BoundingBox(const Vector2D &lowerRight, const Vector2D &upperLeft);
  BoundingBox(double lowerRightX, double lowerRightY, double upperLeftX,
              double upperLeftY);
  BoundingBox(const BoundingBox &other);
  ~BoundingBox();

  void operator=(const BoundingBox &other);

  bool operator==(const BoundingBox &other) const;
  bool operator!=(const BoundingBox &other) const;

  BoundingBox operator+(const Vector2D &rhs) const;
  void operator+=(const Vector2D &rhs);
  BoundingBox operator-(const Vector2D &rhs) const;
  void operator-=(const Vector2D &rhs);

  Vector2D getLowerRight() const;
  Vector2D getUpperLeft() const;

  BoxEnclosedState boundingBoxEnclosed(const BoundingBox &other) const;

  friend std::ostream &operator<<(std::ostream &stream, const BoundingBox &b);

private:
  Vector2D *m_lowerRight;
  Vector2D *m_upperLeft;
};

std::istream &operator>>(std::istream &stream, BoundingBox &b);

#endif
