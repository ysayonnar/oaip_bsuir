#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_LENGTH 50
#define STUDENTS_FILENAME "students"
#define EXAMS_FILENAME "exams"

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

typedef struct {
  StudentInfo info;
  ExamData exams[2]; // [0] - экзамены, [1] - оценки
  int amount;
} Student;

void writeStudentsToFile(Student *students, int amount);

int readStudentsFromFile(Student **students, Exams exams);

void writeExamsToFile(Exams exams);

Exams readExamsFromFile();

void initStudents(Student **students, Exams exams, int amount);

void initStudent(Student *student, Exams exams);

void addStudents(Student **students, Exams exams, int *studentsAmount);

Exams initExams();

void addExams(Exams *exams);

void printStudentsBySemestr(Student *students, Exams exams, int semestr, int l);

void freeStudents(Student **students, int l);

#endif
