#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <iostream>

/*
 * Forward declare Vector3DStack class
 * (avoids including headers within other headers, saves compile time on much
 * larger projects)
 */
class Vector3DStack;

class Quaternion
{
public:
  Quaternion();
  Quaternion(const double w);
  Quaternion(const double w, const double i, const double j, const double k);
  Quaternion(const double angle, const Vector3DStack &axis);
  Quaternion(const Vector3DStack &v0, const Vector3DStack &v1);
  Quaternion(const Quaternion &other);
  ~Quaternion();

  void operator=(const Quaternion &rhs);

  bool operator==(const Quaternion &rhs) const;
  bool operator!=(const Quaternion &rhs) const;

  void setReal(double w);
  double getReal() const;

  void setI(double i);
  double getI() const;

  void setJ(double j);
  double getJ() const;

  void setK(double k);
  double getK() const;

  double magnitude() const;

  Quaternion operator+(const Quaternion &rhs) const;
  Quaternion operator-(const Quaternion &rhs) const;
  Quaternion operator*(const Quaternion &rhs) const;

  double operator[](const int index) const;
  double& operator[](const int index);

  Quaternion conjugate() const;
  Quaternion inverse() const;

  Vector3DStack rotateVector(const Vector3DStack &vector) const;

  friend std::ostream &operator<<(std::ostream &stream, const Quaternion &q);

private:
  double m_w;
  double m_i;
  double m_j;
  double m_k;
};

std::istream &operator>>(std::istream &stream, Quaternion &q);

#endif
