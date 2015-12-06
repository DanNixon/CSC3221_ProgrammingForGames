/** \file */

#ifndef __GAMEIMPL_H_
#define __GAMEIMPL_H_

#include <cstdlib>
#include <ostream>
#include <list>

class BoundingBox;
class Shape;

/**
 * \brief A list containing pointers to Shape objects.
 */
typedef std::list<Shape *> ShapeList;

/**
 * \brief An iterator over a list containing pointers to Shape objects.
 */
typedef std::list<Shape *>::iterator ShapeListIt;

/**
 * \class GameImpl
 * \brief A class to represent that state machine of the game described in the
 *        spec.
 */
class GameImpl
{
  public:
    GameImpl(const BoundingBox &clamp, std::ostream &stream);
    ~GameImpl();

    void generateInitialShapes(int numShapes, double maxDimension);
    void applyRandomOffsets(double maxOffset);
    bool cullOverlapping();

    void printAllShapes();
    double random(double lower, double upper) const;
    size_t numShapes() const;

  private:
    ShapeList m_shapes;
    const BoundingBox &m_clamp;
    std::ostream &m_stream;
};

#endif
