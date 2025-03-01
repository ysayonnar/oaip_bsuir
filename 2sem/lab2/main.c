#include "functions.h"
#include "../../utils/utils.h"

int main(){
	Exams exams = initExams();
	int amount = inputNumber("Enter how many students to create: ", 1, 20);
	Student *students;
	initStudents(&students, exams, amount);
	
	int ans = -1;

	while(ans != 0){
		ans = inputNumber("Enter which semestr you would like to see(-1 - to all, 0 - to quit): ", -1,8);
		printStudentsBySemestr(students, ans, amount);
	}

	freeStudents(&students, amount);
}