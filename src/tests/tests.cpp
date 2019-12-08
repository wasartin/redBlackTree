#include "../../include/tests/tests.h"

//Look this up later
// https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top

void inputNodes_fromPictureExample(vector<Node> *input){
  input->push_back(node_init(NULL, 41, RED, 1));
  input->push_back(node_init(NULL, 38, RED, 1));
  input->push_back(node_init(NULL, 31, RED, 1));
  input->push_back(node_init(NULL, 19, RED, 1));
  input->push_back(node_init(NULL, 12, RED, 1));
}

void inputNodesARR_fromPictureExample(Node *input){
  input[0] = node_init(NULL, 41, RED, 1);
  input[1] = node_init(NULL, 38, RED, 1);
  input[2] = node_init(NULL, 31, RED, 1);
  input[3] = node_init(NULL, 19, RED, 1);
  input[4] = node_init(NULL, 12, RED, 1);
}

void initTreeWithNodes_ARR(RBTree *tree, Node *input){
  inputNodesARR_fromPictureExample(input);
  for(uint8_t i = 0; i < 5; i++){
    RBInsert(tree, &input[i]);
  }
}

void initTreeWithNodes(RBTree *tree, vector<Node> *input){

  inputNodes_fromPictureExample(input);
  for (vector<Node>::iterator i = input->begin(); i != input->end(); ++i){
        RBInsert(tree, &*i);
  }
}

bool runAllTests(bool noisy){

  bool nodes = NodeTest_All(noisy);
  bool io = IOTests_ALL(noisy);
  bool bstTree = BSTreeTest_All(noisy);
  bool rbtree = RBTreeFunctionTests_All(noisy);

  bool result = nodes && io && bstTree && rbtree;
  return result;
}


/* Start of RBTree Tests */
bool RBTreeFunctionTests_All(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 9;

  //Make the tree just for the rbTreePropTests
  Node *inputNodes = (Node*)malloc(5 * sizeof(*inputNodes));
  RBTree *treeFromSampleText = new RBTree();
  initTreeWithNodes_ARR(treeFromSampleText, inputNodes);

  uint8_t insertTest = RBInsert_RBTreeTest(noisy);

  uint8_t rbTreeProps = RBTreePropertyTests_All(treeFromSampleText, noisy);
  uint8_t rbDeleteTest = RBDelete_RBTreeTest(noisy);

  correct = insertTest + rbTreeProps + rbDeleteTest;
  if(noisy){
    cout << "\tRBTree Tests: " << +(correct) << "/" << +(expected) << endl;
    cout << "\t\tRBTree Property Tests: " << +(rbTreeProps) << "/" << 5 << " passed" <<  endl;
    cout << "\t\tRBTree Insert Tests: " << +(insertTest) << "/" << 3 << " passed" << endl;
    cout << "\t\tRBTree Delete Tests: " << +(rbDeleteTest) << "/" << 1 << " passed" << endl;
  }

  //Free the tree for the rbTreeTests
  free(inputNodes);
  delete treeFromSampleText;
  return (correct == expected);
}

uint8_t RBTreePropertyTests_All(RBTree *tree, bool noisy){
  uint8_t correct = 0;
  uint8_t prop1 = RBTreePropertyOne_RBTreeTest(tree, noisy);
  uint8_t prop2 = RBTreePropertyTwo_RBTreeTest(tree, noisy);
  uint8_t prop3 = RBTreePropertyThree_RBTreeTest(tree, noisy);
  uint8_t prop4 = RBTreePropertyFour_RBTreeTest(tree, noisy);
  uint8_t prop5 = RBTreePropertyFive_RBTreeTest(tree, noisy);

  correct = prop1 + prop2 + prop3 + prop4 + prop5;
  return correct;
}

/**
 * Every node is either red or black
 */
uint8_t RBTreePropertyOne_RBTreeTest(RBTree *tree, bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 5;

  vector<Node> inOrderNodes = InOrder(tree->getRoot());
  for(vector<Node>::iterator n = inOrderNodes.begin(); n != inOrderNodes.end(); ++n){
      if(n->color == RED || n->color == BLACK) correct++;
  }

  if(correct == expected) return 1;

  return 0;
}

/**
 * The root node is black
 */
uint8_t RBTreePropertyTwo_RBTreeTest(RBTree *tree, bool noisy){
  if(tree->getRoot()->color == BLACK) return 1;
  return 0;
}

/**
 * Every leaf (NIL) is black,
 * (And only references one node)
 */
uint8_t RBTreePropertyThree_RBTreeTest(RBTree *tree, bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 6;

  if(isNilNode(tree->getRoot()->left->left->left)) correct++;
  if(isNilNode(tree->getRoot()->left->left->right)) correct++;
  if(isNilNode(tree->getRoot()->left->right->left)) correct++;
  if(isNilNode(tree->getRoot()->left->right->right)) correct++;
  if(isNilNode(tree->getRoot()->right->right)) correct++;
  if(isNilNode(tree->getRoot()->right->left)) correct++;

  if(correct == expected) return 1;

  return 0;
}

/**
 * If a node is red, then both of its children are black
 */
uint8_t RBTreePropertyFour_RBTreeTest(RBTree *tree, bool noisy){
  vector<Node> inOrderNodes = InOrder(tree->getRoot());
  for(vector<Node>::iterator n = inOrderNodes.begin(); n != inOrderNodes.end(); ++n){
      if(n->color == RED){
        if(n->left->color != BLACK) return 0;
        if(n->right->color != BLACK) return 0;
      }
  }
  return 1;
}

/**
 * Black height
 * For each node, all simple paths from the node to descendent
 *  leaves contain the same number of Black Nodes.
 */
