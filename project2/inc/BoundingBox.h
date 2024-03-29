/** \file */

#ifndef __GEOMETRY_BOUNDINGBOX_H_
#define __GEOMETRY_BOUNDINGBOX_H_

#include <iostream>

class Vector2D;

/**
 * \enum Direction
 * \brief Represents a direction.
 */
enum Direction
{
  D_UNDEFINED,
  D_UPPERRIGHT,
  D_LOWERRIGHT,
  D_LOWERLEFT,
  D_UPPERLEFT
};

/**
 * \class BoundingBox
 * \brief Represents the box around a shape defined by its maximum and minimum
 *        dimensions in each axis.
 */
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
  Vector2D getUpperLeft() const;
  Vector2D getLowerRight() const;
  Vector2D getCentre() const;

  bool intersects(const BoundingBox &other) const;
  bool encloses(const BoundingBox &other) const;

  Direction getRelativePosition(const BoundingBox &other) const;

  friend std::ostream &operator<<(std::ostream &stream, const BoundingBox &b);

private:
  Vector2D *m_lowerLeft;  //!< Lower left hand vertex
  Vector2D *m_upperRight; //!< Upper right hand vertex
};

std::istream &operator>>(std::istream &stream, BoundingBox &b);

#endif
