#include "../../include/models/node.h"

void node_init(Node *node, uint8_t key){
  node->key = key;
  node->left = nullptr;
  node->right = nullptr;
  node->parent = nullptr;
  node->size = 1;
  node->color = RED;
  pthread_mutex_init(node->m, NULL);
}

Node node_init(Node *parent, uint8_t key, COLOR color, uint8_t size){
  Node node;
  node_init(&node, key);
  node.parent = parent;
  node.size = size;
  node.color = color;
  return node;
}

Node node_init_from_str(string data){
  Node newNode;
  //Check if NIL Node
  if(data == "f") {
    newNode = node_init(NULL, 0, BLACK, 0);
  }else{
    string numStr = "";
    for(uint8_t i = 0; i < data.length(); i++){
      COLOR color = UNKNOWN;
      if(isdigit(data.at(i))){
        numStr+=data.at(i);
      }else if(data.at(i) == 'b' || data.at(i) == 'r'){//f is new for NIL NODES
        color = (data.at(i) == 'r')? RED : BLACK;
        //cout << "\tNum: " << numStr << ", Color: " << ((color == BLACK)? "Black" : "Red") << endl; // Debugging
        if(data.at(i) != 'f'){//NILL NODE
          newNode = node_init(NULL, atoi(numStr.c_str()), color, 1);

        }

      }
    }
  }
    return newNode;
}

bool isNilNode(Node *node){
  return (node->size == 0);
}

void lock_node(Node *node){
  //Temp, cout for debuggin
  pthread_mutex_lock(node->m);
}

void unlock_node(Node *node){
  //temp cout for debuggin
  pthread_mutex_lock(node->m);
}

/**
 * A helper function, for seeing what a node looks like
 */
string simpleString(Node *node) {
  ostringstream convert;
  convert << (int) node->key;
  if(isNilNode(node)){
    return "f";
  }
  string nodeStr =  convert.str();
  nodeStr += (node->color == RED)? "r" : "b";
  /* //For Debuggin
  int temp = +(node->size);
  nodeStr += " (" + to_string(temp) + ")";
  */
  return nodeStr;
}

/**
 * A helper function to see the tree Hierarchy
 */
void printNodes(string prefix, Node *n){
  if(!isNilNode(n)){
    printNodes(prefix + "     ", n->right);
    cout << prefix << "|-- " << simpleString(n) << endl;
    printNodes(prefix + "     ", n->left);
  }
}

void updateNodeInfo(Node *node_v){
  if(!isNilNode(node_v)){
    node_v->size = (node_v->left->size) + (node_v->right->size) + 1;
  }
}

void updateNodesInfo(Node *node_x, Node *node_y){
  node_y->size = node_x->size;
  node_x->size = (node_x->left->size) + (node_x->right->size) + 1;
  updateNodeInfo(node_x);
  updateNodeInfo(node_y);
}

/**
 * Helper method used to update Node info in Insert
 * and Delete. This only goes up the tree til it hits
 * the root's parent (nil).
 */
void percolateUpUpdates(Node *node_v){
  while(!isNilNode(node_v)){
    updateNodeInfo(node_v);
    node_v = node_v->parent;
  }
}

/**
 * List Keys of the given subtree in Inreasing Order
 * Param: node_x, a pointer to a node in a Binary Tree
 */
vector<Node> InOrder(Node *node_x){
  vector<Node> result;
  if(isNilNode(node_x)) return result;

  vector<Node> left = InOrder(node_x->left);
  result.insert(result.end(), left.begin(), left.end());

  result.push_back(*node_x);

  vector<Node> right = InOrder(node_x->right);
  result.insert(result.end(), right.begin(), right.end());

  return result;
}

/**
 * List Keys of the given subtree in Pre Order
 * Root, Left subtree, Right Subtree
 * Param: node_x, a pointer to a node in a Binary Tree
 */
