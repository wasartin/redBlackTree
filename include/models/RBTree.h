#ifndef RBTREE_H
# define RBTREE_H

#include <iostream> /* For cout */
#include <string>
#include <cstdlib> /* For itoa function */
#include <sstream> /* for ostringsteam used in converting uint8_t to a string */
#include <vector> /* For the inorder traveral */

#include <pthread.h> /* For threads */
#include <stdint.h> /* For uint8_t */

#include "node.h"
#include "../lib/utils.h" /* For uint8_t extractNumber(string input) */

using namespace std;

/**
 * A Red Black Tree is a binary tree that satisfies the following:
 *      i. Every Node is either RED or BLACK
 *      ii. The root is BLACK
 *      iii. Every Leaf(nil) is BLACK
 *      iv. If a Node is RED,
 *           then both of its children are BLACK
 *      v. For each Node, all simple paths from Node to desc. leaves
 *         contain the same # of BLACK Nodes
 */
class RBTree {

private:
  Node *root;
  void destroyTree(Node *leaf);

public:
  Node NIL;
  RBTree(){
    NIL = node_init(NULL, 0, BLACK, 0);
    root = &NIL;

  }
  RBTree(Node *root){
    root = root;
  }
  ~RBTree();

  void destroyTree();
  bool isEmpty();
  Node *getRoot();
  void setRoot(Node *node);
  Node *getNILNode();

};

/* Red Black Tree Functions */

/**
 * The number of black Nodes on any simple path, but not including
 * x, down to a leaf.
 *
 * Note: The black height of a tree is the black height of its root.
 * All simple paths haev the same number of black nodes.
 */
uint8_t getBlackHeight(Node *node_x);
/**
 *
 */
void LeftRotate(RBTree *tree, Node *node_x);

/**
 *
 */
void RightRotate(RBTree *tree, Node *node_x);

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
void RBInsert(RBTree *tree, Node *node_z);

/**
 *
 */
void RBInsertFixup(RBTree *tree, Node *node_z);

/**
 *
 */
void RBTransplant(RBTree *tree, Node *node_u, Node *node_v);

/**
 *
 */
void RBDelete(RBTree *tree, uint8_t keyToDelete);

/**
 *
 */
void RBDeleteFixup(RBTree *tree, Node *node_x);

/*API designated by homework */
Node *rb_search(uint8_t key);

Node *rb_insert(uint8_t key);

uint8_t rb_delete(uint8_t key);

/**
 * Helper function to populate an array of Nodes.
 */
void setNodesFromStringArr(Node *nodes, string inputNodes[], uint8_t numOfNodes);

/**
 * This function populates a tree with nodes from a preOrder traversal.
 * This is for filehandling and the IO for the project
 */
void buildTreeFromPreOrderNodes(RBTree *tree, Node *preOrderNodes, uint8_t numOfNodes);

/**
 * This recursive helper function populates a tree with nodes from a preOrder traversal.
 * This is for filehandling and the IO for the project
 */
Node* buildTreeFromPreOrderNodes_Rec(Node *preOrderNodes, uint8_t* preIndexPtr, uint8_t low, uint8_t high, uint8_t numOfNodes);

//I have no idea how to do this without any indication what the root node is
void buildTreeFromInOrderNodes(RBTree *tree, vector<Node> nodes);
#endif
