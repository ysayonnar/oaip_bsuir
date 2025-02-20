#include <stdlib.h>
#include "functions.h"

int main(void){
		int n = inputNumber("Enter maximum string length: ", 1, 100); //ввод длины строки
		int numbersToKeep = inputNumber("Enter how many numbers to delete: ", 1, 100);
		char *str = inputString(n); //ввод строки
		printString("Before: ", str);
		str = transformString(str, &n, numbersToKeep);//преобразование строки
		printString("After: ", str);
		free(str);
		// printf("Do you want to continue(1 - yes)?: ");
		// scanf("%d", &userResponse);
}
