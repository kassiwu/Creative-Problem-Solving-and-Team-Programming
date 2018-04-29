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
int inc = 0;

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
    x->right = merge(x->Right(), y);
    x->size = getSize(x->Left()) + getSize(x->Right()) + 1;
    return x;
  }
  else
  {
    y->left = merge(x, y->Left());
    y->size = getSize(y->Left()) + getSize(y->Right()) + 1;
    return y;
  }
}


//Helper function for extracting subtrees that recursively splits
void splitNode(Node *n, int k, Node *&l, Node *&r)
{
  if (! n)
    l = r = NULL;
  else {
    int c = getSize(n->left) + 1;
    if (k < c) {
      splitNode(n->left, k, l, n->left);
      r = n;
    } else {
      splitNode(n->right, k-c, n->right, r);
      l = n;
    }
    n->size = getSize(n->left) + getSize(n->right) + 1;
  }
}

//in order to get the subtree must be able to spit into subtrees
Node *extract(Node *&n, int from, int to)
{
  Node *left, *right, *middle;
  splitNode(n, to, middle, right);
  splitNode(middle, from, left, middle);
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
    // cout << x->Value() << " ";
    values[inc] = x->Value();
    inc++;
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

  long n, m;
  cin >> n;
  cin >> m;
  Node *tree = NULL;

  for (long i = 0; i < n; i++)
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
    int type;
    long i, j;
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

  cout << abs(values[0] - values[n - 1]) << endl;
  for (long i = 0; i < n; ++i)
  {
    cout << values[i] << " ";
  }
  cout << endl;

  return 0;
}
