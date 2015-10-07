#ifndef _VECTOR3DSTACK_H_
#define _VECTOR3DSTACK_H_

class Vector3DStack
{
public:
  Vector3DStack();
  Vector3DStack(int x, int y, int z);

  int getX() const;
  int getY() const;
  int getZ() const;

  int magnitude() const;
  Vector3DStack getUnitVector() const;

  Vector3DStack operator+(const Vector3DStack &rhs);
  Vector3DStack operator-(const Vector3DStack &rhs);

  Vector3DStack operator*(const int rhs);
  Vector3DStack operator/(const int rhs);

  int operator*(const Vector3DStack &rhs);
  Vector3DStack operator%(const Vector3DStack &rhs);

private:
  int m_x;
  int m_y;
  int m_z;
};

#endif
