#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
//5
int main(){
	int userResponse = 1;

	while(userResponse == 1){
		int scanfResult = 0;
		int matrixOrder = inputMatrixOrder();
		double **arr = create2DArray(matrixOrder, matrixOrder); // создание матрицы
		double *numbers = createArray(matrixOrder);// создание массива чисел для вставки
		int typeOfFilling = inputInteger(1, 2);//ввод типа заполнения

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
		columnIndex = inputInteger(0, matrixOrder);

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
