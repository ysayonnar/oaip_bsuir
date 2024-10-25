#include <stdlib.h>
#include <stdio.h>

int main(void){
	int length;
	int *arr;

	printf("Enter the length of the array: ");
	scanf("%d", &length);

	arr = malloc(sizeof(int) * length);

	*arr = 1;
	for (int i = 1; i < length; i++) {
		*(arr + i) = *(arr + i - 1) * 2;  
	}

	printf("\n");
	for(int i = 0; i < length; i++){
		printf("%d ", *(arr + i));
	}
	printf("\nChanging the array...\n");
	length += 4;
	arr = realloc(arr, sizeof(int) * length);
	
	for(int i = length - 4; i < length; i++){
		*(arr+i) = 11;
	}
	
	for(int i = 0; i < length; i++){
		printf("%d ", *(arr + i));
	}

	free(arr);
}
