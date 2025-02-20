#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct Company {
	char *name;
	char *tax;
	char *deadline;
	char *paymentDate;
};

struct Companies {
	struct Company* companies;
	int maxNameLength;
	int count;
};

struct Companies initCompanies();
int inputNumber(char* message, int min, int max);
void addCompany(struct Companies *companies);
void printAll(struct Companies companies);
void printTop(struct Companies companies);
void clearBuffer();
void clearScreen();
void freeCompanies(struct Companies *companies);
struct Companies searchCompaniesByTax(struct Companies companies, float tax);

#endif