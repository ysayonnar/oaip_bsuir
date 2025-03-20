#include "../../utils/utils.h"
#include "functions.h"
#include <stdio.h>
#define MAX_LENGTH 100

int main() {
  int ans = 1;

  while (ans == 1) {
    char expression[MAX_LENGTH];

    printf("Enter expression: ");

    fgets(expression, sizeof(expression), stdin);

    int isCorrect = checkBrackets(expression);
    if (isCorrect == 1) {
      printf("correct!\n");
    } else {
      printf("error: ");
      for (int i = 0; *(expression + i) != '\0'; i++) {
        if (i == isCorrect) {
          printf("\033[1;31m%c\033[0m", *(expression + i));
        } else {
          printf("%c", *(expression + i));
        }
      }
    }

    clearBuffer();
    ans = inputNumber("Would you like to continue? (1 - yes):\t", 0, 1);
  }
}
