#include "functions.h"
#include "../../utils/utils.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_LENGTH 50

void initStudents(Student** students, Exams exams, int amount){
	*students = (Student*)malloc(sizeof(Student) * amount);

	for(int i = 0; i < amount; i++){
		printf("\nCreating of student number %d: \n", i + 1);
		initStudent(*students + i, exams);
	}
}

void initStudent(Student *student, Exams exams){
	printf("Enter firstname of student: ");
	scanf("%49s", student->info.firstName);

	printf("Enter lastname of student: ");
	scanf("%49s", student->info.lastName);

	printf("Enter patronymic of student: ");
	scanf("%49s", student->info.patronymic);

	student->info.semestr = inputNumber("Enter number of semestr(1-8): ", 1, 8);

	student->isMarks = inputNumber("Do you want to enter marks of numbers of exams(0 - exams, 1 - marks): ", 0, 1);

	printf("Exams:\n");
	for(int i = 0; i < exams.amount; i++){
		printf("%d - %s\n", i, *(exams.exams + i));
	}
	
	int amountOfExams = inputNumber("Enter how many exams/marks to add: ", 1, exams.amount);

	if(student->isMarks == 0){
		student->exams.examNumbers = (int*)malloc(sizeof(int) * amountOfExams);
	}else {
		student->exams.marks = (float*)malloc(sizeof(float) * amountOfExams);
	}
	
	for(int i = 0; i < amountOfExams; i++){
		if(student->isMarks == 0){
			int idx = inputNumber("Enter index of exam: ", 0, exams.amount - 1);
			*(student->exams.examNumbers + i) = idx;
			for(int j = 0; j < i; j++){
				if(*(student->exams.examNumbers + j) == idx){
					printf("\033[1;31m\tExam already added!\033[0m\n");
					i--;
					break;
				}
			}
		}else{
			float mark = inputFloat("Enter mark of exam: ", 0, 10);
			*(student->exams.marks + i) = mark;
		}
	}
	student->amount = amountOfExams;
}

Exams initExams(){
	int count = inputNumber("Enter how many exams to add: ", 1, 20);
	char **exams = (char**)malloc(count * sizeof(char*));

	for (int i = 0; i < count; i++){
		*(exams + i) = (char*)malloc(sizeof(char));
	}

	for (int i = 0; i < count; i++){
		printf("Enter exam number %d: ", i);
		scanf("%49s", *(exams + i));
	}

	Exams e = {exams, count};
	return e; 
}


void printStudentsBySemestr(Student *students, int semestr, int l){
	int ctr = 0;
    for(int i = 0; i < l; i++){
        Student s = *(students + i);
		if (semestr == -1 || s.info.semestr == semestr){
			ctr++;
		}
	}

	if (ctr == 0){
		printf("\nNot found\n");
		return;
	}

    printf("\n\n");
    printf("%-20s %-20s %-20s %-10s %-30s\n", "First Name", "Last Name", "Patronymic", "Semester", "Exams/Marks");
    printf("----------------------------------------------------------------------------------------------------\n");

    for(int i = 0; i < l; i++){
        Student s = *(students + i);
        if (semestr == -1 || s.info.semestr == semestr){
            printf("%-20s %-20s %-20s %-10d ", s.info.firstName, s.info.lastName, s.info.patronymic, s.info.semestr);

            for(int j = 0; j < s.amount; j++){
                if(s.isMarks == 0){
                    printf("%-10d ", *(s.exams.examNumbers + j)); 
                } else {
                    printf("%.1f %-10s", *(s.exams.marks + j), "");
                }
            }
            printf("\n");
        }
    }
	printf("\n");
}

void freeStudents(Student **students, int l){
	for (int i = 0; i < l; i++) {
		Student *s = *(students + i);
		free(s->info.firstName);
		free(s->info.lastName);
		free(s->info.patronymic);
		free(s->exams.examNumbers);
		free(s->exams.marks);
		free(s);
	}
	free(students);
}

