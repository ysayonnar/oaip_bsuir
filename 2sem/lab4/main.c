#include "../../utils/utils.h"
#include "functions.h"
#include <stdio.h>

int main() {
  Exams exams = initExams();
  int amount = inputNumber("Enter how many students to create: ", 1, 20);

  StudentsList *studentsList = NewStudentsList();
  initStudents(studentsList, exams, amount);

  int ans = -1;
  while (ans != 0) {
    StudentsList *finded;
    ans = inputNumber(
        "Find for lastname or semestr?(1 - lastname, 2 - semestr, 0 - quit):",
        0, 2);
    if (ans == 1) {
      char lastname[50];
      printf("\nEnter lastname: ");
      scanf("%49s", lastname);
      finded = findStudentsByName(studentsList, lastname);
      printStudents(finded, exams);
      freeStudents(finded);
    } else if (ans == 2) {
      int semestr =
          inputNumber("Enter which semestr you would like to see(-1 - to "
                      "all): ",
                      -1, 8);
      finded = findStudentsBySemestr(studentsList, semestr);
      printStudents(finded, exams);
      freeStudents(finded);
    }
  }

  freeStudents(studentsList);
}
