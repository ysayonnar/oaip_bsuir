#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int push(Stack **stack, char symbol) {
  if (!isBracket(symbol)) {
    return 0;
  }

  Stack *newNode = (Stack *)malloc(sizeof(Stack));
  newNode->bracket = symbol;
  newNode->next = *stack;
  *stack = newNode;
  return 1;
}

int pop(Stack **stack, char *destination) {
  if (*stack == NULL) {
    return 0;
  }

  Stack *temp = *stack;
  *destination = temp->bracket;
  *stack = temp->next;

  free(temp);
  return 1;
}

int isBracket(char symbol) {
  return symbol == '(' || symbol == ')' || symbol == '[' || symbol == ']' ||
         symbol == '{' || symbol == '}';
}

int isOpeningBracket(char c) { return c == '(' || c == '[' || c == '{'; }

int isClosingBracket(char c) { return c == ')' || c == ']' || c == '}'; }

int isMatchingPair(char opening, char closing) {
  return (opening == '(' && closing == ')') ||
         (opening == '[' && closing == ']') ||
         (opening == '{' && closing == '}');
}

int checkBrackets(const char *expression) {
  Stack *stack = NULL;

  for (int i = 0; *(expression + i) != '\0'; i++) {
    char symbol = *(expression + i);

    if (isOpeningBracket(symbol)) {
      push(&stack, symbol);
    } else if (isClosingBracket(symbol)) {
      if (stack == NULL) {
        return 0;
      }

      char prev;
      int isPopped = pop(&stack, &prev);
      if (!isPopped) {
        return 0;
      }

      if (!isMatchingPair(prev, symbol)) {
        return 0;
      }
    }
  }

  return stack == NULL;
}