uint8_t RBTreePropertyFive_RBTreeTest(RBTree *tree, bool noisy){
  uint8_t expected = 3;
  uint8_t actual = getBlackHeight(tree->getRoot());

  return (actual == expected)? 1 : 0;
}

uint8_t RBInsert_RBTreeTest(bool noisy){
  uint8_t correct = 0;
  //Simple Tree
  RBTree *tree = new RBTree();

  //Node a = node_init(&tree->NIL, 5, RED, 1);
  Node a = node_init(nullptr, 5, RED, 1);
  Node b = node_init(nullptr, 10, RED, 1);
  Node c = node_init(nullptr, 20, RED, 1);

  RBInsert(tree, &a);
  if(tree->getRoot() == &a){
    correct++;
  }

  RBInsert(tree, &b);
  if(tree->getRoot() == &a && tree->getRoot()->right == &b){
    correct++;
  }

  RBInsert(tree, &c);
  if(tree->getRoot() == &b && tree->getRoot()->size == 3
    && tree->getRoot()->right == &c && tree->getRoot()->right->size == 1
    && tree->getRoot()->left == &a && tree->getRoot()->left->size == 1){
    correct++;
  }
  delete tree;
  uint8_t correct1 = (correct == 3)? 1 : 0;

  //2nd Tree
  correct = 0;
  a = node_init(NULL, 12, RED, 1);
  b = node_init(NULL, 19, RED, 1);
  c = node_init(NULL, 31, RED, 1);
  Node d = node_init(NULL, 38, RED, 1);
  Node e = node_init(NULL, 41, RED, 1);
  RBTree *tree2 = new RBTree();

  RBInsert(tree2, &a);//12
  if(tree2->getRoot()->key == 12 && tree2->getRoot()->size == 1
     && tree2->getRoot()->color == BLACK){
    correct++;
  }

  RBInsert(tree2, &b);//19
  Node *root = tree2->getRoot();
  Node *kidR = tree2->getRoot()->right;
  if(root->key == 12 && root->size == 2 && root->color == BLACK
    && kidR->key == 19 && kidR->size == 1 && kidR->color == RED){
      correct++;
  }

  RBInsert(tree2, &c);//31
  root = tree2->getRoot();//19b
  kidR = tree2->getRoot()->right;//31r
  Node *kidL = tree2->getRoot()->left;//12r
  if(root->key == 19 && root->size == 3 && root->color == BLACK
    && kidL->key == 12 && kidL->size == 1 && kidL->color == RED
    && kidR->key == 31 && kidR->size == 1 && kidR->color == RED){
      correct++;
  }

  RBInsert(tree2, &d); //38
  root = tree2->getRoot();
  kidR = root->right;
  kidL = root->left;
  Node *kidR_R = kidR->right;
  if(root->key == 19 && root->size == 4 && root->color == BLACK
     && kidR->key == 31 && kidR->size == 2 && kidR->color == BLACK
      && kidL->key == 12 && kidL->size == 1 && kidL->color == BLACK
       && kidR_R->key == 38 && kidR_R->size == 1 && kidR_R->color == RED){
      correct++;
  }

  RBInsert(tree2, &e); //41
  root = tree2->getRoot(); //19b
  kidR = root->right;    //38b
  kidL = root->left;     //12b
  kidR_R = kidR->right;  //41r
  Node *kidR_L = kidR->left;

  if(root->key == 19 && root->size == 5 && root->color == BLACK
    && kidR->key == 38 && kidR->size == 3 && kidR->color == BLACK
    && kidL->key == 12 && kidL->size == 1 && kidL->color == BLACK
    && kidR_R->key == 41 && kidR_R->size == 1 && kidR_R->color == RED
    && kidR_L->key == 31 && kidR_L->size == 1 && kidR_L->color == RED){
      correct++;
  }

  delete tree2;
  uint8_t correct2 = (correct == 5)? 1 : 0;
  correct = 0;

  // Insert example from picture in the text
  Node *inputNodes = (Node*)malloc(5 * sizeof(*inputNodes));
  RBTree *treeFromSampleText = new RBTree();
  initTreeWithNodes_ARR(treeFromSampleText, inputNodes);
  Node insertThis = node_init(NULL, 8, RED, 1);
  RBInsert(treeFromSampleText, &insertThis);
  root = treeFromSampleText->getRoot();
  Node *kidL_L_L = root->left->left->left;
  if(root->key == 38 && root->size == 6 && root->color == BLACK
  && kidL_L_L->key == 8 && kidL_L_L->size == 1 && kidL_L_L->color == RED){
    correct++;
  }

  uint8_t correct3 = (correct == 1)? 1 : 0;

  free(inputNodes);
  delete treeFromSampleText;


  return correct1 + correct2 + correct3;
}

uint8_t RBDelete_RBTreeTest(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 5;

  RBTree *treeFromSampleText = new RBTree();
  Node *inputNodes = (Node*)malloc(5 * sizeof(*inputNodes));
  initTreeWithNodes_ARR(treeFromSampleText, inputNodes);

  Node insertThis = node_init(NULL, 8, RED, 1);
  RBInsert(treeFromSampleText, &insertThis);

  RBDelete(treeFromSampleText, 8);

  vector<Node> inOrder = InOrder(treeFromSampleText->getRoot());

  uint8_t i = 0;
  string expected_value[5] = {"12b", "19r", "31b", "38b", "41b"};
  for (vector<Node>::iterator n = inOrder.begin();
                              n != inOrder.end();
                              ++n){
    if(expected_value[i++] == simpleString(&*n)) correct++;
  }

    free(inputNodes);
    delete treeFromSampleText;
  return (correct == expected) ? 1 : 0;
}

/* End of RBTree Tests */
