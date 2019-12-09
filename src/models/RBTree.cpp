#include "../../include/models/RBTree.h"


//Node *buildTreeFromPreOrderNodes_Rec(string preNodes[],  int *index_ptr, int n);

RBTree::~RBTree(){
  RBTree::destroyTree();
}

void RBTree::destroyTree(){
  destroyTree(root);
}

void RBTree::destroyTree(Node *leaf){
  if(!leaf){//todo Remove null check?
    destroyTree(leaf->left);
    destroyTree(leaf->right);
    delete leaf;
  }
}

bool RBTree::isEmpty(){
  return (root->size == 0);
}

Node *RBTree::getRoot(){
  return root;
}

void RBTree::setRoot(Node *node){
    root = node;
}

Node *RBTree::getNILNode(){
  return &NIL;
}

/**
 * The number of black Nodes on any simple path, but not including
 * x, down to a leaf.
 *
 * Note: The black height of a tree is the black height of its root.
 * All simple paths haev the same number of black nodes.
 */
uint8_t getBlackHeight(Node *node_x){
  if(isNilNode(node_x)){
    return 1;
  }
  uint8_t left = getBlackHeight(node_x->left);
  uint8_t right = getBlackHeight(node_x->right);
  uint8_t maxBlackHeight = (left >= right)? left : right;
  if(node_x->color == BLACK){
    return 1 + maxBlackHeight;
  }
  return maxBlackHeight;
}

/**
 * Function for inserting intou a Red Black tree
 * Suppose node_z is to be inserted into the RBTree T.
 * Assume z.key has already been instantied
 * To insert node_z into T, we first add node_z to T as an ordinary BST,
 * and made node_z color to red. This satisfies RBTree Properties 1, 3, 5.
 * Property 2 will fail if z is the root, and Property 4 will fail if the
 * new node's parent is red.
 * RBInsertFixup recolors nodes and performs rotations to ensure that then
 * RB propertyies hold for the Tree
 * (Take From CLRS)
 *
 * Param: tree, a pointer to a Red Black tree
 * Param: node_z, a poitner to a node that will be inserted
 */
void RBInsert(RBTree *tree, Node *node_z){
  Node *node_y = tree->getNILNode();
  Node *node_x = tree->getRoot();
  while(!isNilNode(node_x)){
    node_x->size++;           //CLRS 14.1
    node_y = node_x;
    if(node_z->key < node_x->key){
      node_x = node_x->left;
    }else{
      node_x = node_x->right;
    }
  }
  node_z->parent = node_y;
  if(node_y == nullptr || isNilNode(node_y)){
    tree->setRoot(node_z);
  }
  else if(node_z->key < node_y->key){
    node_y->left = node_z;
  }else {
    node_y->right = node_z;
  }
  node_z->left = tree->getNILNode();
  node_z->right = tree->getNILNode();
  node_z->color = RED;
  RBInsertFixup(tree, node_z);
  updateNodeInfo(node_z);
  percolateUpUpdates(node_y);
}

void RBInsertFixup(RBTree *tree, Node *node_z){
  Node *node_y = tree->getNILNode();
  while(node_z->parent->color == RED){
    if(node_z->parent == node_z->parent->parent->left){
      node_y = node_z->parent->parent->right;
      if(node_y->color == RED){                          //CASE 1
        node_z->parent->color = BLACK;
        node_y->color = BLACK;
        node_z->parent->parent->color = RED;
        node_z = node_z->parent->parent;
      }else {                                           //CASE 2
        if(node_z == node_z->parent->right){
          node_z = node_z->parent;
          LeftRotate(tree, node_z);
        }
        node_z->parent->color = BLACK;                  //Case 3
        node_z->parent->parent->color = RED;
        RightRotate(tree, node_z->parent->parent);
      }
    }else{
      node_y = node_z->parent->parent->left;
      if(node_y->color == RED){                          //CASE 1
        node_z->parent->color = BLACK;
        node_y->color = BLACK;
        node_z->parent->parent->color = RED;
        node_z = node_z->parent->parent;
      }else {                                           //CASE 2
        if(node_z == node_z->parent->left){
          node_z = node_z->parent;
          RightRotate(tree, node_z);
        }
        node_z->parent->color = BLACK;                  //Case 3
        node_z->parent->parent->color = RED;
        LeftRotate(tree, node_z->parent->parent);
      }
    }
  }
  tree->getRoot()->color = BLACK;
}

