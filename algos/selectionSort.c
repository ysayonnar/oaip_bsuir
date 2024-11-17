#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int* createArray(int length){
	int *arr = (int*)calloc(length, sizeof(int));
	return arr;
}

void fillArray(int *arr, int length){
	for (int i = 0; i < length; i++) {
        arr[i] = rand() % 10001;
    }
}

void printArray(int *arr, int length){
	for (int i = 0; i < length; i++) {
		printf("\033[1;32m");
		printf("%d ", arr[i]);
		printf("\033[0m");
	}
}

void selectionSort(int *arr, int length){
	for (int i = 0; i < length - 1; i++) {
		int minimalIndex = i;
		for(int j = i; j < length; j++){
			if(arr[j] < arr[minimalIndex]){
				minimalIndex = j;
			}
		}
		
		if(minimalIndex != i){
			int temp = arr[i];
			arr[i] = arr[minimalIndex];
			arr[minimalIndex] = temp;
		}
	}
}

void isSorted(int *arr, int length){
	for (int i = 0; i < length - 1; i++) {
		if(arr[i + 1] < arr[i]){
			printf("\n\nNOT SORTED!");
			return;
		}
	}
	printf("\n\nSORTED!");
}

int main(){
	srand(time(NULL));
	int length = 10;
	printf("Enter length: ");
	scanf("%d", &length);
	int *arr = createArray(length);
	fillArray(arr, length);

	printf("Array before sorting: ");
	printArray(arr, length);

	selectionSort(arr, length);

	printf("\nArray after sorting: ");
	printArray(arr, length);

	isSorted(arr, length);

	free(arr);
}