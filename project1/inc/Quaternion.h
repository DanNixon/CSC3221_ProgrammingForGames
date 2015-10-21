#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <iostream>

class Quaternion
{
public:
  Quaternion();
  Quaternion(const double w);
  Quaternion(const double w, const double i, const double j, const double k);
  Quaternion(const Quaternion &other);
  ~Quaternion();

  void operator=(const Quaternion &rhs);

  bool operator==(const Quaternion &rhs) const;
  bool operator!=(const Quaternion &rhs) const;

  double getReal() const;
  double getI() const;
  double getJ() const;
  double getK() const;

  double magnitude() const;

  Quaternion operator+(const Quaternion &rhs) const;
  Quaternion operator-(const Quaternion &rhs) const;
  Quaternion operator*(const Quaternion &rhs) const;

private:
  double m_w;
  double m_i;
  double m_j;
  double m_k;
};

std::ostream &operator<<(std::ostream &stream, const Quaternion &q);
std::istream &operator>>(std::istream &stream, Quaternion &q);

#endif
