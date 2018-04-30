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
#include <stack>
#include <algorithm>
using namespace std;

// Treaps = BST + heap
// 1) data/key field
// 2) priority field -- random value

// 1<=N<=10^5
const int MAX_N = 100000;

// insert the (key, priority,size)
struct Node
{
  int value;    // data/key field
  int priority; //rand() -- int type
  int size;     // size -- tree size
  Node *left;   // left child
  Node *right;  // right child
} node[MAX_N];

int values[MAX_N];
int inc = 0;

// get the size of a tree
int getSize(Node *n)
{
  if (n == NULL)
  {
    return 0;
  }
  return n->size;
}

// join two trees -- with no rotation
// the heap order is to maintain a min heap
// the merge operation merges two given treaps L and R into a single treap T
// only care about immediate parent

// all Nodes in the left subtree are visited before the root is visited
// and all Nodes in the right subtree are visited after the root is visited
Node *merge(Node *n1, Node *n2)
{
  //if null then the tree is the other side
  if (n1 == NULL)
  {
    return n2;
  }
  if (n2 == NULL)
  {
    return n1;
  }
  //if y priority is higher
  if (n1->priority < n2->priority)
  {
    //merge right subtree recursively
    n1->right = merge(n1->right, n2);
    //increase size
    n1->size = getSize(n1->left) + getSize(n1->right) + 1;
    return n1;
  }
  //if x priority is higher
  else
  {
    //merge left subtree recursively
    n2->left = merge(n1, n2->left);
    //increase size
    n2->size = getSize(n2->left) + getSize(n2->right) + 1;
    return n2;
  }
}

//Helper function for extracting subtrees that recursively splits
void splitNode(Node *n, Node *&left, Node *&right, int value)
{
  if (!n)
  {
    //set to null and ignore
    left = NULL;
    right = NULL;
  }
  else
  {
    //use left subtree
    int maxSize = getSize(n->left) + 1;
    //if left subtree is greater than value
    if (value < maxSize)
    {
      // if in the bounds split right
      right = n;
      splitNode(n->left, left, n->left, value);
    }
    else
    {
      //if in the bounds split right
      left = n;
      splitNode(n->right, n->right, right, value - maxSize);
    }
    //increase tree size
    n->size = getSize(n->left) + getSize(n->right) + 1;
  }
}

//in order to get the subtree must be able to spit into subtrees
Node *extract(Node *&n, int from, int to)
{
  Node *left, *right, *middle;
  //split from right
  splitNode(n, middle, right, to);
  //split from left
  splitNode(middle, left, middle, from);
  //merge into Node
  n = merge(left, right);
  return middle;
}

// Inorder tree traversal
// 1) visit node
// 2) traverse left subtree
// 3) traverse right subtree
// Performs recursive Inorder traversal of a given binary tree.
void Inorder(Node *n)
{
  if (n != NULL)
  {
    Inorder(n->left);
    values[inc] = n->value;
    inc++;
    Inorder(n->right);
  }
}

int main()
{
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
  int n, m;
  cin >> n;
  cin >> m;
  Node *tree = NULL;

  for (int i = 0; i < n; i++)
  {
    // initialize values in each Node

    cin >> node[i].value;
    node[i].priority = rand();
    node[i].size = 1;
    // points to the root of the tree
    tree = merge(tree, node + i);
  }

  while (m > 0)
  {
    m--;
    int type;
    int i, j;
    cin >> type;
    cin >> i;
    cin >> j;

    Node *subtree = extract(tree, i - 1, j);
    // Modify the given array by removing elements from i to j and adding them to the front
    if (type == 1)
    {
      // points to the root of the tree
      tree = merge(subtree, tree);
    }
    // Modify the given array by removing elements from i to j and adding them to the back
    else if (type == 2)
    {
      // points to the root of the tree
      tree = merge(tree, subtree);
    }
  }
  // Store values of tree using in-order traversal
  Inorder(tree);

  //print tree
  cout << abs(values[0] - values[n - 1]) << endl;
  for (int i = 0; i < n; ++i)
  {
    cout << values[i] << " ";
  }
  //newline
  cout << endl;

  return 0;
}
