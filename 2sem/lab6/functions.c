#include "functions.h"
#include "../../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50
#define STUDENTS_FILENAME "students.txt"
#define EXAMS_FILENAME "exams.txt"

void writeStudentsToFile(Student *students, int amount) {
  FILE *file = fopen(STUDENTS_FILENAME, "w");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: w\n",
           STUDENTS_FILENAME);
    return;
  }

  for (int i = 0; i < amount; i++) {
    Student current = *(students + i);
    fprintf(file, "%s %s %s %d %d ", current.info.firstName,
            current.info.lastName, current.info.patronymic,
            current.info.semestr, current.amount);

    for (int j = 0; j < current.amount; j++) {
      fprintf(file, "%d %f ", *(current.exams[0].examNumbers + j),
              *(current.exams[1].marks + j));
    }

    fprintf(file, "\n");
  }

  fclose(file);
  return;
}

int readStudentsFromFile(Student **all, Exams exams) {
  FILE *file = fopen(STUDENTS_FILENAME, "r");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: r\n",
           STUDENTS_FILENAME);
    return 0;
  }

  int counter = 0;
  char line[256];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    if (line[0] == '\n') {
      return counter;
    }

    counter++;
    *all = (Student *)realloc(*all, sizeof(Student) * counter);
    Student *current = *all + counter - 1;

    int marksAmount;
    sscanf(line, "%s %s %s %d %d", current->info.firstName,
           current->info.lastName, current->info.patronymic,
           &(current->info.semestr), &marksAmount);
    current->amount = marksAmount;

    char *markPairsPointer = line;
    for (int i = 0; i < 5; i++) {
      markPairsPointer += strcspn(markPairsPointer, " \t");
      markPairsPointer += strspn(markPairsPointer, " \t");
    }

    current->exams[0].examNumbers = (int *)malloc(sizeof(int) * marksAmount);
    current->exams[1].marks = (float *)malloc(sizeof(float) * marksAmount);

    for (int i = 0; i < marksAmount; i++) {
      int examIdx;
      float mark;
      sscanf(markPairsPointer, "%d %f", &examIdx, &mark);

      *(current->exams[0].examNumbers + i) = examIdx;
      *(current->exams[1].marks + i) = mark;

      markPairsPointer += strcspn(markPairsPointer, " \t");
      markPairsPointer += strspn(markPairsPointer, " \t");
    }
  }

  fclose(file);
  return counter;
}

void writeExamsToFile(Exams exams) {
  FILE *file = fopen(EXAMS_FILENAME, "w");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: w\n",
           STUDENTS_FILENAME);
    return;
  }

  for (int i = 0; i < exams.amount; i++) {
    fprintf(file, "%d %s\n", i, *(exams.exams + i));
  }

  fclose(file);
  return;
}

Exams readExamsFromFile() {
  Exams exams;
  exams.amount = 0;

  FILE *file = fopen(EXAMS_FILENAME, "r");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: r\n", EXAMS_FILENAME);
    return exams;
  }

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    if (line[0] == '\n') {
      return exams;
    }

    exams.amount++;
    exams.exams = (char **)realloc(exams.exams, sizeof(char *) * exams.amount);
    *(exams.exams + exams.amount - 1) = (char *)malloc(sizeof(char));

    int idx;
    sscanf(line, "%d %s", &idx, *(exams.exams + exams.amount - 1));
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