vector<Node> PreOrder(Node *node_x){
  vector<Node> result;
  if(isNilNode(node_x)) return result;

  result.push_back(*node_x);

  vector<Node> left = PreOrder(node_x->left);
  result.insert(result.end(), left.begin(), left.end());

  vector<Node> right = PreOrder(node_x->right);
  result.insert(result.end(), right.begin(), right.end());

  return result;
}

/**
 * List Keys of the given subtree in Post Order
 * Param: node_x, a pointer to a node in a Binary Tree
 */
vector<Node> PostOrder(Node *node_x){
  vector<Node> result;
  if(isNilNode(node_x)) return result;

  vector<Node> left = PostOrder(node_x->left);
  result.insert(result.end(), left.begin(), left.end());

  vector<Node> right = PostOrder(node_x->right);
  result.insert(result.end(), right.begin(), right.end());

  result.push_back(*node_x);

  return result;
}

/**
 * Return a reference to the node y, in the subtree rooted
 * at x, such that node_y.k == k. Return null if no such
 * y exists.
 * Param: node_x, a pointer to the node of a subtree
 * Param: k, the key value being looked for
 */
Node *Search(Node *node_x, uint8_t key){
  Node *currNode = node_x;
  while(!isNilNode(currNode)){
    if(currNode->key == key){
      return currNode;
    }else if (key < currNode->key){
      currNode = currNode->left;
    }else{
      currNode = currNode->right;
    }
  }
  return NULL;
}

/**
 * Return a reference to the node in the subtree rooted at
 * x that contains the minimum key-value
 * Param: node_x, given subtree root
 */
Node *Minimum(Node *node_x){
  while(!isNilNode(node_x->left)){
    node_x = node_x->left;
  }
  return node_x;
}

/**
 * Return a reference to the node in the subtree rooted at
 * x that contains the maximum key-value
 * Param: node_x, the given subtree root
 */
Node *Maximum(Node *node_x){
  while(!isNilNode(node_x->right)){
    node_x = node_x->right;
  }
  return node_x;
}

/**
 * Return a reference to node containing the key-value
 * immediately following x.key in the BST that contains x.
 * Return null if x has the largest key in the tree.
 * Param: node_x, given subtree root
 */
Node *Successor(Node *node_x){
  /*
  if(!isNilNode(node_x->right)){
    return Minimum(node_x->right);
  }
  Node y = *node_x->parent;
  while( (!isNilNode(&y)) && (node_x == y.right) ){
    node_x = &y;
    y = *y.parent;
  }
  return node_x->parent;
  */
  if(!isNilNode(node_x->right)){  //Case 1: There is a right subtree
    return Minimum(node_x->right);
  }else {                         //Case 2: No right subtree
    Node *successor = node_x;
    Node *ancestorNode = node_x;
    while(!isNilNode(ancestorNode->parent)){//get the root
      ancestorNode = ancestorNode->parent;
    }
    while(ancestorNode->key != node_x->key){
      if(node_x->key < ancestorNode->key){
        successor = ancestorNode;
        ancestorNode = ancestorNode->left;
      }else{
        ancestorNode = ancestorNode->right;
      }
    }
    return successor;
  }
}

/**
 * Return a reference to the node containing the key-value
 * immediately preceding x.key in the BST that contains x.
 * Return null if x has the smallest key in the tree
 * Param: node_x, given subtree root.
 */
Node *Predecessor(Node *node_x){
  if(!isNilNode(node_x->left)){
    return Maximum(node_x->left);
  }else {                         //Case 2: No right subtree
    Node *predecessor = node_x;
    Node *ancestorNode = node_x;
    while(!isNilNode(ancestorNode->parent)){//get the root
      ancestorNode = ancestorNode->parent;
    }
    while(ancestorNode->key != node_x->key){
      if(node_x->key > ancestorNode->key){
        predecessor = ancestorNode;
        ancestorNode = ancestorNode->right;
      }else{
        ancestorNode = ancestorNode->left;
      }
    }
    return predecessor;
  }
}
