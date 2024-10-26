#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//функция очистки буфера входного потока
void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int main(void){
	int userResponse = 1;
	//цикл для многоразового использования
	while(userResponse == 1){
		int *matrix;
		int matrixOrder = 0;
		int maximumElement = 0;
		int maximumIndexByRow = 0;
		int maximumIndexByColumn = 0;
		int lowerBound, upperBound;
		int inputResult;

		//ввод порядка матрицы
		while(matrixOrder < 2){
			printf("Enter matrix order: ");
			inputResult = scanf_s("%d", &matrixOrder);
			if(inputResult != 1){
				printf("\033[1;31m"); //окрашивание в красный цвет ошибок
				printf("\tIncorrect input!\n");
				printf("\033[0m"); 
			}else if(matrixOrder < 2){
				printf("\033[1;31m"); 
				printf("\tMatrix order cant be less than 2.\n");
				printf("\033[0m"); 
			}
			clearBuffer();//Очистка буфера потока ввода
			inputResult = 0;
		}
		//выделяем память для матрицы
		matrix = (int *)malloc(sizeof(int) * matrixOrder * matrixOrder);
		
		while(inputResult == 0){
			//ввод максимальной и минимальной границы
			printf("Enter the lower and upper bounds (from -10000 to 10000):");
			inputResult = scanf("%d %d", &lowerBound, &upperBound);
			if (inputResult == 2){
				//проверка на выход из границ
				if (lowerBound < -10000 || upperBound > 10000){
					printf("\033[1;31m"); 
					printf("\tOut of Bounds!\n");
					printf("\033[0m"); 
					inputResult = 0;
				}
				//проверка на то чтобы нижняя граница не была больше верхней
				if(lowerBound >= upperBound){
					printf("\033[1;31m"); 
					printf("\tMinimal cant be greater than maximum!\n");
					printf("\033[0m"); 
					inputResult = 0;
				}
			}else{
				//вывод сообщения о неправильном вводе
				printf("\033[1;31m"); 
				printf("\tIncorrect input!\n");
				printf("\033[0m"); 
				inputResult = 0;
			}
			clearBuffer();//очищаем поток ввода
		}

		srand(time(0));//создаем seed для генерации случайных чисел по времени, иначе при каждом запуску числа будут одинаковые
		for (int i = 0; i < matrixOrder; i++) {
			for (int j = 0; j < matrixOrder; j++) {
				//Заполняем массив случайными числами
				*(matrix + i * matrixOrder + j) = lowerBound + rand() % (upperBound - lowerBound + 1);
			}
		}
		
		//Находим максимальный по модулю элемент и его индексы
		for(int i = 0; i < matrixOrder; i++){
			for (int j = 0; j < matrixOrder; j++) {
				int currentNum = *(matrix + i*matrixOrder + j);
				if(abs(currentNum) > maximumElement){
					maximumElement = abs(currentNum);
					maximumIndexByRow = i;
					maximumIndexByColumn = j;
				}
			}
		}

		//вывод матрицы
		printf("Your matrix looks like this (the greatest element is highlighted):\n");
		for (int i = 0; i < matrixOrder; i++) {
			printf("|");
			for(int j = 0; j < matrixOrder; j++){
				//выделяю элементы
				if (i == maximumIndexByRow && j == maximumIndexByColumn) {
					printf("\033[1;32m"); 
					printf("%6d ", *(matrix + (i*matrixOrder) + j));
					printf("\033[0m"); 
				}else if(i == maximumIndexByRow || j == maximumIndexByColumn){
					printf("\033[1;34m"); 
					printf("%6d ", *(matrix + (i*matrixOrder) + j));
					printf("\033[0m");
				}
				else{
					printf("%6d ", *(matrix + (i*matrixOrder) + j));
				}
			}
			printf("|\n");
		}

		//вывод матрицы без строки и столбца максимального элемента
		printf("Matrix without rows and columns of the maximum element:\n");
		for (int i = 0; i < matrixOrder; i++) {
			if(i == maximumIndexByRow ){
				continue;
			}
			printf("|");
			for (int j = 0; j < matrixOrder; j++) {
				if(j == maximumIndexByColumn){
					continue;
				}
				printf("%6d ", *(matrix + (i*matrixOrder) + j));
			}
			printf("|\n");
		}

		// int scanfResult;
		printf("Do you want to continue?(1-Yes):");
		// scanfResult = scanf("%d", &userResponse);
		if(scanf("%d", &userResponse) == 0){
			userResponse = 0;
		}
		clearBuffer();
		free(matrix); //освобождаем память
	}
}