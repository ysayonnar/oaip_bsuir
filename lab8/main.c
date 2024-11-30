#include <stdlib.h>
#include "functions.h"

int main(void){
	int n = inputNumber("Enter maximum string length: ", 1, 100);
	char *str = inputString(n);
	printString("Before: ", str);
	str = transformString(str, &n);
	printString("After: ", str);
	free(str);
}

//gcc main.c functions.c -o main
