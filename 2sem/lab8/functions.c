#include "functions.h"
#include "../../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeStudentsToBinaryFile(StudentsList *students, int amount) {
  FILE *file = fopen(STUDENTS_FILENAME_BINARY, "wb");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: wb\n",
           STUDENTS_FILENAME_BINARY);
    return;
  }

  StudentNode *current = students->head;
  while (current != NULL) {
    int strLength = 0;

    strLength = strlen(current->info.firstName) + 1;
    fwrite(&strLength, sizeof(int), 1, file);
    fwrite(&current->info.firstName, sizeof(char), strLength, file);

    strLength = strlen(current->info.lastName) + 1;
    fwrite(&strLength, sizeof(int), 1, file);
    fwrite(&current->info.lastName, sizeof(char), strLength, file);

    strLength = strlen(current->info.patronymic) + 1;
    fwrite(&strLength, sizeof(int), 1, file);
    fwrite(&current->info.patronymic, sizeof(char), strLength, file);

    fwrite(&current->info.semestr, sizeof(int), 1, file);
    fwrite(&current->amount, sizeof(int), 1, file);

    for (int j = 0; j < current->amount; j++) {
      fwrite(current->exams[0].examNumbers + j, sizeof(int), 1, file);
      fwrite(current->exams[1].marks + j, sizeof(float), 1, file);
    }

    current = current->nextStudent;
  }

  fclose(file);
  return;
}

int readStudentsFromBinaryFile(StudentsList *all, Exams exams) {
  FILE *file = fopen(STUDENTS_FILENAME_BINARY, "rb");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: rb\n",
           STUDENTS_FILENAME_BINARY);
    return 0;
  }

  int counter = 0;
  int length = 0;
  StudentNode *current = (StudentNode *)malloc(sizeof(StudentNode));

  while (fread(&length, sizeof(int), 1, file) == 1) {
    counter++;

    if (counter == 1) {
      all->head = current;
    } else {
      current->nextStudent = (StudentNode *)malloc(sizeof(StudentNode));
      current = current->nextStudent;
    }

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

void writeExamsToBinaryFile(Exams exams) {
  FILE *file = fopen(EXAMS_FILENAME_BINARY, "wb");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: wb\n",
           STUDENTS_FILENAME_BINARY);
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

Exams readExamsFromBinaryFile() {
  Exams exams;
  exams.exams = NULL;
  exams.amount = 0;

  FILE *file = fopen(EXAMS_FILENAME_BINARY, "rb");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: rb\n",
           EXAMS_FILENAME_BINARY);
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

void writeStudentsToTextFile(StudentsList *students, int amount) {
  FILE *file = fopen(STUDENTS_FILENAME_TEXT, "w");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: w\n",
           STUDENTS_FILENAME_TEXT);
    return;
  }

  StudentNode *current = students->head;
  while (current != NULL) {
    fprintf(file, "%s %s %s %d %d ", current->info.firstName,
            current->info.lastName, current->info.patronymic,
            current->info.semestr, current->amount);

    for (int j = 0; j < current->amount; j++) {
      fprintf(file, "%d %f ", *(current->exams[0].examNumbers + j),
              *(current->exams[1].marks + j));
    }
    fprintf(file, "\n");

    current = current->nextStudent;
  }

  fclose(file);
  return;
}

int readStudentsFromTextFile(StudentsList *students, Exams exams) {
  FILE *file = fopen(STUDENTS_FILENAME_TEXT, "r");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: r\n",
           STUDENTS_FILENAME_TEXT);
    return 0;
  }

  StudentNode *current;

  int counter = 0;
  char line[256];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    if (line[0] == '\n') {
      return counter;
    }

    if (counter == 0) {
      students->head = (StudentNode *)malloc(sizeof(StudentNode));
      current = students->head;
    } else {
      current->nextStudent = (StudentNode *)malloc(sizeof(StudentNode));
      current = current->nextStudent;
    }

    counter++;
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

void writeExamsToTextFile(Exams exams) {
  FILE *file = fopen(EXAMS_FILENAME_TEXT, "w");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: w\n",
           STUDENTS_FILENAME_TEXT);
    return;
  }

  for (int i = 0; i < exams.amount; i++) {
    fprintf(file, "%d %s\n", i, *(exams.exams + i));
  }

  fclose(file);
  return;
}

Exams readExamsFromTextFile() {
  Exams exams;
  exams.amount = 0;
  exams.exams = NULL;

  FILE *file = fopen(EXAMS_FILENAME_TEXT, "r");
  if (file == NULL) {
    printf("unexpected error while opening file %s, mode: r\n",
           EXAMS_FILENAME_TEXT);
    return exams;
  }

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    if (line[0] == '\n') {
      break;
    }

    int idx;
    char name[128];

    if (sscanf(line, "%d %127s", &idx, name) != 2) {
      printf("Invalid line format: %s\n", line);
      continue;
    }

    exams.amount++;
    exams.exams = (char **)realloc(exams.exams, sizeof(char *) * exams.amount);
    exams.exams[exams.amount - 1] = (char *)malloc(strlen(name) + 1);
    strcpy(exams.exams[exams.amount - 1], name);
  }

  fclose(file);
  return exams;
}

StudentsList *NewStudentsList() {
  StudentsList *studentsList = (StudentsList *)malloc(sizeof(StudentsList));
  studentsList->head = NULL;
  return studentsList;
}

void addStudents(StudentsList *students, Exams exams, int *studentsAmount) {
  int amount = inputNumber("Enter how many students to add: ", 1, 20);
  *studentsAmount += amount;

  StudentNode *current = students->head;
  if (current != NULL) {
    while (current->nextStudent != NULL) {
      current = current->nextStudent;
    }
  }

  for (int i = *studentsAmount - amount; i < *studentsAmount; i++) {
    if (current == NULL) {
      students->head = (StudentNode *)malloc(sizeof(StudentNode));
      current = students->head;
    } else {
      current->nextStudent = (StudentNode *)malloc(sizeof(StudentNode));
      current = current->nextStudent;
    }

    printf("\nCreating of student number %d: \n", i + 1);
    initStudent(current, exams);
  }
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
