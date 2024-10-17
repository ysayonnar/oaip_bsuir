#include <stdio.h>
#define LENGTH 9


int main(void){
    int arr[LENGTH] = {12,3,1,1,5,1,-123,123,10};
    int temp;

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\n");
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", arr[i]);
    }
    
}