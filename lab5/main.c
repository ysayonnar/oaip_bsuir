#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//директивы препроцессора
#define ROWS 5
#define COLUMNS 5

//функция для очистки потока ввода
void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int main(void){
	//ининциализация переменных
	int matrix[ROWS][COLUMNS];
	int response = 0;
	int sum = 0;
	int repeatResult = 0;

	//цикл while для зацикливания программы
	while(1){
		//даем пользователю выбор: вводить массив вручную, либо заполнить случайными числами
		while(response == 0){
			printf("Do you want the array to be filled with random values or to fill it manually?(1 - random/2 - manualy):");
			scanf("%d", &response);
			if (response != 1 && response != 2){
				printf("Incorrect input!\n");
				response = 0;
			}	
			clearBuffer(); //очищаем поток ввода
		}

		//пользователь выбрал заполнение случайными числами
		if (response == 1){
			int minimal = 0, maximum = 0, inputResult = 0;
			//вводим нижнюю и верхнюю границу для случайных чисел
			while(inputResult == 0){
				printf("Enter the lower and upper bounds (from -10000 to 10000):");
				inputResult = scanf("%d %d", &minimal, &maximum);
				// printf("\nminimal: %d, maximum: %d\n", minimal, maximum);
				if (inputResult == 2){
					//проверка на выход из границ
					if (minimal < -10000 || maximum > 10000){
						printf("Out of Bonds!\n");
						inputResult = 0;
					}
					//проверка на то чтобы нижняя граница не была больше верхней
					if(minimal >= maximum){
						printf("Minimal cant be greater than maximum!\n");
						inputResult = 0;
					}
				}else{
					printf("Incorrect input!\n");
					inputResult = 0;
				}
				clearBuffer();//очищаем поток ввода
			}

			srand(time(0));//создаем seed для генерации случайных чисел по времени, иначе при каждом запуску числа будут одинаковые
			for (int i = 0; i < ROWS; i++){
				for (int j = 0; j < COLUMNS; j++){
					//заполняем массив случайными числами
					matrix[i][j] = minimal + rand() % (maximum - minimal + 1);
				}			
			}
		}
		
		//вариант заполнения вручную
		if(response == 2){
			int inputInfo;
			for (int i = 0; i < ROWS; i++){
				for (int j = 0; j < COLUMNS; j++){
					inputInfo = 0;
					while(inputInfo != 1){
						printf("Enter element with indexes %dx%d: ",i + 1, j + 1);
						inputInfo = scanf("%d", &matrix[i][j]);
						if(inputInfo != 1){
							printf("Invalid input!\n");
						}
						clearBuffer();//очищаем поток ввода
					}
				}
			}
		}

		printf("Array looks like:\n");

		//вывод массива и счет суммы 
		for(int i = 0; i < ROWS; i++){
			printf("|");
			for (int j = 0; j < COLUMNS; j++){
				printf(" %5d ", matrix[i][j]);
				//условие для суммирования, два амперсанта можно заменить на логическое или, тк в условии не совсем точно сказано
				if(matrix[i][j] % 2 != 0 && (i + j) % 2 == 0){
					sum += matrix[i][j];
				}
			}
			printf("|\n");
		}
		
		//выводим сумму
		printf("The sum of the elements having odd values and standing in even places is %d", sum);
		
		//спрашиваем у пользователя желает ли он продолжить выполнение
		printf("\nDo you want to continue?(1-yes): ");
		scanf("%d", &repeatResult);
		if (repeatResult != 1){
			//выходим из программы
			break;
		}else{
			//обнуляем переменные, массив можем не обновлять, так как он будет перезаполнен
			response = 0;
			sum = 0;
			repeatResult = 0;
			clearBuffer(); //очищаем поток ввода
			continue;
		}
	}
}