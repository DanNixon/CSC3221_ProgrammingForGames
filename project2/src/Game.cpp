/** \file */

#include <sstream>
#include "GameImpl.h"
#include "BoundingBox.h"

/**
 * \brief Entry point.
 *
 * Usage: [num shapes]
 */
int main(int argc, char *argv[])
{
  int numShapes = 50;

  /* Parse number of shapes from command line */
  if (argc > 1)
  {
    std::stringstream numShapesStr(argv[1]);
    numShapesStr >> numShapes;
    if (!numShapesStr)
    {
      std::cerr << "Failed to parse number of shapes: " << argv[1]
                << std::endl;
      return 1;
    }
  }

  std::cout << "Num. shapes: " << numShapes << std::endl;

  /* Bounding box for 2D game area */
  const BoundingBox box(0, 0, 100, 100);
  std::cout << "Game area: " << box << std::endl;

  GameImpl game(box, std::cout);

  /* Generate initial list of shapes */
  game.generateInitialShapes(numShapes, 5.0);
  std::cout << "INITIAL SHAPES:" << std::endl;
  game.printAllShapes();

  std::cout << std::endl;
  unsigned int iteration = 1;

  /* Iterate while more than one shape remains */
  while (game.numShapes() > 1)
  {
    game.applyRandomOffsets(2.0);

    if (game.cullOverlapping())
    {
      /* Output details if shapes were removed this iteration */
      std::cout << "After iteration " << iteration
                << ", " << game.numShapes() << " shape(s) remaining"
                << std::endl << std::endl;
    }

    iteration++;
  }

  return 0;
}
