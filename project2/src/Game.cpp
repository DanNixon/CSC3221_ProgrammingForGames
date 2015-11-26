/** \file */

#include <cstdlib>
#include <list>

#include "BoundingBox.h"
#include "Shape.h"
#include "Square.h"
#include "Circle.h"

/**
 * \brief A list containing pointers to Shape objects.
 */
typedef std::list<Shape *> ShapeList;

/**
 * \brief An iterator over a list containing pointers to Shape objects.
 */
typedef std::list<Shape *>::iterator ShapeListIt;

/**
 * \brief Generates a random double between two limits.
 *
 * \param lower Lower limit
 * \param upper Upper limit
 * \return Random double
 */
double randomBetween(double lower, double upper)
{
  double v = (double)rand() / RAND_MAX;
  return lower + (v * (upper - lower));
}

/**
 * \brief Generates random shapes and adds them to a vector.
 *
 * Type of shape (Square or Circle) is randomly selected.
 *
 * Generates random values for psoition and size, position is contrained by the
 * clamp BoundingBox, size is constrained by maxDim.
 *
 * \param shapes Reference to the vector to add shapes to
 * \param clamp BoundingBox to place shapes within
 * \param numShapes Number of shapes to generate
 * \param maxDim Maximum dimension of shapes
 */
void generateRandomShapes(ShapeList &shapes, const BoundingBox &clamp,
                          int numShapes, const double maxDim)
{
  for (int i = 0; i < numShapes; i++)
  {
    Shape *s = NULL;
    if (rand() % 2 == 0)
      s = new Square(randomBetween(0, maxDim), randomBetween(0, maxDim));
    else
      s = new Circle(randomBetween(0, maxDim));

    Vector2D pos(
        randomBetween(clamp.getLowerLeft()[0], clamp.getUpperRight()[0]),
        randomBetween(clamp.getLowerLeft()[1], clamp.getUpperRight()[1]));
    s->setPosition(pos, clamp);

    shapes.push_back(s);
  }
}

/**
 * \brief Apply a random positional offset to each shape in a vector.
 *
 * \param shapes List of shapes to offset
 * \param clamp BoundingBox to keep shapes within
 */
void applyRandomOffsets(ShapeList &shapes, const BoundingBox &clamp)
{
  const double lower = -2.0;
  const double upper = 2.0;

  for (ShapeListIt it = shapes.begin(); it != shapes.end(); ++it)
  {
    (*it)->offsetPositionBy(
        Vector2D(randomBetween(lower, upper), randomBetween(lower, upper)),
        clamp);
  }
}

/**
 * \brief Remove overlapping shapes and output details of shapes removes to a
 *        stream.
 *
 * \param shapes List of shapes
 * \param stream Stream to output to
 */
void cullOverlapping(ShapeList &shapes, std::ostream &stream)
{
  for (ShapeListIt outerIt = shapes.begin(); outerIt != shapes.end();)
  {
    bool removeFlag = false;

    for (ShapeListIt innerIt = shapes.begin(); innerIt != shapes.end();)
    {
      if (outerIt == innerIt)
      {
        ++innerIt;
        continue;
      }

      if ((*outerIt)->intersects(*(*innerIt)))
      {
        stream << *(*outerIt) << " INTERSETCS " << *(*innerIt) << std::endl;
        removeFlag = true;

        innerIt = shapes.erase(innerIt);
      }
      else
        ++innerIt;
    }

    if (removeFlag)
      outerIt = shapes.erase(outerIt);
    else
      ++outerIt;
  }
}

/**
 * \brief Prints a vector of shapes to a stream.
 *
 * \param shapes List of shapes
 * \param stream Stream to output to
 */
void printAllShapes(ShapeList &shapes, std::ostream &stream)
{
  unsigned int i = 0;
  for (ShapeListIt it = shapes.begin(); it != shapes.end(); ++it)
  {
    stream << i << ": " << *(*it) << std::endl;
    i++;
  }
}

int main(void)
{
  const unsigned int initialNumShapes = 50;
  const unsigned int maxIterations = 10;

  // Seed random number generator
  srand(time(NULL));

  // Bounding box for 2D game area
  const BoundingBox box(0, 0, 100, 100);
  std::cout << box << std::endl;

  // Generate initial list of shapes
  ShapeList shapes;
  generateRandomShapes(shapes, box, initialNumShapes, 5);
  std::cout << "INITIAL SHAPES:" << std::endl;
  printAllShapes(shapes, std::cout);

  for (unsigned int i = 0; i < maxIterations; i++)
  {
    std::cout << std::endl << "ITERATION: " << (i + 1) << std::endl;

    applyRandomOffsets(shapes, box);
    cullOverlapping(shapes, std::cout);

    /* printAllShapes(shapes, std::cout); */
    std::cout << "Shapes remaining: " << shapes.size() << std::endl;
  }

  return 0;
}
