#include "../../utils/utils.h"
#include "functions.h"
#include "stdio.h"

int main() {
  int count = inputNumber("Enter how many nums to insert: ", 0, 100);

  TreeNode *tree;

  for (int i = 0; i < count; i++) {
    int num = inputNumber("Enter number: ", -1000, 1000);

    if (i == 0) {
      tree = newTreeNode(num);
    } else {
      insertTree(tree, num);
    }
  }

  printTree(tree);

  Slice *dfsSlice = newSlice();
  dfsPreorder(tree, dfsSlice);
  printf("DFS_PREORDER:");
  printSlice(dfsSlice);
  freeSlice(dfsSlice);

  dfsInorder(tree, dfsSlice);
  printf("DFS_INORDER:");
  printSlice(dfsSlice);
  freeSlice(dfsSlice);

  dfsPostorder(tree, dfsSlice);
  printf("DFS_POSTORDER:");
  printSlice(dfsSlice);
  freeSlice(dfsSlice);
}
