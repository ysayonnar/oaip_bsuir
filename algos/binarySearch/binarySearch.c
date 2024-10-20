#include <stdio.h>
#define LENGTH 20

int main(void){
	int item = 0;
	int arr[LENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int middle;
	int minimal = 0;
	int maximum = LENGTH - 1; 

	while(minimal <= maximum){
		middle = (minimal + maximum) / 2;

		if(arr[middle] == item){
			printf("Index of %d is [%d]", item, middle);
			return 0;
		}else if(arr[middle] < item){
			minimal = middle + 1; 
		}else{
			maximum = middle - 1;
		}
	}

	printf("Element is not found!");
	return 0;
}