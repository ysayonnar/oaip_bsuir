#include "functions.h"
#include "../../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 50

void initStudents(Student **students, Exams exams, int amount) {
  *students = (Student *)malloc(sizeof(Student) * amount);

  for (int i = 0; i < amount; i++) {
    printf("\nCreating of student number %d: \n", i + 1);
    initStudent(*students + i, exams);
  }
}

void initStudent(Student *student, Exams exams) {
  printf("Enter firstname of student: ");
  scanf("%49s", student->info.firstName);

  printf("Enter lastname of student: ");
  scanf("%49s", student->info.lastName);

  printf("Enter patronymic of student: ");
  scanf("%49s", student->info.patronymic);

  student->info.semestr = inputNumber("Enter number of semestr(1-8): ", 1, 8);

  printf("Exams:\n");
  for (int i = 0; i < exams.amount; i++) {
    printf("%d - %s\n", i, *(exams.exams + i));
  }

  int amountOfExams =
      inputNumber("Enter how many exams/marks to add: ", 1, exams.amount);

  student->exams[0].examNumbers = (int *)malloc(sizeof(int) * amountOfExams);
  student->exams[1].marks = (float *)malloc(sizeof(float) * amountOfExams);

  for (int i = 0; i < amountOfExams; i++) {
    int examIdx = inputNumber("Enter index of exam: ", 0, exams.amount - 1);
    float mark = inputFloat("Enter mark of exam: ", 0, 10);

    *(student->exams[0].examNumbers + i) = examIdx;
    *(student->exams[1].marks + i) = mark;
    for (int j = 0; j < i; j++) {
      if (*(student->exams[0].examNumbers + j) == examIdx) {
        printf("\033[1;31m\tExam already added!\033[0m\n");
        i--;
        break;
      }
    }
  }

  student->amount = amountOfExams;
}

Exams initExams() {
  int count = inputNumber("Enter how many exams to add: ", 1, 20);
  char **exams = (char **)malloc(count * sizeof(char *));

  for (int i = 0; i < count; i++) {
    *(exams + i) = (char *)malloc(sizeof(char));
  }

  for (int i = 0; i < count; i++) {
    printf("Enter exam number %d: ", i);
    scanf("%49s", *(exams + i));
  }

  Exams e = {exams, count};
  return e;
}

void printStudentsBySemestr(Student *students, Exams exams, int semestr,
                            int l) {
  int ctr = 0;
  for (int i = 0; i < l; i++) {
    Student s = *(students + i);
    if (semestr == -1 || s.info.semestr == semestr) {
      ctr++;
    }
  }

  if (ctr == 0) {
    printf("\nNot found\n");
    return;
  }

  printf("\n\n");
  printf("%-20s %-20s %-20s %-10s %-30s\n", "First Name", "Last Name",
         "Patronymic", "Semester", "Exams/Marks");
  printf("---------------------------------------------------------------------"
         "-------------------------------\n");

  for (int i = 0; i < l; i++) {
    Student s = *(students + i);
    if (semestr == -1 || s.info.semestr == semestr) {
      printf("%-20s %-20s %-20s %-10d ", s.info.firstName, s.info.lastName,
             s.info.patronymic, s.info.semestr);

      for (int j = 0; j < s.amount; j++) {
        printf("%s: %.1f, ", exams.exams[*(s.exams[0].examNumbers + j)],
               *(s.exams[1].marks + j));
      }
      printf("\n");
    }
  }
  printf("\n");
}

void freeStudents(Student **students, int l) {
  for (int i = 0; i < l; i++) {
    Student *s = *(students + i);
    free(s->exams[0].examNumbers);
    free(s->exams[1].marks);
    free(s);
  }
  free(students);
}
