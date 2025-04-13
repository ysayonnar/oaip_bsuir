#include "functions.h"

int main() {
  TreeNode *tree = newTreeNode(50);
  insertTree(tree, 25);
  insertTree(tree, 12);
  insertTree(tree, 75);
  insertTree(tree, 60);
  insertTree(tree, 87);
  insertTree(tree, 100);

  printTree(tree);
}
