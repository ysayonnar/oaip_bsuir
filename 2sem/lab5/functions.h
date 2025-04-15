#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct TreeNode {
  int value;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

typedef struct {
  int *values;
  int len;
  int capacity;
} Slice;

Slice *newSlice();

void append(Slice *slice, int value);

void printSlice(Slice *slice);

void freeSlice(Slice *slice);

TreeNode *newTreeNode(int value);

void insertTree(TreeNode *tree, int value);

void printTree(TreeNode *tree);

void dfsPreorder(TreeNode *tree, Slice *slice);

void dfsInorder(TreeNode *tree, Slice *slice);

void dfsPostorder(TreeNode *tree, Slice *slice);

#endif
