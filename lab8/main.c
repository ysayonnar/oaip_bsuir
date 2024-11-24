#include <stdio.h>
#include <stdlib.h>

void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int isNumber(char symbol){
    if (symbol >='0' && symbol <= '9'){
        return 1;
    }else{
        return 0;
    }
}

char* transformString(char *str, int *length){
    char *newString = (char*)calloc(*length, sizeof(char));
    int counter = 0;
    int isDotWas = 0;
    int elementsToDelete = 0;

    for (int i = 0; i < *length; i++) {
        if(str[i] == '.'){
            newString[i-elementsToDelete] = str[i];
            isDotWas = 1;
            counter = 0;
        }
        else if(isDotWas == 1 && isNumber(str[i]) == 1){
            counter++;
            if(counter > 2){
                elementsToDelete++;
                printf("hello world!");
            }else{
                newString[i - elementsToDelete] = str[i];
            }
        }
        else{
            newString[i - elementsToDelete] = str[i];
            counter = 0;
            isDotWas = 0;
        }
    }

    *length -= elementsToDelete;
    newString = (char*)realloc(newString, *length * sizeof(char));
    free(str);
    return newString;
}

int main(void){
    int n = 0;
    int scanfRes = 0;
    char *str;

    while(scanfRes == 0){
        printf("Enter string length: ");
        scanfRes = scanf("%d", &n);
        if(scanfRes == 0){
            printf("Invalid input!\n");
            clearBuffer();
        }
        if(n < 0) {
            printf("Invalid n\n");
            clearBuffer();
            scanfRes = 0;
            n = 0;
        }
    }
    clearBuffer();

    str = (char*)calloc(n + 1, sizeof(char));
    printf("enter string: ");
    fgets(str, n + 1, stdin);
    printf("BEFORE TRANSFORMING string: %s, length: %d\n", str, n);

    str = transformString(str, &n);
    printf("AFTER TRANSFORMING string: %s, length: %d\n", str, n);
    
    free(str);
}