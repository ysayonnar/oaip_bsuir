#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void clearBuffer();
int strLength( char *str);
int inputNumber(char* message, int min, int max);
char* inputString(char *msg, int length);
void printString(char *message, char *str);
int count_words(char *str);
char**** createArrayOfMatrix(int matrixNumber, int rows, int cols);
char*** createMatrixAndFill(int rows, int cols);
void printArrayOfMatrix(char ****arr, int matrixNumber, int rows, int cols);
void findPalindromes(char ****arr, int matrixNumber, int rows, int cols);
int getPalindromesInString(char **palindromes, int palindromesCounter, char* string);
char **findWords(char *string, int *wordsAmount);
int isPalindrome(char *word);
void freeArrayOfMatrix(char ****arr, int matrixNumber, int rows, int cols);

#endif