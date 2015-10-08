#include <cstdlib>

#include "Vector3DStack.h"
#include "Quaternion.h"

#define TH 0.0001

int result = 0;

#define TS_ASSERT_EQUALS(a, b) { if (!(a == b)) result = 1; }
#define TS_ASSERT_DIFFERS(a, b) { if (a == b) result = 1; }
#define TS_ASSERT_DELTA(a, b, th) { if (abs(a - b) > th) result = 1; }

//TODO: Test functions

int main()
{
  //TODO: Test function calls

  return result;
}
