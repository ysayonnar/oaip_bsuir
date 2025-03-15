#include "../../utils/utils.h"
#include "functions.h"
#include <stdio.h>

int main() {
  int ans = 1;

  while (ans == 1) {
    char expression[100];

    printf("Enter expression: ");

    fgets(expression, sizeof(expression), stdin);

    int isCorrect = checkBrackets(expression);
    if (isCorrect) {
      printf("correct!\n");
    } else {
      printf("not correct!\n");
    }

    clearBuffer();
    ans = inputNumber("Would you like to continue? (1 - yes):\t", 0, 1);
  }
}
