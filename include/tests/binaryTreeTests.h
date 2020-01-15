#ifndef BINARYTREETESTS_H
# define BINARYTREETESTS_H

#include <iostream>
#include <string>
#include <iterator>

#include <stdint.h>

#include "nodeTests.h"

#include "../models/RBTree.h"
#include "../io/io.h"

using namespace std;


/* Start of Binary Search Tree Tests */
bool BSTreeTest_All(bool noisy);
uint8_t inOrder_BSTreeTest(bool noisy);
uint8_t preOrderTest(bool noisy);
uint8_t postOrderTest(bool noisy);
uint8_t Search_BSTreeTest();
uint8_t Minimum_BSTreeTest();
uint8_t Maximum_BSTreeTest();
uint8_t Successor_BSTreeTest();
uint8_t Predecessor_BSTreeTest();
uint8_t makeTreeFromPreOrder_BSTreeTest(bool noisy);
/* End of Binary Search Tree Tests */


#endif
