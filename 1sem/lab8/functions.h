#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void clearBuffer();
int isNumber(char symbol);
int inputNumber(char* message, int min, int max);
char* inputString(int length);
void printString(char *message, char *str);
char* transformString(char *str, int *length, int numbersToKeep);
char* transformString2(char *str, int *length);

#endif