#include "functions.h"

int main(){
	void (*task[])(char ****arr, int matrixNumber, int rows, int cols) = {printArrayOfMatrix, findPalindromes};

	int matrixNumber = inputNumber("Enter how many matrices you want to create: ", 1, 20);
	int rows = inputNumber("Enter rows length: ", 2, 20);
	int cols = inputNumber("Enter cols length: ", 2, 20);
	char ****arr = createArrayOfMatrix(matrixNumber, rows, cols);

	task[0](arr, matrixNumber, rows, cols);
	task[1](arr, matrixNumber, rows, cols);

	freeArrayOfMatrix(arr, matrixNumber, rows, cols);
}