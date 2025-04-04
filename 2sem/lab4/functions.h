#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
  char **exams;
  int amount;
} Exams;

typedef struct {
  char firstName[50];
  char lastName[50];
  char patronymic[50];
  int semestr;
} StudentInfo;

typedef union {
  int *examNumbers;
  float *marks;
} ExamData;

typedef struct StudentNode {
  StudentInfo info;
  ExamData exams[2]; // [0] - экзамены, [1] - оценки
  int amount;        // количество экзаменов
  struct StudentNode *nextStudent;
} StudentNode;

typedef struct {
  StudentNode *head;
} StudentsList;

StudentsList *NewStudentsList();

void initStudents(StudentsList *studentsList, Exams exams,
                  int amount); // amount - количество создаваемых

void initStudent(StudentNode *studentNode, Exams exams);

Exams initExams();

void printStudentsBySemestr(StudentsList *studentsList, Exams exams,
                            int semestr);

void freeStudents(StudentsList *studentsList);

#endif
