#include "functions.h"
#include "../../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

StudentsList *NewStudentsList() {
  StudentsList *studentsList = (StudentsList *)malloc(sizeof(StudentsList));
  studentsList->head = NULL;
  return studentsList;
}

void initStudents(StudentsList *studentsList, Exams exams, int amount) {
  StudentNode *current = (StudentNode *)malloc(sizeof(StudentNode));
  studentsList->head = current;

  for (int i = 0; i < amount; i++) {
    printf("\nCreating of student number %d: \n", i + 1);
    initStudent(current, exams);

    StudentNode *next = (StudentNode *)malloc(sizeof(StudentNode));
    current->nextStudent = next;

    if (i != amount - 1) {
      current = current->nextStudent;
    }
  }

  current->nextStudent = NULL;
}

void initStudent(StudentNode *studentNode, Exams exams) {
  printf("Enter firstname of student: ");
  scanf("%49s", studentNode->info.firstName);

  printf("Enter lastname of student: ");
  scanf("%49s", studentNode->info.lastName);

  printf("Enter patronymic of student: ");
  scanf("%49s", studentNode->info.patronymic);

  studentNode->info.semestr =
      inputNumber("Enter number of semestr(1-8): ", 1, 8);

  printf("Exams:\n");
  for (int i = 0; i < exams.amount; i++) {
    printf("%d - %s\n", i, *(exams.exams + i));
  }

  int amountOfExams =
      inputNumber("Enter how many exams/marks to add: ", 1, exams.amount);

  studentNode->exams[0].examNumbers =
      (int *)malloc(sizeof(int) * amountOfExams);
  studentNode->exams[1].marks = (float *)malloc(sizeof(float) * amountOfExams);

  for (int i = 0; i < amountOfExams; i++) {
    int examIdx = inputNumber("Enter index of exam: ", 0, exams.amount - 1);
    float mark = inputFloat("Enter mark of exam: ", 0, 10);

    *(studentNode->exams[0].examNumbers + i) = examIdx;
    *(studentNode->exams[1].marks + i) = mark;
    for (int j = 0; j < i; j++) {
      if (*(studentNode->exams[0].examNumbers + j) == examIdx) {
        printf("\033[1;31m\tExam already added!\033[0m\n");
        i--;
        break;
      }
    }
  }

  studentNode->amount = amountOfExams;
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

StudentsList *findStudentsBySemestr(StudentsList *studentsList, int semestr) {
  StudentsList *findedStudents = (StudentsList *)malloc(sizeof(StudentsList));
  findedStudents->head = NULL; // обязательно

  StudentNode *current = studentsList->head;
  StudentNode *last = NULL;

  while (current != NULL) {
    if (current->info.semestr == semestr || semestr == -1) {
      StudentNode *newNode = (StudentNode *)malloc(sizeof(StudentNode));
      newNode->amount = current->amount;
      newNode->exams[0] = current->exams[0];
      newNode->exams[1] = current->exams[1];
      newNode->info = current->info;
      newNode->nextStudent = NULL;

      if (findedStudents->head == NULL) {
        findedStudents->head = newNode;
        last = newNode;
      } else {
        last->nextStudent = newNode;
        last = newNode;
      }
    }
    current = current->nextStudent;
  }

  return findedStudents;
}

StudentsList *findStudentsByName(StudentsList *studentsList,
                                 char targetFio[50]) {
  StudentsList *foundStudents = (StudentsList *)malloc(sizeof(StudentsList));
  foundStudents->head = NULL;

  StudentNode *current = studentsList->head;
  StudentNode *last = NULL;

  while (current != NULL) {
    if (strcmp(current->info.lastName, targetFio) == 0) {
      StudentNode *newNode = (StudentNode *)malloc(sizeof(StudentNode));
      newNode->amount = current->amount;
      newNode->exams[0] = current->exams[0];
      newNode->exams[1] = current->exams[1];
      newNode->info = current->info;
      newNode->nextStudent = NULL;

      if (foundStudents->head == NULL) {
        foundStudents->head = newNode;
        last = newNode;
      } else {
        last->nextStudent = newNode;
        last = newNode;
      }
    }

    current = current->nextStudent;
  }

  return foundStudents;
}

void printStudents(StudentsList *studentsList, Exams exams) {
  StudentNode *current = (StudentNode *)malloc(sizeof(StudentNode));
  current = studentsList->head;

  if (current == 0) {
    printf("\nNot found\n");
    return;
  }

  printf("\n");
  printf("%-20s %-20s %-20s %-10s %-30s\n", "First Name", "Last Name",
         "Patronymic", "Semester", "Exams/Marks");
  printf("---------------------------------------------------------------------"
         "-------------------------------\n");

  while (current != NULL) {
    printf("%-20s %-20s %-20s %-10d ", current->info.firstName,
           current->info.lastName, current->info.patronymic,
           current->info.semestr);

    for (int j = 0; j < current->amount; j++) {
      printf("%s: %.1f, ", exams.exams[*(current->exams[0].examNumbers + j)],
             *(current->exams[1].marks + j));
    }
    printf("\n");

    current = current->nextStudent;
  }
  printf("\n");
}

void freeStudents(StudentsList *students) {
  StudentNode *current = students->head;

  while (current != NULL) {
    StudentNode *prev = current;
    current = current->nextStudent;
    free(prev);
  }

  free(students);
}
