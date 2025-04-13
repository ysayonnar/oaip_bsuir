#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct TreeNode {
  int value;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *newTreeNode(int value);

void insertTree(TreeNode *tree, int value);

void printTree(TreeNode *tree);

#endif
