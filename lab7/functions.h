#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int inputInteger(int max, int min);

void clearBuffer();

int inputMatrixOrder();

double** create2DArray(int rows, int cols);

void input2DArrayManually(double** arr, int rows, int cols);

void input2DArrayRandomly(double** arr, int cols, int rows);

void print2DArray(double** arr, int rows, int cols, int columnIndexToHighlight);

void freeMemory2DArray(double** arr, int rows);

double* createArray(int length);

void inputArray(double* arr, int length);

double** insertColumn(double** arr, double* numbers, int rows, int cols, int columnIndex);

#endif