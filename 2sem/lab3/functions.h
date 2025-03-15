#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Stack {
  char bracket;
  struct Stack *next;
} Stack;

// returns 0 or 1, where 1 means that op was successfull
int push(Stack **stack, char symbol);
int pop(Stack **stack, char *destination);

// brackets ops
int isBracket(char symbol);
int isOpeningBracket(char c);
int isClosingBracket(char c);
int isMatchingPair(char opening, char closing);

int checkBrackets(const char *expression);

#endif
