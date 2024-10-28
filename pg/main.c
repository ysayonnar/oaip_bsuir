#include <stdio.h>

int main() {
    int rows = 20;
    int cols = 10; 

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i % 2 == 0) {
                printf("%3d ", i + j);
            } else {
                printf("%3d ", 100 - i - j);
            }
        }
        printf("\n");
    }
}
