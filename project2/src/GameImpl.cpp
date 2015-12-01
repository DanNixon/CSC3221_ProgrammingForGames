/** \file */

#include "GameImpl.h"

#include <algorithm>
#include <ctime>

#include "BoundingBox.h"
#include "Shape.h"
#include "Square.h"
#include "Circle.h"

/**
 * \brief Creates a new instance of the game.
 *
 * \param clamp BoundingBox defining game area
 * \param stream Stream to print output to
 */
GameImpl::GameImpl(const BoundingBox &clamp, std::ostream &stream)
    : m_clamp(clamp)
    , m_stream(stream)
{
  // Seed random number generator
  srand(time(NULL));
}

GameImpl::~GameImpl()
{
}

/**
 * \brief Generates random shapes and adds them to a vector.
 *
 * Type of shape (Square or Circle) is randomly selected.
 *
 * Generates random values for position and size, position is contrained by the
 * BoundingBox passed to the constructor, size is constrained by maxDimension.
 *
 * Random positions are chosen until a valid one which keeps the shape within
 * the game area is found.
 *
 * \param numShapes Number of shapes to generate
 * \param maxDimension Maximum dimension of shapes
 */
void GameImpl::generateInitialShapes(int numShapes, double maxDimension)
{
  for (int i = 0; i < numShapes; i++)
  {
    Shape *s = NULL;
    if (rand() % 2 == 0)
      s = new Square(random(0, maxDimension), random(0, maxDimension));
    else
      s = new Circle(random(0, maxDimension));

    /* Generate random positions until a valid one is found */
    Vector2D pos;
    do
    {
      pos = Vector2D (random(m_clamp.getLowerLeft()[0], m_clamp.getUpperRight()[0]),
                      random(m_clamp.getLowerLeft()[1], m_clamp.getUpperRight()[1]));
    }
    while(!s->setPosition(pos, m_clamp));

    m_shapes.push_back(s);
  }
}

/**
 * \brief Apply a random positional offset to each shape in a vector.
 *
 * Random offsets are chosen until a valid one which keeps the shape within the
 * game area is found.
 */
void GameImpl::applyRandomOffsets()
{
  const double lower = -2.0;
  const double upper = 2.0;

  for (ShapeListIt it = m_shapes.begin(); it != m_shapes.end(); ++it)
  {
    /* Generate random offsets until a valid one is found */
    Vector2D offset;
    do
    {
      offset = Vector2D(random(lower, upper), random(lower, upper));
    }
    while(!(*it)->offsetPositionBy(offset, m_clamp));
  }
}

/**
 * \brief Remove overlapping shapes and output details of shapes removes to a
 *        stream.
 */
void GameImpl::cullOverlapping()
{
  for (ShapeListIt outerIt = m_shapes.begin(); outerIt != m_shapes.end();)
  {
    bool removeFlag = false;

    for (ShapeListIt innerIt = m_shapes.begin(); innerIt != m_shapes.end();)
    {
      if (outerIt == innerIt)
      {
        ++innerIt;
        continue;
      }

      if ((*outerIt)->intersects(*(*innerIt)))
      {
        m_stream << *(*outerIt) << " INTERSETCS " << *(*innerIt) << std::endl;
        removeFlag = true;

        innerIt = m_shapes.erase(innerIt);
      }
      else
        ++innerIt;
    }

    if (removeFlag)
      outerIt = m_shapes.erase(outerIt);
    else
      ++outerIt;
  }
}

/**
 * \brief Prints a vector of shapes to a stream.
 */
void GameImpl::printAllShapes()
{
  unsigned int i = 0;
  for (ShapeListIt it = m_shapes.begin(); it != m_shapes.end(); ++it)
  {
    m_stream << i << ": " << *(*it) << std::endl;
    i++;
  }
}

/**
 * \brief Generates a random double between two limits.
 *
 * \param lower Lower limit
 * \param upper Upper limit
 * \return Random double
 */
double GameImpl::random(double lower, double upper) const
{
  double v = (double)rand() / RAND_MAX;
  return lower + (v * (upper - lower));
}

/**
 * \brief Returns the number of shapes in the game.
 *
 * \return NUmber of shapes
 */
size_t GameImpl::numShapes() const
{
  return m_shapes.size();
}