void LeftRotate(RBTree *tree, Node *node_x){
  Node *node_y = node_x->right;
  node_x->right = node_y->left;
  if(!isNilNode(node_y)){
    node_y->left->parent = node_x;
  }
  node_y->parent = node_x->parent;
  if(isNilNode(node_x->parent)){
    tree->setRoot(node_y);
  }
  else if(node_x == node_x->parent->left){
    node_x->parent->left = node_y;
  }else{
    node_x->parent->right = node_y;
  }
  node_y->left = node_x;
  node_x->parent = node_y;

  updateNodesInfo(node_x, node_y);
}

void RightRotate(RBTree *tree, Node *node_x){
  Node *node_y = node_x->left;
  node_x->left = node_y->right;
  if(!isNilNode(node_y)){
    node_y->right->parent = node_x;
  }
  node_y->parent = node_x->parent;
  if(isNilNode(node_x->parent)){
    tree->setRoot(node_y);
  }
  else if(node_x == node_x->parent->right){
    node_x->parent->right = node_y;
  }else{
    node_x->parent->left = node_y;
  }
  node_y->right = node_x;
  node_x->parent = node_y;

  updateNodesInfo(node_x, node_y);
}


/**
 *
 */
void RBTransplant(RBTree *tree, Node *node_u, Node *node_v){
  //ToDo
  if(isNilNode(node_u->parent)){
    tree->setRoot(node_u);
  } else if(node_u == (node_u->parent->left)){
    node_u->parent->left = node_v;
  } else{
    node_u->parent->right = node_v;
  }
  node_v->parent = node_u->parent;
  updateNodeInfo(node_v);
}


/**
 * Private helper method used to update Node Info in Insert and Delete.
 * This only goes up the tree til it hits the root's parent (nil).
 *
 * @param v
 */
 void percolateUp(Node *node_v) {
	while(!isNilNode(node_v)) {
		updateNodeInfo(node_v);
		node_v = node_v->parent;
	}
}

/**
 *
 */
void RBDelete(RBTree *tree, uint8_t keyToDelete){
  Node *node_z;
  node_z = Search(tree->getRoot(), keyToDelete);
  if(isNilNode(node_z)){ //need to double check i return nilNode if this doesn't exist
    cout << "Error, couldn't find node with key:= " << +(keyToDelete) << endl;
  }
  Node *node_y = node_z;
  Node *node_x = tree->getNILNode();
  COLOR node_y_originalColor = node_y->color;
  if(isNilNode(node_z)){                //Case 1, delete right child
    node_x = node_z->right;
    RBTransplant(tree, node_z, node_z->right);
  } else if(isNilNode(node_z->right)){  //Case 2 (just delete left child)
    node_x = node_z->right;
    RBTransplant(tree, node_z, node_z->left);
  } else {                              //Case 3 or 4
    node_y = Minimum(node_z->right);
    node_y_originalColor = node_y->color; //is this right?
    node_x = node_y->right;
    if(node_y->parent == node_z){       //Case 4 only
      node_x->parent = node_y;
    } else{                             //Case 4
      RBTransplant(tree, node_y, node_y->right);
      node_y->right = node_z->right;
      node_y->right->parent = node_y;
    }
    RBTransplant(tree, node_z, node_y);
    node_y->left = node_z->left;
    node_y->left->parent = node_y;
    node_y->color = node_z-> color;
  }
  if(node_y_originalColor == BLACK){
    RBDeleteFixup(tree, node_x);
  }
  Node *goingUp = node_x;
  percolateUp(goingUp);
}

/**
 *
 */
