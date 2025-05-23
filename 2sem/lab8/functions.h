#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_LENGTH 50
#define STUDENTS_FILENAME_BINARY "data/students"
#define EXAMS_FILENAME_BINARY "data/exams"
#define STUDENTS_FILENAME_TEXT "data/students.txt"
#define EXAMS_FILENAME_TEXT "data/exams.txt"

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

void writeStudentsToBinaryFile(StudentsList *students, int amount);

int readStudentsFromBinaryFile(StudentsList *all, Exams exams);

void writeExamsToBinaryFile(Exams exams);

Exams readExamsFromBinaryFile();

void writeStudentsToTextFile(StudentsList *students, int amount);

int readStudentsFromTextFile(StudentsList *all, Exams exams);

void writeExamsToTextFile(Exams exams);

Exams readExamsFromTextFile();

void initStudents(StudentsList *studentsList, Exams exams,
                  int amount); // amount - количество создаваемых

void initStudent(StudentNode *studentNode, Exams exams);

Exams initExams();

void addStudents(StudentsList *students, Exams exams, int *studentsAmount);

void addExams(Exams *exams);

StudentsList *findStudentsBySemestr(StudentsList *studentsList, int semestr);

StudentsList *findStudentsByName(StudentsList *studentsList,
                                 char targetFio[50]);

void printStudents(StudentsList *studentsList, Exams exams);

void freeStudents(StudentsList *studentsList);

#endif
