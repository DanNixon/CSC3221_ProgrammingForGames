#ifndef __GEOMETRY_BOUNDINGBOX_H_
#define __GEOMETRY_BOUNDINGBOX_H_

#include <iostream>

class Vector2D;

enum BoxEnclosedState
{
  BE_FULL,
  BE_LOWERLEFT_OUT,
  BE_UPPERRIGHT_OUT,
  BE_LARGER
};

class BoundingBox
{
public:
  BoundingBox();
  BoundingBox(const Vector2D &lowerLeft, const Vector2D &upperRight);
  BoundingBox(double lowerLeftX, double lowerLeftY, double upperRightX,
              double upperRightY);
  BoundingBox(const BoundingBox &other);
  ~BoundingBox();

  BoundingBox &operator=(const BoundingBox &other);

  bool operator==(const BoundingBox &other) const;
  bool operator!=(const BoundingBox &other) const;

  BoundingBox operator+(const Vector2D &rhs) const;
  void operator+=(const Vector2D &rhs);
  BoundingBox operator-(const Vector2D &rhs) const;
  void operator-=(const Vector2D &rhs);

  Vector2D size() const;

  Vector2D getLowerLeft() const;
  Vector2D getUpperRight() const;

  BoxEnclosedState boundingBoxEnclosed(const BoundingBox &other) const;
  bool intersects(const BoundingBox &other) const;

  friend std::ostream &operator<<(std::ostream &stream, const BoundingBox &b);

private:
  Vector2D *m_lowerLeft;
  Vector2D *m_upperRight;
};

std::istream &operator>>(std::istream &stream, BoundingBox &b);

#endif
