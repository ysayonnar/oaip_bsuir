#include "functions.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"

Slice *newSlice() {
  Slice *slice = (Slice *)malloc(sizeof(Slice));

  slice->values = NULL;
  slice->capacity = 0;
  slice->len = 0;

  return slice;
}

void append(Slice *slice, int value) {
  if (slice->capacity == 0) {
    slice->capacity = 1;
    slice->len = 1;
    slice->values = (int *)malloc(sizeof(int));
  } else {
    if (slice->len == slice->capacity) {
      slice->capacity *= 2;
      slice->values =
          (int *)realloc(slice->values, sizeof(int) * slice->capacity);
    }
    slice->len++;
  }

  *(slice->values + slice->len - 1) = value;
}

void printSlice(Slice *slice) {
  if (slice->len == 0) {
    printf("Slice is empty\n");
  }

  for (int i = 0; i < slice->len; i++) {
    printf("%d ", *(slice->values + i));
  }

  printf("\n");
}

void freeSlice(Slice *slice) {
  free(slice->values);
  slice->len = 0;
  slice->capacity = 0;
}

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

void dfsPreorder(TreeNode *tree, Slice *slice) {
  if (tree == NULL) {
    return;
  }

  append(slice, tree->value);

  dfsPreorder(tree->left, slice);
  dfsPreorder(tree->right, slice);
}

void dfsInorder(TreeNode *tree, Slice *slice) {
  if (tree == NULL) {
    return;
  }

  dfsInorder(tree->left, slice);
  append(slice, tree->value);
  dfsInorder(tree->right, slice);
}

void dfsPostorder(TreeNode *tree, Slice *slice) {
  if (tree == NULL) {
    return;
  }

  dfsPostorder(tree->left, slice);
  dfsPostorder(tree->right, slice);
  append(slice, tree->value);
}
