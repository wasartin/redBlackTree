#include "../../include/tests/binaryTreeTests.h"


void inputNodesFromFileExample(Node *nodes){
  nodes[0] = node_init(NULL, 3, RED, 1);
  nodes[1] = node_init(NULL, 7, RED, 1);
  nodes[2] = node_init(NULL, 8, RED, 1);
  nodes[3] = node_init(NULL, 10, RED, 1);
  nodes[4] = node_init(NULL, 11, RED, 1);
  nodes[5] = node_init(NULL, 18, RED, 1);
  nodes[6] = node_init(NULL, 22, RED, 1);
  nodes[7] = node_init(NULL, 26, RED, 1);
}

/* Start of Binary Tree TESTS*/
bool BSTreeTest_All(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 6;

  uint8_t inOrder = inOrder_BSTreeTest(noisy);
  uint8_t preOrder = preOrderTest(noisy);
  uint8_t postOrder = postOrderTest(noisy);
  uint8_t minimum = Minimum_BSTreeTest();
  uint8_t maximum = Maximum_BSTreeTest();
  uint8_t succ = Successor_BSTreeTest();
  uint8_t pred = Predecessor_BSTreeTest();

  correct = inOrder + preOrder + minimum + maximum + succ + pred;

  if(noisy){
    cout << "\tBS Tree Tests: " << +(correct) << "/" << +(expected) << endl;
    cout << "\t\tBS Inorder Traversal: " << +(inOrder) << "/" << 1 << endl;
    cout << "\t\tBS Preorder Traversal: " << +(preOrder) << "/" << 1 << endl;
    cout << "\t\tBS Postorder Traversal: " << +(postOrder) << "/" << 1 << endl;
    cout << "\t\tBS Minimum: " << +(minimum) << "/" << 1 << endl;
    cout << "\t\tBS Maximum: " << +(maximum) << "/" << 1 << endl;
    cout << "\t\tBS Successor: " << +(succ) << "/" << 1 << endl;
    cout << "\t\tBS Predecessor: " << +(pred) << "/" << 1 << endl;
  }

  return (correct == expected);
}

uint8_t inOrder_BSTreeTest(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 8;

  RBTree *tree = new RBTree();
  Node *inputNodes = (Node*)malloc(8 * sizeof(*inputNodes));
  inputNodesFromFileExample(inputNodes);

  uint8_t k;
  for (k = 0; k < 8; k++)  {
    RBInsert(tree, &inputNodes[k]);
  }

  vector<Node> inOrder = InOrder(tree->getRoot());

  uint8_t i = 0;
  string expected_value[8] = {"3b", "7r", "8b", "10b", "11b", "18r", "22b", "26r"};
  for (vector<Node>::iterator n = inOrder.begin();
                              n != inOrder.end();
                              ++n){
    if(expected_value[i++] == simpleString(&*n)) correct++;
  }
  free(inputNodes);
  delete tree;

  return (correct == expected) ? 1 : 0;
}

uint8_t preOrderTest(bool noisy){
    uint8_t correct = 0;
    uint8_t expected = 8;

    RBTree *tree = new RBTree();
    Node *inputNodes = (Node*)malloc(8 * sizeof(*inputNodes));
    inputNodesFromFileExample(inputNodes);

    uint8_t k;
    for (k = 0; k < 8; k++)  {
      RBInsert(tree, &inputNodes[k]);
    }

    vector<Node> preOrder = PreOrder(tree->getRoot());

    uint8_t i = 0;
    string expected_value[8] = {"10b", "7r", "3b", "8b", "18r", "11b", "22b", "26r"};
    for (vector<Node>::iterator n = preOrder.begin();
                                n != preOrder.end();
                                ++n){
      if(expected_value[i++] == simpleString(&*n)) correct++;
    }

    free(inputNodes);
    delete tree;

    return (correct == expected) ? 1 : 0;
}

uint8_t postOrderTest(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 8;

  RBTree *tree = new RBTree();

  Node *inputNodes = (Node*)malloc(8 * sizeof(*inputNodes));
  inputNodesFromFileExample(inputNodes);

  uint8_t k;
  for (k = 0; k < 8; k++)  {
    RBInsert(tree, &inputNodes[k]);
  }

  vector<Node> postOrder = PostOrder(tree->getRoot());

  uint8_t i = 0;
  string expected_value[8] = {"3b", "8b", "7r", "11b", "26r", "22b", "18r", "10b"};
  for (vector<Node>::iterator n = postOrder.begin();
                              n != postOrder.end();
                              ++n){
    if(expected_value[i++] == simpleString(&*n)) correct++;
  }

  free(inputNodes);
  delete tree;

  return (correct == expected) ? 1 : 0;
}

