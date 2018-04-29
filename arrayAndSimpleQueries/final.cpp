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

// Tittle: Treaps Data Structure
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
  int Value()
  {
    return value;
  }
  Node *Left()
  {
    return left;
  }
  Node *Right()
  {
    return right;
  }
} node[MAX_N];

int values[MAX_N];

// get the size of a tree
int getSize(Node *x)
{
  if (x != NULL)
  {
    return x->size;
  }
  return 0;
}

// join two trees -- with no rotation
// the heap order is to maintain a min heap
// the merge operation merges two given treaps L and R into a single treap T
// only care about immediate parent

// all Nodes in the left subtree are visited before the root is visited
// and all Nodes in the right subtree are visited after the root is visited
// A very important assumption of the merge operation is that the largest value of L is less than the smallest value of R
Node *merge(Node *x, Node *y)
{
  if (x == NULL)
  {
    return y;
  }
  if (y == NULL)
  {
    return x;
  }
  if (x->priority < y->priority)
  {
    x->Right() = merge(x->Right(), y);
    x->size = getSize(x->Left()) + getSize(x->Right()) + 1;
    return x;
  }
  else
  {
    y->Left() = merge(x, y->Left());
    y->size = getSize(y->Left()) + getSize(y->Right()) + 1;
    return y;
  }
}

//Helper function for extracting subtrees that recursively splits
void splitNode(Node *n, Node *&left, Node *&right, int val)
{

  if (n != NULL)
  {
    //get max possible size
    int max = getSize(n->left) + 1;

    //if in the bounds split right
    if (max > val)
    {
      splitNode(n->right, n->right, right, (val - max));
      left = n;
    }
    else
    {
      //else split left
      splitNode(n->left, left, n->left, val);
      right = n;
    }
    n->size = getSize(left) + getSize(right) + 1;
  }
  else
  {
    //set to null and ignore
    right = NULL;
    left = NULL;
  }
}

//in order to get the subtree must be able to spit into subtrees
Node *extract(Node *&n, int from, int to)
{

  Node *left, *right, *middle;

  //split from to right to middle
  splitNode(n, middle, right, to);
  //split from middle to left
  splitNode(middle, left, middle, from);
  //merge into Node
  n = merge(left, right);
  return middle;
}

// in-order tree traversal
// 1) visit Node
// 2) traverse left subtree
// 3) traverse right subtree
// Performs recursive Inorder traversal of a Given Binary Tree.
void Inorder(Node *x)
{
  if (x != NULL)
  {
    Inorder(x->Left());
    cout << x->Value() << " ";
    Inorder(x->Right());
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

  while (m--)
  {
    int type, i, j;

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
  // Print values of tree using in-order traversal
  Inorder(tree);

  // cout << abs(values[0] - values[n - 1]) << endl;
  // for (int i = 0; i < n; ++i)
  // {
  //   cout << values[i] << " ";
  // }
  // cout << endl;

  return 0;
}

// ***the heap order is to maintain a min heap
// the Nodes in the left subtree of the root will have data fields that are less than the data field of the root
// the Nodes in the right subtree of the root will have data fields that are greater than the data field of the root
// the left and right subtrees are binary search trees
// the priority value of the root is greater than the priority value of its children
// the left and right subtrees are max heaps

// follow the rules of binary search tree and heap to maintain the tree
