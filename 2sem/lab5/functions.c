#include "functions.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"

TreeNode *newTreeNode(int value) {
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  node->value = value;
  node->right = NULL;
  node->left = NULL;
  return node;
}

void insertTree(TreeNode *tree, int value) {
  if (tree == NULL) {
    tree = newTreeNode(value);
    return;
  }

  TreeNode *currentNode = tree;
  while (currentNode != NULL) {
    if (value == currentNode->value) {
      return;
    } else if (value < currentNode->value) {
      if (currentNode->left == NULL) {
        currentNode->left = newTreeNode(value);
        break;
      }
      currentNode = currentNode->left;
    } else if (value > currentNode->value) {
      if (currentNode->right == NULL) {
        currentNode->right = newTreeNode(value);
        break;
      }
      currentNode = currentNode->right;
    }
  }
}

void printTreeHelper(TreeNode *tree, int space) {
  if (tree == NULL) {
    return;
  }

  space += 4;

  printTreeHelper(tree->right, space);

  printf("\n");
  for (int i = 4; i < space; i++) {
    printf(" ");
  }
  printf("%d\n", tree->value);

  printTreeHelper(tree->left, space);
}

void printTree(TreeNode *tree) { printTreeHelper(tree, 0); }
