/** \file */

#include "BoundingBox.h"

#include <stdexcept>
#include "Vector2D.h"

/**
 * \brief Creates a new bounding box with zero area.
 */
BoundingBox::BoundingBox()
    : m_lowerLeft(new Vector2D())
    , m_upperRight(new Vector2D())
{
}

/**
 * \brief Creates a new bounding box with specified coordinates as vectors.
 *
 * \param lowerLeft Vector defining lower left vertex
 * \param upperRight Vector defining upper right vertex
 */
BoundingBox::BoundingBox(const Vector2D &lowerLeft, const Vector2D &upperRight)
    : m_lowerLeft(new Vector2D(lowerLeft))
    , m_upperRight(new Vector2D(upperRight))
{
  if (*m_lowerLeft > *m_upperRight)
    std::swap(m_lowerLeft, m_upperRight);
}

/**
 * \brief Creates a new bounding box with specified coordinates of each vertex.
 *
 * \param lowerLeftX X position of lower left vertex
 * \param lowerLeftY Y position of lower left vertex
 * \param upperRightX X position of upper right vertex
 * \param upperRightY Y position of upper right vertex
 */
BoundingBox::BoundingBox(double lowerLeftX, double lowerLeftY,
                         double upperRightX, double upperRightY)
    : m_lowerLeft(new Vector2D(lowerLeftX, lowerLeftY))
    , m_upperRight(new Vector2D(upperRightX, upperRightY))
{
  if (*m_lowerLeft > *m_upperRight)
    std::swap(m_lowerLeft, m_upperRight);
}

/**
 * \brief Creates a copy of an existing BoundingBox.
 *
 * \param other BoundingBox to copy
 */
BoundingBox::BoundingBox(const BoundingBox &other)
    : m_lowerLeft(new Vector2D(other.m_lowerLeft))
    , m_upperRight(new Vector2D(other.m_upperRight))
{
}

BoundingBox::~BoundingBox()
{
  delete m_lowerLeft;
  delete m_upperRight;
}

/**
 * \brief Copies vertices from another BoundingBox.
 *
 * \param other BoundingBox to copy
 */
BoundingBox &BoundingBox::operator=(const BoundingBox &other)
{
  if (this == &other)
    return *this;

  delete m_lowerLeft;
  delete m_upperRight;

  m_lowerLeft = new Vector2D(other.m_lowerLeft);
  m_upperRight = new Vector2D(other.m_upperRight);

  return *this;
}

/**
 * \brief Tests for equality with another BoundingBox.
 *
 * \param other BoundingBox to compare to
 * \return True of both vertices match
 */
bool BoundingBox::operator==(const BoundingBox &other) const
{
  return (*m_lowerLeft == *(other.m_lowerLeft)) &&
         (*m_upperRight == *(other.m_upperRight));
}

/**
 * \brief Tests for inequality with another BoundingBox.
 *
 * \param other BoundingBox to compare to
 * \return True of either vertices differ
 */
bool BoundingBox::operator!=(const BoundingBox &other) const
{
  return !(this->operator==(other));
}

/**
 * \brief Offsets both vertices of a BoundingBox by a Vector2D.
 *
 * \param rhs Vector to offset by
 * \return Offset BoundingBox
 */
BoundingBox BoundingBox::operator+(const Vector2D &rhs) const
{
  BoundingBox result(*this);
  result += rhs;
  return result;
}

/**
 * \brief Offsets both vertices of this BoundingBox by a Vector2D.
 *
 * \param rhs Vector to offset by
 */
void BoundingBox::operator+=(const Vector2D &rhs)
{
  (*m_lowerLeft) += rhs;
  (*m_upperRight) += rhs;
}

/**
 * \brief Offsets both vertices of a BoundingBox by the negation of a Vector2D.
 *
 * \param rhs Vector to offset by
 * \return Offset BoundingBox
 */
BoundingBox BoundingBox::operator-(const Vector2D &rhs) const
{
  BoundingBox result(*this);
  result -= rhs;
  return result;
}

/**
 * \brief Offsets both vertices of this BoundingBox by the negation of a
 *Vector2D.
 *
 * \param rhs Vector to offset by
 */
void BoundingBox::operator-=(const Vector2D &rhs)
{
  (*m_lowerLeft) -= rhs;
  (*m_upperRight) -= rhs;
}

/**
 * \brief Calculates the size of this BoundingBox.
 *
 * \return Vector denoting size of box
 */
Vector2D BoundingBox::size() const
{
  return *m_upperRight - *m_lowerLeft;
}

/**
 * \brief Gets the lower left hand side vertex of the box.
 *
 * \return Position of lower left vertex
 */
Vector2D BoundingBox::getLowerLeft() const
{
  return *m_lowerLeft;
}

/**
 * \brief Gets the upper right hand side vertex of the box.
 *
 * \return Position of upper right vertex
 */
Vector2D BoundingBox::getUpperRight() const
{
  return *m_upperRight;
}

/**
 * \brief Gets the upper left hand side vertex of the box.
 *
 * \return Position of upper left vertex
 */
