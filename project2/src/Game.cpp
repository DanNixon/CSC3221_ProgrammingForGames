/** \file */

#include <sstream>
#include "GameImpl.h"
#include "BoundingBox.h"

/**
 * \brief Entry point.
 *
 * Usage: [num shapes] [max num parameters]
 */
int main(int argc, char *argv[])
{
  int numShapes = 50;
  int maxIterations = 10;

  /* Parse number of shapes from command line */
  if (argc > 1)
  {
    std::stringstream numShapesStr(argv[1]);
    numShapesStr >> numShapes;
    if (!numShapesStr)
    {
      std::cerr << "Failed to parse number of shapes: " << argv[1]
                << std::endl;
      return 2;
    }
  }

  /* Parse max iteration limit form command line */
  if (argc > 2)
  {
    std::stringstream maxIterationsStr(argv[2]);
    maxIterationsStr >> maxIterations;
    if (!maxIterationsStr)
    {
      std::cerr << "Failed to parse maximum iteration: " << argv[2]
                << std::endl;
      return 2;
    }
  }

  std::cout << "Num. shapes: " << numShapes << std::endl
            << "Max. iterations: " << maxIterations << std::endl;

  /* Bounding box for 2D game area */
  const BoundingBox box(0, 0, 100, 100);
  std::cout << "Game area: " << box << std::endl;

  GameImpl game(box, std::cout);

  /* Generate initial list of shapes */
  game.generateInitialShapes(numShapes, 5.0);
  std::cout << "INITIAL SHAPES:" << std::endl;
  game.printAllShapes();

  for (int i = 0; i < maxIterations; i++)
  {
    std::cout << std::endl << "ITERATION: " << (i + 1) << std::endl;

    game.applyRandomOffsets();
    game.cullOverlapping();

    std::cout << "Shapes remaining: " << game.numShapes() << std::endl;

    /* Exit if all shapes removed */
    if (game.numShapes() == 0)
      break;
  }

  return 0;
}
