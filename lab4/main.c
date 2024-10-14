#include <stdio.h>

//максимальное значение 978, я проверял
#define MAX 990

//функция очистики потока ввода
void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char *argv[]){
	// printf("Parametrs: ");
	// for (int i = 0; i < argc; i++) {
	// 	printf("\n%s", argv[i]);
	// }
	//инициализация переменных
	int n;
	int inputResult = 0;
	int numbers[MAX];

	//Ввод числа n
	while(inputResult == 0){
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

	return 0;
}