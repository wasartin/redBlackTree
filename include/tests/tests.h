#ifndef TESTS_H
# define TESTS_H

#include <iostream>
#include <string>
#include <iterator>

#include <stdint.h>


#include "../models/RBTree.h"
#include "../io/io.h"


#include "nodeTests.h"
#include "binaryTreeTests.h"
#include "ioTests.h"

using namespace std;


bool runAllTests(bool noisy);

/* Start of Red Black Tree Tests */
uint8_t RBTreePropertyTests_All(RBTree *tree, bool noisy);
uint8_t RBTreePropertyOne_RBTreeTest(RBTree *tree, bool noisy);
uint8_t RBTreePropertyTwo_RBTreeTest(RBTree *tree, bool noisy);
uint8_t RBTreePropertyThree_RBTreeTest(RBTree *tree, bool noisy);
uint8_t RBTreePropertyFour_RBTreeTest(RBTree *tree, bool noisy);
uint8_t RBTreePropertyFive_RBTreeTest(RBTree *tree, bool noisy);

bool RBTreeFunctionTests_All(bool noisy);
uint8_t RBInsert_RBTreeTest(bool noisy);
uint8_t RBDelete_RBTreeTest(bool noisy);

/* End of Red Black Tree Tests */

/* Start of Misc Tests */

/* End of Misc Tests */

#endif
