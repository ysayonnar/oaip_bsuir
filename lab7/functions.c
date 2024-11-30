#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int inputInteger(int min, int max){
	int number = 0;
	int scanfResult = 0;
	while(scanfResult == 0){	
		printf("Enter number: ");
		scanfResult = scanf("%d", &number);
		if(scanfResult == 0){
			printf("\033[1;31m\tIncorrect input!\n\033[0m");
		}else if(number > max || number < min){
			printf("\033[1;31m\tMust be from %d to %d!\n\033[0m", min, max);
			scanfResult = 0;
		}
		clearBuffer();
	}
	return number;
}

int inputMatrixOrder(){
	int matrixOrder = 0;
	int scanfResult = 0;
	while (matrixOrder < 2){
		printf("Enter matrix order: ");
		scanfResult = scanf("%d", &matrixOrder);
		if(scanfResult == 0){
			printf("\033[1;31m\tIncorrect input!\n\033[0m");
		}else if(matrixOrder < 2){
			printf("\033[1;31m\tMatrix order cant be %d!\n\033[0m", matrixOrder);
		}
		clearBuffer();
	}
	return matrixOrder;
}

double** create2DArray(int rows, int cols){
	double **arr;
	arr = (double**)calloc(rows, sizeof(double*));
	for (int i = 0; i < rows; i++) {
		*(arr + i) = (double*)calloc(cols, sizeof(double));
	}
	return arr;
}

void input2DArrayManually(double** arr, int rows, int cols){
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int scanfResult = 0;
			while(scanfResult == 0){
				printf("Enter element with index [%dx%d]: ", i, j);
				scanfResult = scanf("%lf", *(arr + i) + j);
				if(scanfResult == 0){
					printf("\033[1;31m\tIncorrect input!\n\033[0m");
				}
				clearBuffer();
			}
		}
	}
}

void input2DArrayRandomly(double** arr, int rows, int cols){
	int lowerBound = 0, upperBound = 0;
	int inputResult = 0;
	while(inputResult == 0){
		printf("Enter the lower and upper bounds (from -10000 to 10000):");
		inputResult = scanf("%d %d", &lowerBound, &upperBound);
		if (inputResult == 2){
			if (lowerBound < -10000 || upperBound > 10000){
				printf("\033[1;31m\tOut of Bounds!\n\033[0m");
				inputResult = 0;
			}
			if(lowerBound >= upperBound){
				printf("\033[1;31m\tMinimal cant be greater than maximum!\n\033[0m");
				inputResult = 0;
			}
		}else{
			printf("\033[1;31m\tIncorrect input!\n\033[0m");
			inputResult = 0;
		}
		clearBuffer();
	}
	srand(time(0));
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double scale = rand() / (double) RAND_MAX; 
			*(*(arr + i) + j) = lowerBound + scale * (upperBound - lowerBound);
		}
	}
}

void print2DArray(double** arr, int rows, int cols, int columnIndexToHighlight){
	for (int i = 0; i < rows; i++) {
		printf("|");
		for (int j = 0; j < cols; j++) {
			if(j == columnIndexToHighlight){
				printf("\033[1;34m%10.2lf\033[0m", *(*(arr + i) + j));
			}else{
				printf("%10.2lf", *(*(arr + i) + j));
			}
		}
		printf("|\n");
	}
}

void freeMemory2DArray(double** arr, int rows){
	for(int i = 0; i < rows; i++){
		free(*(arr + i));
	}
	free(arr);
}

double* createArray(int length){
	double *arr;
	arr = (double*)calloc(length, sizeof(double));
	return arr;
}

void inputArray(double *arr, int length){
	for (int i = 0; i < length; i++) {
		int scanfResult = 0;
		while(scanfResult == 0){
			printf("Enter element with index [%d]: ", i);
			scanfResult = scanf("%lf", arr + i);
			if(scanfResult == 0){
				printf("\033[1;31m\tIncorrect input!\n\033[0m");
			}
			clearBuffer();
		}
	}
}

double** insertColumn(double **arr, double *numbers, int rows, int cols, int columnIndex){
	int newColumnsLength = cols + 1;
	double **transformedArray = create2DArray(rows, newColumnsLength);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < newColumnsLength; j++) {
			if(j == columnIndex){
				*(*(transformedArray + i) + j) = *(numbers + i);
			}else if(j < columnIndex){
				*(*(transformedArray + i) + j) = *(*(arr + i) + j);
			}else{
				*(*(transformedArray + i) + j) = *(*(arr + i) + j - 1);
			}
		}
	}
	return transformedArray;
}