/** \file */

#include "GameImpl.h"
#include "BoundingBox.h"

/**
 * \brief Entry point.
 */
int main(void)
{
  // Bounding box for 2D game area
  const BoundingBox box(0, 0, 100, 100);
  std::cout << box << std::endl;

  GameImpl game(box, std::cout);

  const unsigned int maxIterations = 10;

  // Generate initial list of shapes
  game.generateInitialShapes(50, 5.0);
  std::cout << "INITIAL SHAPES:" << std::endl;
  game.printAllShapes();

  for (unsigned int i = 0; i < maxIterations; i++)
  {
    std::cout << std::endl << "ITERATION: " << (i + 1) << std::endl;

    game.applyRandomOffsets();
    game.cullOverlapping();

    /* game.printAllShapes(); */
    std::cout << "Shapes remaining: " << game.numShapes() << std::endl;
  }

  return 0;
}
