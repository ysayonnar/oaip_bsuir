#include "../../utils/utils.h"
#include "functions.h"

int main() {
  Exams exams = readExamsFromFile();
  if (exams.amount == 0) {
    exams = initExams();
  } else if (inputNumber("Do you want to add exams?(1 - yes): ", 0, 1) == 1) {
    addExams(&exams);
  }

  Student *students;
  int studentsAmount = readStudentsFromFile(&students, exams);
  if (studentsAmount == 0) {
    studentsAmount = inputNumber("Enter how many students to create: ", 1, 20);
    initStudents(&students, exams, studentsAmount);
  } else if (inputNumber("Do you want to add students?(1 - yes): ", 0, 1) ==
             1) {
    addStudents(&students, exams, &studentsAmount);
  }

  int ans = -1;
  while (ans != 0) {
    ans = inputNumber(
        "Enter which semestr you would like to see(-1 - to all, 0 - to quit): ",
        -1, 8);
    printStudentsBySemestr(students, exams, ans, studentsAmount);
  }

  writeStudentsToFile(students, studentsAmount);
  writeExamsToFile(exams);
}
