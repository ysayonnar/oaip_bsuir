#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(){
	int userResponse = 1;

	while(userResponse == 1){
		int scanfResult = 0;
		int typeOfFilling = 0;
		int matrixOrder = inputMatrixOrder();
		double **arr = create2DArray(matrixOrder, matrixOrder); // создание матрицы
		double *numbers = createArray(matrixOrder);// создание массива чисел для вставки

		//выбор варианта заполнения массива
		while(scanfResult == 0){	
			printf("Do you want to fill array randomly or manually(1-random/2-manualy): ");
			scanfResult = scanf("%d", &typeOfFilling);
			if(scanfResult == 0){
				printf("\033[1;31m\tIncorrect input!\n\033[0m");
			}else if(typeOfFilling != 1 && typeOfFilling != 2){
				printf("\033[1;31m\tMust be 1 or 2!\n\033[0m");
				scanfResult = 0;
			}
			clearBuffer();
		}
		//заполнение массива
		if (typeOfFilling == 1) {
			input2DArrayRandomly(arr, matrixOrder, matrixOrder);
		}else if(typeOfFilling == 2){
			input2DArrayManually(arr, matrixOrder, matrixOrder);
		}

		//вывод матрицы
		printf("Your matrix looks like:\n");
		print2DArray(arr, matrixOrder, matrixOrder, -1);

		//ввод вещественных числе для вставки
		printf("Enter number to insert\n");
		inputArray(numbers, matrixOrder);
		//ввод элемента после которого будут вставлены числа
		int columnIndex = -1;
		scanfResult = 0;
		while(scanfResult == 0){
			printf("Enter the column after which the numbers will be inserted: ");
			scanfResult = scanf("%d", &columnIndex);
			if(scanfResult == 0){
				printf("\033[1;31m\tIncorrect input!\n\033[0m");
			}else if(columnIndex < 0 || columnIndex > matrixOrder){
				printf("\033[1;31m\tOut of range!\n\033[0m");
				scanfResult = 0;
			}
			clearBuffer();
		}

		//преобразование массива
		double **transformedArray = insertColumn(arr, numbers, matrixOrder, matrixOrder, columnIndex);
		int newOrder = matrixOrder + 1;
		print2DArray(transformedArray, matrixOrder, newOrder, columnIndex);

		//освобождение памяти
		freeMemory2DArray(transformedArray, matrixOrder);
		freeMemory2DArray(arr, matrixOrder);
		free(numbers);

		printf("Do you want to continue?(1 - yes): ");
		scanf("%d", &userResponse);
	}
}

//gcc main.c functions.c -o main
