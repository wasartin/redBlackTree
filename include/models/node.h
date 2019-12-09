#ifndef NODE_H
# define NODE_H

#include <iostream> /* For cout */
#include <string>
#include <cstdlib> /* For itoa function */
#include <sstream> /* for ostringsteam used in converting uint8_t to a string */
#include <vector> /* For the inorder traveral */

#include <pthread.h> /* For threads */
#include <stdint.h> /* For uint8_t */

using namespace std;

/**
 * An enum to represent the color of the Node
 *      RED: For a red colored node
 *      BLACK: For a black colored node
 *      UNKNOWN: For the NULL object design pattern
 */
enum COLOR{RED, BLACK, UNKNOWN};

/**
 * A struct to define a node, slightly modified from the one given
 * by the assignment
 */
typedef struct Node{
  uint8_t key = 0;
  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
  uint8_t size = 0;
  COLOR color = UNKNOWN;
  pthread_mutex_t *m = NULL;
} Node;

void node_init(Node *node, uint8_t key);
Node node_init(Node *parent, uint8_t key, COLOR color, uint8_t size);
Node node_init_from_str(string data);

void lock_node(Node *node);
void unlock_node(Node *node);
bool is_locked(Node *node);

void updateNodesInfo(Node *node_x, Node *node_y);
void updateNodeInfo(Node *node_v);
void percolateUpUpdates(Node *node_v);

string simpleString(Node *node);
void printNodes(string prefix, Node *n);
void printNodesAndNil(string prefix, Node *n);

bool isNilNode(Node *node);


/* Binary Tree Functions */

/**
 * List Keys of the given subtree in Inreasing Order
 * Param: node_x, a pointer to a node in a Binary Tree
 */
vector<Node> InOrder(Node *node_x);

/**
 * List Keys of the given subtree in Pre Order
 * Root, Left subtree, Right Subtree
 * Param: node_x, a pointer to a node in a Binary Tree
 */
vector<Node> PreOrder(Node *node_x);

vector<Node> PreOrderWithNilNodes(Node *node_x);

/**
 * List Keys of the given subtree in Post Order
 * Param: node_x, a pointer to a node in a Binary Tree
 */
vector<Node> PostOrder(Node *node_x);

/**
 * Return a reference to the node y, in the subtree rooted
 * at x, such that node_y.k == k. Return null if no such
 * y exists.
 * Param: node_x, a pointer to the node of a subtree
 * Param: k, the key value being looked for
 */
Node *Search(Node *node_x, uint8_t k);

/**
 * Return a reference to the node in the subtree rooted at
 * x that contains the minimum key-value
 * Param: node_x, given subtree root
 */
Node *Minimum(Node *node_x);

/**
 * Return a reference to the node in the subtree rooted at
 * x that contains the maximum key-value
 * Param: node_x, the given subtree root
 */
Node *Maximum(Node *node_x);

/**
 * Return a reference to node containing the key-value
 * immediately following x.key in the BST that contains x.
 * Return null if x has the largest key in the tree.
 * Param: node_x, given subtree root
 */
Node *Successor(Node *node_x);

/**
 * Return a reference to the node containing the key-value
 * immediately preceding x.key in the BST that contains x.
 * Return null if x has the smallest key in the tree
 * Param: node_x, given subtree root.
 */
Node *Predecessor(Node *node_x);

#endif
