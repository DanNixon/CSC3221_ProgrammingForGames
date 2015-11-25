/** \file */

#ifndef __GEOMETRY_SHAPE_H_
#define __GEOMETRY_SHAPE_H_

#include "Vector2D.h"
#include "BoundingBox.h"

/**
 * \class Shape
 * \brief Abstract class to represent a 2D shape.
 *
 * Note that the position denotes the centre of the shape.
 */
class Shape
{
public:
  Shape();
  Shape(const Shape &other);
  virtual ~Shape();

  Shape &operator=(const Shape &other);

  bool operator==(const Shape &other) const;
  bool operator!=(const Shape &other) const;

  void setPosition(const Vector2D &position);
  void setPosition(const Vector2D &position, const BoundingBox &clamp);
  void offsetPositionBy(const Vector2D &offset);
  void offsetPositionBy(const Vector2D &offset, const BoundingBox &clamp);

  Vector2D getPosition() const;

  /**
   * \brief Calculate a bounding box around this shape.
   *
   * \return BoundingBox around this shape
   */
  virtual BoundingBox getBoundingBox() const = 0;

  /**
   * \brief Determine if this shape intersects another.
   *
   * First performs a fast bounding box intersection test in order to increase
   * performance when shapes are sufficiently far apart.
   *
   * Also evaluates to true if one shape is enclosed by another.
   *
   * \param other Shape to check intersection with
   * \return True if shapes intersect
   */
  virtual bool intersects(const Shape &other) const;

protected:
  /**
   * \brief Checks for equality between this shape and another shape of the same
   *        subclass.
   *
   * Should always returns false if other is not the same type as this.
   *
   * \param other Other shape
   * \return True if shapes are equal
   */
  virtual bool compare(const Shape &other) const = 0;

  Vector2D m_position; //!< Position of the shape
};

#endif
