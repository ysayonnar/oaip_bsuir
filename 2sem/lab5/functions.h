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

// slice functions

Slice *newSlice();

void append(Slice *slice, int value);

void printSlice(Slice *slice);

void freeSlice(Slice *slice);

// tree functions

void insertTree(TreeNode **tree, int value);

void printTree(TreeNode *tree);

void dfsByType(TreeNode *tree, Slice *slice, int type);

int deleteNode(TreeNode *tree, int value);

void freeTree(TreeNode *tree);

// client functions

void fillTree(TreeNode **tree);

void printDfsByType(TreeNode *tree, int type);

void deleteNodeByValue(TreeNode *tree);

#endif
