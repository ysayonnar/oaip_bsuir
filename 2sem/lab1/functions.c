#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

void clearScreen(){
	printf("\033[H\033[2J");
}

int inputNumber(char* message, int min, int max){
    int n = 0;
    int scanfRes = 0;

    while(scanfRes == 0){
        printf("%s", message);
        scanfRes = scanf("%d", &n);
        if(scanfRes == 0){
            printf("\033[1;31m\tInvalid Input!\033[0m\n");
        }
        else if(n < min || n > max) {
            printf("\033[1;31m\tNumber must be from %d to %d!\033[0m\n", min, max);
            scanfRes = 0;
            n = 0;
        }
		clearBuffer();
    }

	return n;
}

void inputString(char *str, int max_len) {
    if (!str || max_len == 0) return; 
    fgets(str, max_len, stdin);

    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
	clearBuffer();
}

int strLength(char *str) {
    int length = 0;
    while (*(str + length) != '\0') {
        length++;
    }
    return length;
}

int compareStrings(char *str1, char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

int isDateValid(char *date){
	int day, month, year;

	if(compareStrings(date, "0") == 0 ){
		return 1;
	}

	//проверка формата даты
	if (sscanf(date, "%2d.%2d.%4d", &day, &month, &year) != 3){
		return 0;
	}

	if(month < 1 || month > 12){
		return 0;
	}

	int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	//високосный год
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
		days_in_month[1] = 29;
	}

    if (day < 1 || day > days_in_month[month - 1]){
		return 0;
	}

    return 1;
}

int validateFormatTax(char *input, float *number) {
    char unit[20];
    
    if (sscanf(input, "%f %s", number, unit) != 2) {
        return 0;
    }
    
    if (compareStrings(unit, "mln") == 0) {
        *number *= 1000000;
    } else if (compareStrings(unit, "thousand") == 0) {
        *number *= 1000;
    } else if (compareStrings(unit, "hundred") == 0) {
        *number *= 100;
    } else {
        return 0;
    }
    
    return 1;
}

float getValidInputTax(char *input) {
    float number;
    
    while (1) {
        printf("Enter a value (format: n mln/thousand/hundred): ");
        fgets(input, 20, stdin);
        input[strcspn(input, "\n")] = 0;
		
		clearBuffer();
        if (validateFormatTax(input, &number)) {
            return number;
        }
    
    	printf("\033[1;31m\tInvalid tax format!\033[0m\n");
    }
}

void inputDate(char *msg, char *date){
	while (1) {
		printf("%s format DD.MM.YYYY: ", msg);
		fgets(date, 11, stdin);
		clearBuffer();

		for(int i = 0; date[i] != '\0'; i++){
			if(date[i] == '\n'){
				date[i] = '\0';
				break;
			}
		}

		if(isDateValid(date) == 1){
			break;
		}
		printf("\033[1;31m\tInvalid date format!\033[0m\n");
	}
}

struct Companies searchCompaniesByTax(struct Companies companies, float tax){
	struct Companies newCompanies = {.maxNameLength =  companies.maxNameLength, .count = companies.count};

	newCompanies.companies = (struct Company*)calloc(newCompanies.count, sizeof(struct Company));

	int counter = 0;
	for(int i = 0; i < companies.count; i++){
		float currentTax;
		validateFormatTax(companies.companies[i].tax, &currentTax);
		if (currentTax >= tax){
			newCompanies.companies[counter].name = companies.companies[i].name;
			newCompanies.companies[counter].deadline = companies.companies[i].deadline; 
			newCompanies.companies[counter].paymentDate = companies.companies[i].paymentDate; 
			newCompanies.companies[counter].tax = companies.companies[i].tax; 
			counter++;			
		}
	}
	
	newCompanies.count = counter;
	newCompanies.companies = (struct Company*)realloc(newCompanies.companies, counter * sizeof(struct Company));

	if(counter == 0) {
		printf("Not found!");
	}else{
		printAll(newCompanies);
	}
}

