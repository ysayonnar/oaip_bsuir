#include <stdlib.h>
#include <stdio.h>

int** deleteLastIndex(int **arrToCopy, int cols, int rows){
    int **new = (int**)malloc(rows * sizeof(int*));
    
    for (int i = 0; i < rows; i++) {
        if (i == rows - 1){
            new[i] = realloc(arrToCopy[i], sizeof(int) * (cols - 1));
        }else{
            new[i] = realloc(arrToCopy[i], sizeof(int) * cols);
        }
    }

    return new;
}

int main(){
	int a, b;
	printf("Hello world!");
	scanf("%d %d", &a, &b);
	int res = a + b;
	printf("result: %d", res);
}
