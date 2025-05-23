#include "../../utils/utils.h"
#include "functions.h"
#include <stdio.h>

int main() {
  Exams exams;
  StudentsList *students = NewStudentsList();
  int studentsAmount = -1;
  int option = -1;

  while (option != 0) {
    printf("\n========OPTIONS=======\n");
    printf("1 - read from binary\n2 - read from text\n3 - write to binary\n4 - "
           "write to text\n5 - find students by semestr\n6 - find students by "
           "lastname\n7 - add students\n8 - add exams\n0 - quit\n");
    option = inputNumber("Option: ", 0, 8);

    switch (option) {
    case 1: {
      if (studentsAmount != -1) {
        printf("data already read\n");
        break;
      }
      exams = readExamsFromBinaryFile();
      studentsAmount = readStudentsFromBinaryFile(students, exams);
      break;
    }
    case 2: {
      if (studentsAmount != -1) {
        printf("data already read\n");
        break;
      }
      printf("currently not available\n");
      break;
    }
    case 3: {
      if (studentsAmount == -1) {
        printf("data has not yet been read from the file\n");
        break;
      }
      writeExamsToBinaryFile(exams);
      writeStudentsToBinaryFile(students, studentsAmount);
      option = 0; // for exit
      freeStudents(students);
      break;
    }
    case 4: {
      printf("currently not available\n");
      break;
    }
    case 5: {
      if (studentsAmount == -1) {
        printf("data has not yet been read from the file\n");
        break;
      }
      int semestr =
          inputNumber("Enter which semestr you would like to see(-1 - to "
                      "all): ",
                      -1, 8);
      StudentsList *finded = findStudentsBySemestr(students, semestr);
      printStudents(finded, exams);
      freeStudents(finded);
      break;
    }
    case 6: {
      if (studentsAmount == -1) {
        printf("data has not yet been read from the file\n");
        break;
      }
      char lastname[50];
      printf("\nEnter lastname: ");
      scanf("%49s", lastname);
      StudentsList *finded = findStudentsByName(students, lastname);
      printStudents(finded, exams);
      freeStudents(finded);
      break;
    }
    case 7: {
      addStudents(students, exams, &studentsAmount);
      break;
    }
    case 8: {
      addExams(&exams);
      break;
    }
    }
  }
}
