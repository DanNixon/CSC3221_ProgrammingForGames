/** \file */

#include <cstdlib>
#include <typeinfo>
#include <vector>

#include "BoundingBox.h"
#include "Shape.h"
#include "Square.h"
#include "Circle.h"

/**
 * \brief A vector containing pointers to Shape objects.
 */
typedef std::vector<Shape *> ShapeVect;

/**
 * \brief An iterator over a vector containing pointers to Shape objects.
 */
typedef std::vector<Shape *>::iterator ShapeVectIt;

/**
 * \brief Generates a random double between two limits.
 *
 * \param lower Lower limit
 * \param upper Upper limit
 * \return Random double
 */
double randomBetween(double lower, double upper)
{
  double v = (double) rand() / RAND_MAX;
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
void generateRandomShapes(ShapeVect &shapes, const BoundingBox &clamp,
                          int numShapes, const double maxDim)
{
  for (int i = 0; i < numShapes; i++)
  {
    Shape * s = NULL;
    if (rand() % 2 == 0)
      s = new Square(randomBetween(0, maxDim), randomBetween(0, maxDim));
    else
      s = new Circle(randomBetween(0, maxDim));

    Vector2D pos(randomBetween(clamp.getLowerLeft()[0], clamp.getUpperRight()[0]),
                 randomBetween(clamp.getLowerLeft()[1], clamp.getUpperRight()[1]));
    s->setPosition(pos, clamp);

    shapes.push_back(s);
  }
}

/**
 * \brief Apply a random positional offset to each shape in a vector.
 *
 * \param shapes Vector of shapes to offset
 */
void applyRandomOffsets(ShapeVect &shapes)
{
  for (ShapeVectIt it = shapes.begin(); it != shapes.end(); ++it)
  {
    // TODO
  }
}

/**
 * \brief Remove overlapping shapes and output details of shapes removes to a
 *        stream.
 *
 * \param shapes Vector of shapes
 * \param stream Stream to output to
 */
void cullOverlapping(ShapeVect &shapes, std::ostream &stream)
{
  // TODO
}

/**
 * \brief Prints a vector of shapes to a stream.
 *
 * \param shapes Vector of shapes
 * \param stream Stream to output to
 */
void printAllShapes(ShapeVect &shapes, std::ostream &stream)
{
  unsigned int i = 0;
  for (ShapeVectIt it = shapes.begin(); it != shapes.end(); ++it)
  {
    stream << i << ": ";

    const std::type_info &instanceType = typeid(*(*it));
    if (instanceType == typeid(Square))
      stream << *((Square *) *it);
    else if (instanceType == typeid(Circle))
      stream << *((Circle *) *it);

    stream << std::endl;
    i++;
  }
}

int main(void)
{
  const unsigned int initialNumShapes = 50;
  const unsigned int maxIterations = 5;

  // Bounding box for 2D game area
  BoundingBox box(0, 0, 100, 100);
  std::cout << box << std::endl;

  // Generate initial list of shapes
  ShapeVect shapes;
  shapes.reserve(initialNumShapes);
  generateRandomShapes(shapes, box, initialNumShapes, 5);
  std::cout << "INITIAL SHAPES:" << std::endl;
  printAllShapes(shapes, std::cout);

  for (unsigned int i = 0; i < maxIterations; i++)
  {
    std::cout << std::endl << "ITERATION: " << (i + 1) << std::endl;

    applyRandomOffsets(shapes);
    cullOverlapping(shapes, std::cout);
    /* printAllShapes(shapes, std::cout); */
  }

  return 0;
}
