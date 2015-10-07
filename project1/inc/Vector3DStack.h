#ifndef _VECTOR3DSTACK_H_
#define _VECTOR3DSTACK_H_

class Vector3DStack
{
public:
  Vector3DStack();
  Vector3DStack(const Vector3DStack &other);
  Vector3DStack(const double x, const double y, const double z);

  bool operator==(const Vector3DStack &other) const;
  void operator=(const Vector3DStack &other);

  double getX() const;
  double getY() const;
  double getZ() const;

  double magnitude() const;
  Vector3DStack getUnitVector() const;

  Vector3DStack operator+(const Vector3DStack &rhs) const;
  Vector3DStack operator-(const Vector3DStack &rhs) const;

  Vector3DStack operator*(const double rhs) const;
  Vector3DStack operator/(const double rhs) const;

  double operator*(const Vector3DStack &rhs) const;
  Vector3DStack operator%(const Vector3DStack &rhs) const;

private:
  double m_x;
  double m_y;
  double m_z;
};

#endif
