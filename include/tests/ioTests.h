#ifndef IOTESTS_H
# define IOTESTS_H

#include <iostream> /*For cout */
#include <string> /* For the String data type */
#include <iterator> /* For the iterator data type when iterating vectors */

#include <stdint.h> /* For uint8_t */

#include "nodeTests.h"

#include "../models/RBTree.h"
#include "../io/io.h"

using namespace std;

/* Start of IO Tests */

bool IOTests_ALL(bool noisy);

uint8_t parseNodesTest(bool noisy);
uint8_t parseThreadsTest(bool noisy);
uint8_t parseCommandsTest(bool noisy);
uint8_t parseFileTest(bool noisy);

/* End of IO Tests */


#endif
