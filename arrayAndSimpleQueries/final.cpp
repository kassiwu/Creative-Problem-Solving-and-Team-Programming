/*
 *  arrayAndSimpleQueries.cpp
 *
 *  Created on: Apr 28, 2018
 *  Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 *  Problem: https://www.hackerrank.com/challenges/array-and-simple-queries/problem
 */


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Tittle: Treaps Data Structure
// Treaps = BST + heap
// 1) data/key field
// 2) priority field -- random value

// 1<=N<=10^5
const long MAX_N = 100000l;

// insert the (key, priority,size)
typedef struct node{
    long value; // data/key field
    int priority; //rand() -- int type
    long size; // size -- tree size
    struct node *left; // left child
    struct node *right; // right child
}node[MAX_N];


long values[MAX_N];

// join two trees -- with no rotation
// the heap order is to maintain a min heap
// the merge operation merges two given treaps L and R into a single treap T
// only care about immediate parent

// all nodes in the left subtree are visited before the root is visited
// and all nodes in the right subtree are visited after the root is visited
// A very important assumption of the merge operation is that the largest value of L is less than the smallest value of R
Node *merge(Node *x, Node *y) {
  if (x == NULL) {
    return y;
  }
  if (y == NULL) {
    return x;
  }
  if (x->priority < y->priority) {
    x->right = merge(x->right, y);
    x->size = getSize(x->left) + getSize(x->right) + 1;
    return x;
  } else {
    y->left = join(x, y->l);
    y->size =  getSize(y->left) + getSize(y->right) + 1;
    return y;
  }
}

// get the size of a tree
long getSize(Node *x) {
  if (x != NULL) {
    return x->size;
  }
  return 0;
}


//Helper function for extracting subtrees that recursively splits
void splitNode(Node *n, Node*& left, Node*& right, long val) {

  if(n != NULL) {

    //get max possible size
    int max = getSize(n->left)+1;

    //if in the bounds split right
    if(max > val) {
      splitNode(n->right, n->right, right, (max-val));
      left = n;
    } else {
      //else split left
      splitNode(n->left, left, n->left, val);
      right = n;
    }
    x->size =  getSize(left) + getSize(right) + 1;
 
  } else {
      //set to null and ignore
      right = NULL;
      left = NULL;

  }
}


//in order to get the subtree must be able to spit into subtrees
Node *extract(Node *&n, long from, long to) {

    Node *left, *right, *middle;

    //split from to right to middle 
    splitNode(n, middle, right, to);
    //split from middle to left
    splitNode(middle, left, middle, from);
    //merge into node
    n = merge(left, right);
    return n;
}


// in-order tree traversal
// 1) visit node
// 2) traverse left subtree
// 3) traverse right subtree
// Performs recursive Inorder traversal of a Given Binary Tree.
void Inorder(Node *x) {
  int i = 0;
  if(x != NULL) {
    printInorder(x->left);
    values[i++] = x->value;
    printInorder(x->right);
  }
}

int main() {
  // Dr. B's io speed trick
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  /*
   * Take in user input
   * Line 1: Size n of array, number m of queries
   * Line 2: int array A[]
   * Remaining lines: Queries
   * Query format: 1 i j (remove from i to j and move to front)
   * or 2 i j (remove from i to j and move to back)
   */

   long n, m;
   cin >> n;
   cin >> m;
   Node *tree = NULL;

  for (long i = 0; i < MAX_N; ++i) {
    // initialize values in each node
    cin >> nodes[i].value;
    node[i].priority = rand();
    node[i].size = 1;
    // points to the root of the tree
    tree = merge(tree, node + i);
  }


  int type, i, j;

  while (m--) {
    cin >> type;
    cin >> i;
    cin >> j;
    Node *subtree = extract(tree, i-1, j);
    // Modify the given array by removing elements from i to j and adding them to the front
    if (type == 1) {
      // points to the root of the tree
       tree = merge(subtree, tree);
    }
    // Modify the given array by removing elements from i to j and adding them to the back
    else if (type == 2) {
      // points to the root of the tree
       tree = merge(tree,subtree);
    }
  }
  // Store values of each in an array using in-order traversal
  Inorder(tree);


  cout << abs(values[0] - values[n-1]) << endl;
  for (long i = 0; i < n; ++i) {
    cout << values[i] << " ";
  }
  cout << endl;

  return 0;
}






// ***the heap order is to maintain a min heap
// the nodes in the left subtree of the root will have data fields that are less than the data field of the root
// the nodes in the right subtree of the root will have data fields that are greater than the data field of the root
// the left and right subtrees are binary search trees
// the priority value of the root is greater than the priority value of its children
// the left and right subtrees are max heaps

// follow the rules of binary search tree and heap to maintain the tree
