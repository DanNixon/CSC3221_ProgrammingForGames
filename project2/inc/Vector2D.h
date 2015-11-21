#ifndef __GEOMETRY_VECTOR2D_H_
#define __GEOMETRY_VECTOR2D_H_

#include <iostream>

class Vector2D
{
public:
  Vector2D();
  Vector2D(double x, double y);
  Vector2D(const Vector2D &other);
  Vector2D(Vector2D *other);

  void operator=(const Vector2D &other);

  bool operator==(const Vector2D &other) const;
  bool operator!=(const Vector2D &other) const;

  Vector2D operator+(const Vector2D &rhs) const;
  void operator +=(const Vector2D &rhs);
  Vector2D operator-(const Vector2D &rhs) const;
  void operator -=(const Vector2D &rhs);
  Vector2D operator*(double rhs) const;
  void operator *=(double rhs);
  Vector2D operator/(double rhs) const;
  void operator /=(double rhs);

  double getX() const;
  double getY() const;

  double operator[](const int index) const;

  friend std::ostream &operator<<(std::ostream &stream, const Vector2D &v);

private:
  double m_x;
  double m_y;
};

std::istream &operator>>(std::istream &stream, Vector2D &v);

#endif
