#include "functions.h"
#include <stdlib.h>
#include <stdio.h>


void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

//проверка является ли символ цифрой
int isNumber(char symbol){
    if (symbol >='0' && symbol <= '9'){
        return 1;
    }else{
        return 0;
    }
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

char* inputString(int length){
	char *str;
	str = (char*)calloc(length + 1, sizeof(char));
    printf("Enter string: ");
	fgets(str, length + 1, stdin);
	return str;
}

void printString(char *message, char *str){
	printf("%s", message);
	puts(str);
}

char* transformString(char *str, int *length, int numbersToKeep){
    char *newString = (char*)calloc(*length + 1, sizeof(char));
    int counter = 0;
    int isDotWas = 0;//флаг для символа точки
    int elementsToDelete = 0;//счетчик элементов
    
	for (int i = 0; i < *length; i++) {
        if(str[i] == '.'){
            newString[i - elementsToDelete] = str[i];
            isDotWas = 1;
            counter = 0;
        } else if(isDotWas == 1 && isNumber(str[i]) == 1){
            counter++;
            if(counter > numbersToKeep){
                elementsToDelete++;
            }else{
                newString[i - elementsToDelete] = str[i];
            }
        } else{
            newString[i - elementsToDelete] = str[i];
            counter = 0;
            isDotWas = 0;
        }
    }

    *length -= elementsToDelete;
    newString = (char*)realloc(newString, *length * sizeof(char));
	newString[*length] = '\0';

    free(str);
    return newString;
}

char* transformString2(char *str, int *length){
    char *newString = (char*)calloc(*length + 1, sizeof(char));
    int counter = 0;
    int isDotWas = 0;
    int elementsToDelete = 0;

    for (int i = 0; i < *length; i++) {
        if(*(str + i) == '.'){
			*(newString + i-elementsToDelete) = *(str + i);
            isDotWas = 1;
            counter = 0;
        } else if(isDotWas == 1 && isNumber(*(str + i)) == 1){
            counter++;
            if(counter > 2){
                elementsToDelete++;
            }else{
                *(newString + i-elementsToDelete) = *(str + i);
            }
        } else{
            *(newString + i-elementsToDelete) = *(str + i);
            counter = 0;
            isDotWas = 0;
        }
    }

    *length -= elementsToDelete;
    newString = (char*)realloc(newString, *length * sizeof(char));
	*(newString + *length) = '\0';

    free(str);
    return newString;
}