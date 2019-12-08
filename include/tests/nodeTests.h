#ifndef NODETESTS_H
# define NODETESTS_H

#include <iostream>
#include <string>
#include <iterator>

#include <stdint.h>

#include "../models/node.h"

using namespace std;

/* Start of Node Tests */
bool NodeTest_All(bool noisy);

uint8_t nodeStringTest(bool noisy);
uint8_t sizeOfNode_NodeTest(bool noisy);
uint8_t heightOfNode_NodeTest(bool noisy);
uint8_t newNode_NodeTest(bool noisy);

/* End of Node Tests */


#endif
