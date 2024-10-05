#include <math.h>
#include <stdio.h>

int main(void) {
    //инициализация переменных
    int a,b,c;
    double discriminant;
    int inputInfo = 0;
    int response;

    while(1) {
        //ввод параметров уравения
        while(inputInfo != 3) {
            printf("\nEnter a,b,c parameters for the equation(use space): ");
            inputInfo = scanf("%d %d %d", &a, &b, &c);

            //проверка на то чтобы параметры уравнения не были равны нулю
            if (b == 0 || c ==0) {
                inputInfo = 0;
                printf("Parameters of the equation cant be zero!");
                fflush(stdin);// очистка потока ввода
                continue;
            }
            if(inputInfo != 3) {
                printf("Invalid input, try again!\n");
            }
            fflush(stdin); //очистка потока ввода
        }

        //решение линейного уравения(a = 0)
        if (a == 0 && b != 0) {
            //вывод вида уравнения
            printf("Your equation looks like: %dx + %d = 0", b, c);
            float solve = -1.0 * c / b;
            printf("\nEquation is linear, x = %.2f", solve);

        }else {
            //решения квадратного уравнения
            //вывод вида уравнения
            printf("Your equation looks like: %d * x^2 + %d * x + %d = 0\n",a,b,c);
            //вычисление дискриминанта уравнения
            discriminant = b*b - 4*a*c;
            printf("\n\nD = %.3f\n\n", discriminant);

            //проверка дискриминанта
            if(discriminant < 0) {
                printf("D < 0, no real roots.");
            } else if (discriminant == 0) {
                //подсчет корней уравения
                double solve = -1 * b / 2 / a;
                printf("D = 0, one real root, x = %.2f", solve);
            }else {
                //подсчет корней уравения
                double solve1 = (-1 * b + sqrt(discriminant))/2/a;
                double solve2 = (-1 * b - sqrt(discriminant))/2/a;
                printf("D > 0, two real roots, x1 = %.2f, x2 = %.2f", solve1, solve2);
            }
        }

        //обнуление переменной ответа
        response = 0;
        printf("\n\nDo you want to solve equation again?(1 - yes/0 - no): ");
        scanf("%d", &response);

        if(response == 1) {
            fflush(stdin); //очистка потока ввода
            inputInfo = 0; // очистка переменной информации о вводе
        }else {
            break;
        }
    }
    return 0;
}