Vector2D BoundingBox::getUpperLeft() const
{
  return Vector2D(m_lowerLeft->getX(), m_upperRight->getY());
}

/**
 * \brief Gets the lower right hand side vertex of the box.
 *
 * \return Position of lower right vertex
 */
Vector2D BoundingBox::getLowerRight() const
{
  return Vector2D(m_upperRight->getX(), m_lowerLeft->getY());
}

/**
 * \brief Gets the position of the centre of the BoundingBox.
 *
 * \return Position of the centre of the box
 */
Vector2D BoundingBox::getCentre() const
{
  Vector2D s = size();
  s /= 2;

  return *m_lowerLeft + s;
}

/**
 * \brief Gets the direction of the relative position
 *        between this BoundingBox and another.
 *
 * \param other BoundingBox in direction
 * \return Relative position of other to this
 */
Vertex BoundingBox::getRelativePosition(const BoundingBox &other) const
{
  const Vector2D &thisCentre = getCentre();

  if (other.vertexOut(V_LOWERLEFT, thisCentre))
    return V_LOWERLEFT;
  else if (other.vertexOut(V_LOWERRIGHT, thisCentre))
    return V_LOWERRIGHT;
  else if (other.vertexOut(V_UPPERLEFT, thisCentre))
    return V_UPPERLEFT;
  else if (other.vertexOut(V_UPPERRIGHT, thisCentre))
    return V_UPPERRIGHT;

  return V_UNDEFINED;
}

/**
 * \brief Determines if this BoundingBox is enclosed by another.
 *
 * \param other BoundingBox to test
 * \return Extent to which box is enclosed
 */
Vertex BoundingBox::boundingBoxEnclosed(const BoundingBox &other) const
{
  bool lowerLeftOut = vertexOut(V_LOWERLEFT, *(other.m_lowerLeft));
  bool upperRightOut = vertexOut(V_UPPERRIGHT, *(other.m_upperRight));
  bool lowerRightOut = vertexOut(V_LOWERRIGHT, other.getLowerRight());
  bool upperLeftOut = vertexOut(V_UPPERLEFT, other.getUpperLeft());

  if (lowerLeftOut)
    return V_LOWERLEFT;
  else if (upperRightOut)
    return V_UPPERRIGHT;
  else if (lowerRightOut)
    return V_LOWERRIGHT;
  else if (upperLeftOut)
    return V_UPPERLEFT;

  return V_UNDEFINED;
}

/**
 * \brief Determines if this BoundingBox is intersected by another.
 *
 * \param other BoundingBox to test
 * \return True if boxes overlap
 */
bool BoundingBox::intersects(const BoundingBox &other) const
{
  return !(m_lowerLeft->getX() >= other.m_upperRight->getX() ||
           m_lowerLeft->getY() >= other.m_upperRight->getY() ||
           m_upperRight->getX() <= other.m_lowerLeft->getX() ||
           m_upperRight->getY() <= other.m_lowerLeft->getY());
}

bool BoundingBox::vertexOut(Vertex v, const Vector2D &reference) const
{
  switch (v)
  {
  case V_LOWERLEFT:
    return *m_lowerLeft <= reference;
  case V_UPPERRIGHT:
    return *m_upperRight >= reference;
  case V_LOWERRIGHT:
  {
    const Vector2D &lowerRight = getLowerRight();
    return (lowerRight.getX() >= reference.getX() &&
            lowerRight.getY() <= reference.getY());
  }
  case V_UPPERLEFT:
  {
    const Vector2D &upperLeft = getUpperLeft();
    return (upperLeft.getX() <= reference.getX() &&
            upperLeft.getY() >= reference.getY());
  }
  default:
    throw std::runtime_error("Invalid vertex parameter");
  }
}

/**
 * \brief Outputs a BoundingBox to a stream
 *
 * In format "BoundingBox[LowerLeft[x1,y1],UpperRight[x2,y2]]" where x1 and y2
 * denote the position of the lower left hand vertex and x2 and y2 denote the
 * position of the upper right vertex.
 *
 * \param stream Reference to the output stream
 * \param b BoundingBox to output
 * \return Reference to the output stream
 */
std::ostream &operator<<(std::ostream &stream, const BoundingBox &b)
{
  stream << "BoundingBox[LowerLeft" << *(b.m_lowerLeft) << ",UpperRight"
         << *(b.m_upperRight) << "]";
  return stream;
}

/**
 * \brief Creates a BoundingBox from input from a stream.
 *
 * In format "BoundingBox[LowerLeft[x1,y1],UpperRight[x2,y2]]" where x1 and y2
 * denote the position of the lower left hand vertex and x2 and y2 denote the
 * position of the upper right vertex.
 *
 * \param stream Reference to the input stream
 * \param b Reference to BoundingBox to be created
 * \return Reference to the input stream
 */
std::istream &operator>>(std::istream &stream, BoundingBox &b)
{
  const int n = 100;

  Vector2D lowerRight, upperLeft;

  stream.ignore(n, 't');
  stream >> lowerRight;

  stream.ignore(n, 't');
  stream >> upperLeft;

  stream.ignore(n, ']');

  b = BoundingBox(lowerRight, upperLeft);
  return stream;
}
