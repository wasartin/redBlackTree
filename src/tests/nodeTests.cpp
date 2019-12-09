#include "../../include/tests/nodeTests.h"

/* All Tests for Nodes */
bool NodeTest_All(bool noisy){
  uint8_t expected = 3;

  uint8_t str =  nodeStringTest(noisy);
  uint8_t size = sizeOfNode_NodeTest(noisy);
  uint8_t createNode = newNode_NodeTest(noisy);

  uint8_t correct = str + size + createNode;

  if(noisy){
    cout << "\tNode Tests: " << +(correct) << "/" << +(expected) << endl;
    cout << "\t\tProperty tests passed: " << +(str + size) << "/" << 2 << endl;
    cout << "\t\tCreate Node, passed: " << +(createNode) << "/" << 1 << endl;
  }

  return (correct == expected);
}

uint8_t nodeStringTest(bool noisy){
  Node a = node_init(NULL, 7, RED, 10);
  Node b = node_init(NULL, 10, BLACK, 4);

  Node nil;
  nil.color = BLACK;

  if(noisy){
  }

  return (simpleString(&a) == "7r" && simpleString(&b) == "10b")? 1 : 0;

}

uint8_t sizeOfNode_NodeTest(bool noisy){
  Node a;

  uint8_t correctCount = 0;
  //uint8_t totalTests;

  if(a.size == 0){
    correctCount++;
  }
  return correctCount;
}

uint8_t heightOfNode_NodeTest(bool noisy){

  return 0;
}

uint8_t newNode_NodeTest(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 3;

  string black = "7b";
  Node blackResult = node_init_from_str(black);
  if(simpleString(&blackResult) == black) correct++;

  string red = "8r";
  Node redResult = node_init_from_str(red);
  if(simpleString(&redResult) == red) correct++;

  string nilNode = "f";
  Node nilNodeResult = node_init_from_str(nilNode);
  if(simpleString(&nilNodeResult) == nilNode) correct++;

  return (correct == expected) ? 1 : 0;
}

/* END OF NODE TESTS */
