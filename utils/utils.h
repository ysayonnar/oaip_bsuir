#ifndef UTILS_H
#define UTILS_H

void clearBuffer();
void clearScreen();
int inputNumber(char* message, int min, int max);
float inputFloat(char* message, float min, float max);
void inputString(char *str, int max_len);
int strLength(char *str);
int compareStrings(char *str1, char *str2);

#endif