#include "functions.h"
#include "../../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeStudentsToFile(Student *students, int amount) {
  FILE *file = fopen(STUDENTS_FILENAME, "wb");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: wb\n",
           STUDENTS_FILENAME);
    return;
  }

  for (int i = 0; i < amount; i++) {
    Student current = *(students + i);
    int strLength = 0;

    strLength = strlen(current.info.firstName) + 1;
    fwrite(&strLength, sizeof(int), 1, file);
    fwrite(&current.info.firstName, sizeof(char), strLength, file);

    strLength = strlen(current.info.lastName) + 1;
    fwrite(&strLength, sizeof(int), 1, file);
    fwrite(&current.info.lastName, sizeof(char), strLength, file);

    strLength = strlen(current.info.patronymic) + 1;
    fwrite(&strLength, sizeof(int), 1, file);
    fwrite(&current.info.patronymic, sizeof(char), strLength, file);

    fwrite(&current.info.semestr, sizeof(int), 1, file);
    fwrite(&current.amount, sizeof(int), 1, file);

    for (int j = 0; j < current.amount; j++) {
      fwrite(current.exams[0].examNumbers + j, sizeof(int), 1, file);
      fwrite(current.exams[1].marks + j, sizeof(float), 1, file);
    }
  }

  fclose(file);
  return;
}

int readStudentsFromFile(Student **all, Exams exams) {
  FILE *file = fopen(STUDENTS_FILENAME, "rb");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: rb\n",
           STUDENTS_FILENAME);
    return 0;
  }

  int counter = 0;
  int length = 0;

  while (fread(&length, sizeof(int), 1, file) == 1) {
    counter++;
    *all = (Student *)realloc(*all, sizeof(Student) * counter);
    Student *current = *all + counter - 1;

    fread(current->info.firstName, sizeof(char), length, file);

    fread(&length, sizeof(int), 1, file);
    fread(current->info.lastName, sizeof(char), length, file);

    fread(&length, sizeof(int), 1, file);
    fread(current->info.patronymic, sizeof(char), length, file);

    fread(&current->info.semestr, sizeof(int), 1, file);
    fread(&current->amount, sizeof(int), 1, file);

    current->exams[0].examNumbers =
        (int *)malloc(sizeof(int) * current->amount);
    current->exams[1].marks = (float *)malloc(sizeof(float) * current->amount);

    for (int i = 0; i < current->amount; i++) {
      int examIdx;
      float mark;

      fread(&examIdx, sizeof(int), 1, file);
      fread(&mark, sizeof(float), 1, file);

      *(current->exams[0].examNumbers + i) = examIdx;
      *(current->exams[1].marks + i) = mark;
    }
  }

  fclose(file);
  return counter;
}

void writeExamsToFile(Exams exams) {
  FILE *file = fopen(EXAMS_FILENAME, "wb");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: wb\n",
           STUDENTS_FILENAME);
    return;
  }

  for (int i = 0; i < exams.amount; i++) {
    int len = strlen(*(exams.exams + i)) + 1;
    fwrite(&i, sizeof(int), 1, file);
    fwrite(&len, sizeof(int), 1, file);
    fwrite(*(exams.exams + i), sizeof(char), len, file);
  }

  fclose(file);
  return;
}

Exams readExamsFromFile() {
  Exams exams;
  exams.exams = NULL;
  exams.amount = 0;

  FILE *file = fopen(EXAMS_FILENAME, "rb");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: rb\n",
           EXAMS_FILENAME);
    return exams;
  }

  int indexOfExam = 0;
  while (fread(&indexOfExam, sizeof(int), 1, file) == 1) {
    exams.amount++;
    exams.exams = (char **)realloc(exams.exams, sizeof(char *) * exams.amount);

    int lenOfName = 0;
    fread(&lenOfName, sizeof(int), 1, file);

    *(exams.exams + exams.amount - 1) =
        (char *)malloc(sizeof(char) * lenOfName);

    fread(*(exams.exams + exams.amount - 1), sizeof(char), lenOfName, file);
  }

  fclose(file);
  return exams;
}

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

void addStudents(Student **students, Exams exams, int *studentsAmount) {
  int amount = inputNumber("Enter how many students to add: ", 1, 20);
  *studentsAmount += amount;

  *students = (Student *)realloc(*students, sizeof(Student) * *studentsAmount);

  for (int i = *studentsAmount - amount; i < *studentsAmount; i++) {
    printf("\nCreating of student number %d: \n", i + 1);
    initStudent(*students + i, exams);
  }
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

void addExams(Exams *exams) {
  int count = inputNumber("Enter how many exams to add: ", 1, 20);

  exams->amount += count;
  exams->exams = (char **)realloc(exams->exams, exams->amount * sizeof(char *));

  for (int i = exams->amount - count; i < exams->amount; i++) {
    *(exams->exams + i) = (char *)malloc(sizeof(char));
    printf("Enter exam number %d: ", i);
    scanf("%49s", *(exams->exams + i));

    for (int j = 0; j < exams->amount - count; j++) {
      if (strcmp(*(exams->exams + i), *(exams->exams + j)) == 0) {
        printf("already exists!\n");
        free(*(exams->exams + i));
        i--;
        break;
      }
    }
  }
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
