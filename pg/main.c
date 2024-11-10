#include <stdio.h>

int add(int, int);

int add(int a, int b){
	return a + b;
}

//разделить лабу на три файла - 
//1.prototypes.h - прототипы функций
//2.funcitons.h - реализации функции
//3.lab7.c - дергать ф-ции

//лаба 7 - 8 варик 

int main(void){
	printf("%d", add(1, 2));	
}