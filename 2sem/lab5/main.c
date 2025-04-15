#include "../../utils/utils.h"
#include "functions.h"
#include "stdio.h"
#include "stdlib.h"

int main() {
  int option = 1;
  TreeNode *tree = NULL;

  while (option != 0) {
    printf("Choose option:\n\t1 - Fill tree\n\t2 - Preorder DFS\n\t3 - "
           "Inorder DFS\n\t");
    printf(
        "4 - Postorder DFS\n\t5 - Print tree\n\t6 - Delete node by value\n\t");
    printf("7 - Delete tree and create new one\n\t0 - Quit\n");
    option = inputNumber("Option: ", 0, 7);

    switch (option) {
    case 1:
      fillTree(&tree);
      break;
    case 2:
      printDfsByType(tree, option - 3);
      break;
    case 3:
      printDfsByType(tree, option - 3);
      break;
    case 4:
      printDfsByType(tree, option - 3);
      break;
    case 5:
      printTree(tree);
      break;
    case 6:
      deleteNodeByValue(tree);
      break;
    case 7:
      freeTree(tree);
      tree = NULL;
      break;
    }
  }
}
