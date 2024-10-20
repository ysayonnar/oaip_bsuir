#include <stdio.h>

int main(void){
	int a = 5;
	int *ptr = &a;

	printf("prt: %u, value: %d\n", ptr, *ptr);
	ptr++;
	printf("prt: %u, value: %d\n", ptr, *ptr);

	return 0;
}