uint8_t Search_BSTreeTest(){

  return 0;
}

uint8_t Minimum_BSTreeTest(){
  uint8_t correct = 0;
  uint8_t expected = 8;

  RBTree *tree = new RBTree();
  Node *inputNodes = (Node*)malloc(8 * sizeof(*inputNodes));
  inputNodesFromFileExample(inputNodes);

  uint8_t k;
  for (k = 0; k < 8; k++)  {
    RBInsert(tree, &inputNodes[k]);
  }

  vector<Node> inOrder = InOrder(tree->getRoot());

  uint8_t i = 0;
  string expected_value[8] = {"3b", "3b", "8b", "3b", "11b", "11b", "22b", "26r"};//3, 7, 8, 10, 18, 11, 22, 26
  for (vector<Node>::iterator n = inOrder.begin();
                              n != inOrder.end();
                              ++n){

    if(expected_value[i++] == simpleString(Minimum(&*n))) correct++;
  }

  free(inputNodes);
  delete tree;

  return (correct == expected) ? 1 : 0;
}

uint8_t Maximum_BSTreeTest(){
  uint8_t correct = 0;
  uint8_t expected = 8;

  RBTree *tree = new RBTree();

  Node *inputNodes = (Node*)malloc(8 * sizeof(*inputNodes));
  inputNodesFromFileExample(inputNodes);

  uint8_t k;
  for (k = 0; k < 8; k++)  {
    RBInsert(tree, &inputNodes[k]);
  }

  vector<Node> inOrder = InOrder(tree->getRoot());

  uint8_t i = 0;
  string expected_value[8] = {"3b", "8b", "8b", "26r", "11b", "26r", "26r", "26r"};//3, 7, 8, 10, 18, 11, 22, 26
  for (vector<Node>::iterator n = inOrder.begin();
                              n != inOrder.end();
                              ++n){

    if(expected_value[i++] == simpleString(Maximum(&*n))) correct++;
  }

  free(inputNodes);
  delete tree;

  return (correct == expected) ? 1 : 0;
}

uint8_t Successor_BSTreeTest(){
  uint8_t correct = 0;
  uint8_t expected = 8;

  RBTree *tree = new RBTree();
  Node *inputNodes = (Node*)malloc(8 * sizeof(*inputNodes));
  inputNodesFromFileExample(inputNodes);

  uint8_t k;
  for (k = 0; k < 8; k++)  {
    RBInsert(tree, &inputNodes[k]);
  }

  vector<Node> inOrder = InOrder(tree->getRoot());

  uint8_t i = 0;
  string expected_value[8] = {"7r", "8b", "10b", "11b", "18r", "22b", "26r", "26r"};//3, 7, 8, 10, 18, 11, 22, 26
  for (vector<Node>::iterator n = inOrder.begin();
                              n != inOrder.end();
                              ++n){
    if(expected_value[i++] == simpleString(Successor(&*n))){
      correct++;
    }
  }

  free(inputNodes);
  delete tree;

  return (correct == expected) ? 1 : 0;
}

uint8_t Predecessor_BSTreeTest(){
  uint8_t correct = 0;
  uint8_t expected = 8;

  RBTree *tree = new RBTree();

  Node *inputNodes = (Node*)malloc(8 * sizeof(*inputNodes));
  inputNodesFromFileExample(inputNodes);

  uint8_t k;
  for (k = 0; k < 8; k++)  {
    RBInsert(tree, &inputNodes[k]);
  }

  vector<Node> inOrder = InOrder(tree->getRoot());

  uint8_t i = 0;
  string expected_value[8] = {"3b", "3b", "7r", "8b", "10b", "11b", "18r", "22b"};//3, 7, 8, 10, 18, 11, 22, 26
  for (vector<Node>::iterator n = inOrder.begin();
                              n != inOrder.end();
                              ++n){

    if(expected_value[i++] == simpleString(Predecessor(&*n))) correct++;
  }

  free(inputNodes);
  delete tree;

  return (correct == expected) ? 1 : 0;
}



/* End of Binary Tree Tests */
