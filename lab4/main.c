#include <stdio.h>

//директивы препроцессора
//MAX для указания максимального числа n(задает длину массива чисел)
#define MAX 1000

//функция очистики потока ввода
void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int main(){
	//инициализация переменных
	int n = 0;
	int inputResult = 0;
	int numbers[MAX];
	int repeatResult = 0;
	
	//цикл while для  зацикливания программы
	while (1) {
		//Ввод числа n
		while(n < 2 || n > MAX){
			printf("Enter a number n greater than or equal to 2 and not greater than %d: ", MAX);
			inputResult = scanf("%d", &n);
			if(inputResult == 0){
				printf("Incorrect input!\n");
			}else if (n < 2 || n > MAX){ 
				//проверка на выход за пределы границ
				printf("n must be greater than or equal to 2 and not greater than %d!\n", MAX);
				inputResult = 0;
			}
			clearBuffer();//очистка потока ввода
		}
		
		//Заполнение массива
		for (int i = 0; i < MAX; i++){
			//ячейки с индексам, меньшими n - 2 инициализируем нулями
			if (i + 2 <= n){
				numbers[i] = i + 2;
			}else{
				numbers[i] = 0;
			}
		}

		//сама работа алгоритма
		for (int i = 0; i < n - 1; i++){
			//чтобы не терять в производительности пропускаем нули
			if (numbers[i] == 0){
				continue;
			}
			//вложенный цикл, начинаем со следующего после i индекса(i + 1)
			for (int j = i + 1; j < n - 1; j++){
				//проверяем кратность и в случае если число кратно присваиваем нуль(зачеркиваем)
				if(numbers[j] % numbers[i] == 0){
					numbers[j] = 0;
				}
			}
		}
		//выводим только простые числа и пропускаем нули
		printf("Prime number from 2 to %d:\t", n);
		for (int i = 0; i < n; i++){
			if(numbers[i] != 0){
				printf("%d ", numbers[i]);
			}
		}
		
		printf("\nDo you want to continue?(1-yes): ");
		scanf("%d", &repeatResult);
		if (repeatResult != 1){
			//выходим из программы
			break;
		}else{
			//обнуляем переменные, массив можем не обновлять, так как он будет перезаполнен
			n = 0;
			inputResult = 0;
			repeatResult = 0;
			clearBuffer(); //очищаем поток ввода
			continue;
		}
	}
	return 0;
}