#include "functions.h"
#include "../../utils/utils.h"
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

void insertTree(TreeNode **tree, int value) {
  if (*tree == NULL) {
    *tree = newTreeNode(value);
    return;
  }

  TreeNode *currentNode = *tree;
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

void printTree(TreeNode *tree) {
  if (tree == NULL) {
    printf("Tree is empty!\n");
    return;
  }

  printf("Tree:\n");
  printTreeHelper(tree, 0);
  printf("\n");
}

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

void dfsByType(TreeNode *tree, Slice *slice, int type) {
  switch (type) {
  case -1:
    dfsPreorder(tree, slice);
    break;
  case 0:
    dfsInorder(tree, slice);
    break;
  case 1:
    dfsPostorder(tree, slice);
    break;
  }
}

int deleteNode(TreeNode *tree, int value) {
  if (tree == NULL) {
    return 0;
  } else if (tree->value == value) {
    // root cant be deleted
    return 0;
  }

  TreeNode *prev = NULL;
  TreeNode *currentNode = tree;

  while (currentNode != NULL) {
    if (value == currentNode->value) {
      Slice *slice = newSlice();
      dfsPostorder(currentNode->left, slice);
      dfsPostorder(currentNode->right, slice);

      if (currentNode->value < prev->value) {
        prev->left = NULL;
      } else if (currentNode->value > prev->value) {
        prev->right = NULL;
      }

      freeTree(currentNode);

      for (int i = 0; i < slice->len; i++) {
        insertTree(&prev, *(slice->values + i));
      }

      return 1;
    } else if (value < currentNode->value) {
      prev = currentNode;
      currentNode = currentNode->left;
    } else if (value > currentNode->value) {
      prev = currentNode;
      currentNode = currentNode->right;
    }
  }

  return 0;
}

void freeTree(TreeNode *tree) {
  if (tree == NULL) {
    return;
  }

  freeTree(tree->left);
  freeTree(tree->right);

  free(tree);
  tree = NULL;
}

void fillTree(TreeNode **tree) {
  int count = inputNumber("How many numbers to insert: ", 1, 100);

  for (int i = 0; i < count; i++) {
    int num = inputNumber("Enter number: ", -1000, 1000);
    insertTree(tree, num);
  }
}

void printDfsByType(TreeNode *tree, int type) {
  Slice *slice = newSlice();

  dfsByType(tree, slice, type);
  if (slice->len == 0) {
    printf("Tree is empty!\n");
    return;
  }
  printf("DFS: ");
  printSlice(slice);
  freeSlice(slice);
  printf("\n");
}

void deleteNodeByValue(TreeNode *tree) {
  int value = inputNumber("Enter node to delete: ", -1000, 1000);
  int isDeleted = deleteNode(tree, value);
  if (isDeleted) {
    printf("Deleted!\n");
  } else {
    printf("Node was not deleted...\n");
  }
}
