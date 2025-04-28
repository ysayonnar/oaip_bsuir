#include "../../utils/utils.h"
#include "functions.h"
#include "stdio.h"
#include "stdlib.h"

int main() {
  int option = 1;
  TreeNode *tree = NULL;

  while (option != 0) {
    printf("Choose option:\n\t1 - Fill tree\n\t2 - Preorder DFS LEFT\n\t3 - "
           "Inorder DFS LEFT\n\t");
    printf(
        "4 - Postorder DFS LEFT\n\t5 - Print tree\n\t6 - Delete node by value\n\t");
    printf("7 - Delete tree and create new one\n\t8 - Preorder DFS RIGHT\n\t9 - Inorder DFS RIGHT\n\t10 - Postorder DFS RIGHT\n");
    printf("\t0 - Quit\n");

    option = inputNumber("Option: ", 0, 10);

    switch (option) {
    case 1:
      fillTree(&tree);
      break;
    case 2:
      printDfsByType(tree, 0);
      break;
    case 3:
      printDfsByType(tree, 1);
      break;
    case 4:
      printDfsByType(tree, 2);
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
    case 8:
      printDfsByType(tree, 3);
      break;
    case 9:
      printDfsByType(tree, 4);
      break;
    case 10:
      printDfsByType(tree, 5);
      break;
    }
  }
}
