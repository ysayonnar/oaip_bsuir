#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern void clearBuffer();

extern int inputMatrixOrder();

extern double** create2DArray(int rows, int cols);

extern void input2DArrayManually(double** arr, int rows, int cols);

extern void input2DArrayRandomly(double** arr, int cols, int rows);

extern void print2DArray(double** arr, int rows, int cols, int columnIndexToHighlight);

extern void freeMemory2DArray(double** arr, int rows);

extern double* createArray(int length);

extern void inputArray(double* arr, int length);

extern double** insertColumn(double** arr, double* numbers, int rows, int cols, int columnIndex);


#endif