void RBDeleteFixup(RBTree *tree, Node *node_x){
  while(node_x != tree->getRoot() && node_x->color != BLACK){
    if(node_x == node_x->parent->left){
      Node *node_w = node_x->parent->right;
      if(node_w->color == RED){               //Case 1: node_x's sibling w is red
        node_w->color = BLACK;
        node_x->parent->color = RED;
        LeftRotate(tree, node_x->parent);
        node_w = node_x->parent->right;
      }
      if(node_w->left->color == BLACK && node_w->right->color == BLACK){ //Case 2
        node_w->color = RED; //double check this
        node_x = node_x->parent;
      } else{ //Case 3 and 4
        if(node_w->right->color == BLACK){  //Case 3
          node_w->left->color = BLACK;
          node_w->color = RED;
          RightRotate(tree, node_w);
          node_w = node_x->parent->right;
        }
        node_w->color = node_x->parent->color;
        node_x->parent->color = BLACK;
        node_w->right->color = BLACK;
        LeftRotate(tree, node_x->parent);
        node_x = tree->getRoot();
      }
    } else { //Same as previous, but right and left are changed
      Node *node_w = node_x->parent->left;
      if(node_w->color == RED){               //Case 1: node_x's sibling w is red
        node_w->color = BLACK;
        node_x->parent->color = RED;
        RightRotate(tree, node_x->parent);
        node_w = node_x->parent->left;
      }
      if(node_w->right->color == BLACK && node_w->left->color == BLACK){ //Case 2
        node_w->color = RED; //double check this
        node_x = node_x->parent;
      } else{ //Case 3 and 4
        if(node_w->left->color == BLACK){  //Case 3
          node_w->right->color = BLACK;
          node_w->color = RED;
          LeftRotate(tree, node_w);
          node_w = node_x->parent->left;
        }
        node_w->color = node_x->parent->color;
        node_x->parent->color = BLACK;
        node_w->right->color = BLACK;
        RightRotate(tree, node_x->parent);
        node_x = tree->getRoot();
      }
    }
  }

  updateNodeInfo(node_x);
  node_x->color = BLACK;
}

RBTree static *TREE = new RBTree();

/**
 * API From Homework
 */
Node *rb_insert(uint8_t key){
  Node *node;
  node = {};
  node_init(node, key);
  RBInsert(TREE, node);
  return node;
}

void setNodesFromStringArr(Node *nodes, string inputNodes[], uint8_t numOfNodes){
  for(uint8_t i = 0; i < numOfNodes; i++){
    nodes[i] = node_init_from_str(inputNodes[i]);
  }
}

/**
 * This function populates a tree with nodes from a preOrder traversal.
 * This is for filehandling and the IO for the project
 */
void buildTreeFromPreOrderNodes(RBTree *tree, Node *preOrderNodes, uint8_t numOfNodes){
  uint8_t index = 0;
  Node *root;
  root = buildTreeFromPreOrderNodes_Rec(preOrderNodes, &index, 0, numOfNodes - 1, numOfNodes);
  tree->setRoot(root);
}

/**
 * This recursive helper function populates a tree with nodes from a preOrder traversal.
 * This is for filehandling and the IO for the project
 */
Node *buildTreeFromPreOrderNodes_Rec(Node *preOrderNodes, uint8_t* preIndexPtr, uint8_t low, uint8_t high, uint8_t numOfNodes){
  Node *root = &preOrderNodes[*preIndexPtr];
  *preIndexPtr = *preIndexPtr + 1;
  if (low == high){
      return root;
  }
  uint8_t i;
  for (i = low; i <= high; ++i){
    //uint8_t key = extractNumber(preOrderNodes[i]);
    if (preOrderNodes[i].key > root->key){
        break;
    }
  }

  if(!isNilNode(root)){

    root->left = buildTreeFromPreOrderNodes_Rec(preOrderNodes, preIndexPtr, *preIndexPtr, i - 1, numOfNodes);
    root->right = buildTreeFromPreOrderNodes_Rec(preOrderNodes, preIndexPtr, i, high, numOfNodes);

    /* //For debugging
    cout << "\tValues, PreIndexPointer:= " << +(*preIndexPtr) << ", i:= " << +(i) << ", high:= " << +(high) << endl;
    cout << "\t\t\tLeft:= " << simpleString(root->left) << endl;
    cout << "\t\tCurrNode:= " << simpleString(root) << endl;
    cout << "\t\t\tRight:= " << simpleString(root->right) << endl;
    */
  }

  return root;
}
