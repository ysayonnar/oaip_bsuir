#include "functions.h"

int main(){
	struct Companies companies = initCompanies();
	int choice = 0;

	while (choice != 5){
		choice = inputNumber("\nSelect an option:\n\n1 - add company\n2 - print all\n3 - print debt\n4 - print by tax\n5- quit\n", 1, 5);
		if(choice == 1){
			addCompany(&companies);
		}else if (choice == 2){
			printAll(companies);
		}else if (choice == 3){
			printTop(companies);
		}else if(choice == 4){
			clearBuffer();
			float tax = inputNumber("Input tax: ", 1, 1000000);
			searchCompaniesByTax(companies, tax);
		}

		clearBuffer();
		clearScreen();
	}

	freeCompanies(&companies);
}