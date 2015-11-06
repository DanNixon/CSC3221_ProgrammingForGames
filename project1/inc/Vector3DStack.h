#ifndef _VECTOR3DSTACK_H_
#define _VECTOR3DSTACK_H_

#include <iostream>

class Vector3DStack
{
public:
  Vector3DStack();
  Vector3DStack(const Vector3DStack &other);
  Vector3DStack(const double x, const double y, const double z);
  ~Vector3DStack();

  void operator=(const Vector3DStack &other);

  bool operator==(const Vector3DStack &other) const;
  bool operator!=(const Vector3DStack &other) const;

  void setX(double x);
  double getX() const;

  void setY(double y);
  double getY() const;

  void setZ(double z);
  double getZ() const;

  double magnitude() const;
  Vector3DStack getUnitVector() const;
  Vector3DStack getOrthogonalUnitVector(const Vector3DStack &other) const;

  Vector3DStack operator+(const Vector3DStack &rhs) const;
  Vector3DStack operator-(const Vector3DStack &rhs) const;

  Vector3DStack operator*(const double rhs) const;
  Vector3DStack operator/(const double rhs) const;

  double operator*(const Vector3DStack &rhs) const;
  Vector3DStack operator%(const Vector3DStack &rhs) const;

  double operator[](const int index) const;
  double &operator[](const int index);

  friend std::ostream &operator<<(std::ostream &stream, const Vector3DStack &q);

private:
  double m_x;
  double m_y;
  double m_z;
};

std::istream &operator>>(std::istream &stream, Vector3DStack &q);

#endif
