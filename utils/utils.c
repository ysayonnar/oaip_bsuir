#include "utils.h"
#include <stdio.h>

void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

void clearScreen(){
	printf("\033[H\033[2J");
}

int inputNumber(char* message, int min, int max){
    int n = 0;
    int scanfRes = 0;

    while(scanfRes == 0){
        printf("%s", message);
        scanfRes = scanf("%d", &n);
        if(scanfRes == 0){
            printf("\033[1;31m\tInvalid Input!\033[0m\n");
        }
        else if(n < min || n > max) {
            printf("\033[1;31m\tNumber must be from %d to %d!\033[0m\n", min, max);
            scanfRes = 0;
            n = 0;
        }
		clearBuffer();
    }

	return n;
}

float inputFloat(char* message, float min, float max){
	float n = 0;
    int scanfRes = 0;

    while(scanfRes == 0){
        printf("%s", message);
        scanfRes = scanf("%f", &n);
        if(scanfRes == 0){
            printf("\033[1;31m\tInvalid Input!\033[0m\n");
        }
        else if(n < min || n > max) {
            printf("\033[1;31m\tNumber must be from %.1f to %.1f!\033[0m\n", min, max);
            scanfRes = 0;
            n = 0;
        }
		clearBuffer();
    }

	return n;
}

void inputString(char *str, int max_len) {
    if (!str || max_len == 0) return; 
    fgets(str, max_len, stdin);

    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
	clearBuffer();
}

int strLength(char *str) {
    int length = 0;
    while (*(str + length) != '\0') {
        length++;
    }
    return length;
}

int compareStrings(char *str1, char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }

    return *str1 - *str2;
}