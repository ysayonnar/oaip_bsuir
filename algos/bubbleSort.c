#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define LENGTH 30


int main(void){
    int arr[LENGTH];
    int temp;

    srand(time(0));
    for (int i = 0; i < LENGTH; i++) {
        arr[i] = rand() % 100;
    }

    printf("Unsorted array: ");
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", arr[i]);
    }

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\n\nSorted array: ");
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");   
	 
}