void bubbleSortCompaniesByTax(struct Companies *companies) {
    int n = companies->count;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            struct Company *companyA = &companies->companies[j];
            struct Company *companyB = &companies->companies[j + 1];

            float taxA, taxB;
            validateFormatTax(companyA->tax, &taxA);
            validateFormatTax(companyB->tax, &taxB);

            int shouldSwap = 0;

            if (compareStrings(companyA->paymentDate, "0") == 0 && compareStrings(companyB->paymentDate, "0") != 0) {
                shouldSwap = 0;
            } else if (compareStrings(companyA->paymentDate, "0") != 0 && compareStrings(companyB->paymentDate, "0") == 0) {
                shouldSwap = 1;
            } else {
                shouldSwap = taxA > taxB;
            }

            if (shouldSwap) {
                struct Company temp = companies->companies[j];
                companies->companies[j] = companies->companies[j + 1];
                companies->companies[j + 1] = temp;
            }
        }
    }
}

struct Companies initCompanies(){
	int maxLength = inputNumber("Enter max name length: ", 3, 100);
	struct Companies companies = {.maxNameLength =  maxLength, .count = 0};
	return companies;
}

void addCompany(struct Companies *companies){
	if(companies->count == 0){
		companies->companies = (struct Company*)calloc(1, sizeof(struct Company));
	}else{
		companies->companies = (struct Company*)realloc(companies->companies, (companies->count+1) * sizeof(struct Company));
	}
	companies->count++;
	
	//DATE FORMAT: DD.MM.YYYY
	companies->companies[companies->count-1].name = (char*)malloc(companies->maxNameLength * sizeof(char));
	companies->companies[companies->count-1].deadline = (char*)malloc(10 * sizeof(char));
	companies->companies[companies->count-1].paymentDate = (char*)malloc(10 * sizeof(char));
	companies->companies[companies->count-1].tax = (char*)malloc(20 * sizeof(char));

	printf("Enter name of the company(max length %d): ", companies->maxNameLength);
	inputString(companies->companies[companies->count-1].name, companies->maxNameLength);

	getValidInputTax(companies->companies[companies->count-1].tax);
	
	inputDate("Enter tax deadline, ", companies->companies[companies->count-1].deadline);
	inputDate("Enter payment date, zero if doesn't payed, ", companies->companies[companies->count-1].paymentDate);

	printf("Created!\n");

	clearBuffer();
}

void printLine(){
	//стыдно стыдно но впадлу делать нормально
	printf("+");
	printf("-----------------------");
	printf("+");
	printf("-----------------");
	printf("+");
	printf("----------");
	printf("+");
	printf("----------");
	printf("+");
}

void printAll(struct Companies companies){
	printLine();
	printf("\n|\t  Name  \t|       Tax       | Deadline | Payment  |\n");
	printLine();

	for(int i = 0; i < companies.count; i++){
		struct Company cmp = companies.companies[i];
		printf("\n| ");
		if(strLength(cmp.name) > 21){
			for(int i = 0; i < 18; i++){
				printf("%c", cmp.name[i]);
			}
			printf("... |");
		}else{
			printf(" %21s|", cmp.name);
		}

		printf("%17s|", cmp.tax);
		printf("%10s|", cmp.deadline);
		printf("%10s|", cmp.paymentDate);
		printf("\n");
		printLine();
	}

	clearBuffer();
}

void printTop(struct Companies companies){
	int maxCompanies = inputNumber("Enter how many companies to print: ", 1, companies.count);
	bubbleSortCompaniesByTax(&companies);

	int lineLength = 65;
	printLine();
	printf("\n|\t  Name  \t|       Tax       | Deadline | Payment  |\n");
	printLine();

	int ctr = 0;
	for(int i = 0; i < companies.count && ctr < maxCompanies; i++){
		struct Company cmp = companies.companies[i];
		if (compareStrings(cmp.paymentDate, "0") == 0){
			printf("\n| ");
			if(strLength(cmp.name) > 21){
				for(int i = 0; i < 18; i++){
					printf("%c", cmp.name[i]);
				}
				printf("... |");
			}else{
				printf(" %21s|", cmp.name);
			}

			printf("%17s|", cmp.tax);
			printf("%10s|", cmp.deadline);
			printf("%10s|", cmp.paymentDate);
			printf("\n");
			printLine();
			ctr++;
		}
	}

	clearBuffer();
}

void freeCompanies(struct Companies *companies){
	for (int i = 0; i < companies->count; i++) {
		free(companies->companies[i].name);
		free(companies->companies[i].deadline);
		free(companies->companies[i].tax);
		free(companies->companies[i].paymentDate);
	}
	free(companies->companies);
}