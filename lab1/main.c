#include <stdio.h>

int main(void)
{
    //ининциализация переменных
    int arr[6][9];
    int sum[6];
    int inputInfo;
    int response;

    while(1)
        {
        // just for test push to git
		//another test
        //заполнение матрицы(первый цикл - по строкам, второй(вложенный) - по элементам строки)
        for (int i = 0; i < 6; i++)
            {
            for (int j = 0; j < 9; j++)
                {
                inputInfo = 0;
                //проверка на правильный ввод
                while(inputInfo != 1)
                    {
                    printf("Enter element with indexes %dx%d:",i + 1, j + 1);
                    inputInfo = scanf("%d", &arr[i][j]);
                    if(inputInfo != 1)
                        {
                        printf("Invalid input!\n");
                        fflush(stdin); // очистка потока в случае если ввод неправильный
                    }
                }
            }
        }

        //суммирование строк матрицы и занесение в массив
        //можно сделать суммирование в цикле заполнения, но для сохранения читабельности кода создаем новый цикл
        for (int i = 0; i < 6; ++i) {
            sum[i] = 0;
            for (int j = 0; j < 9; ++j) {
                sum[i] += arr[i][j];
            }
        }

        //выводы массива с результатом
        printf("Result array\n");
        for (int i = 0; i < 6; i++) {
            int strNum = i + 1;
            printf("Sum of elements of stroks number %d: %d\n", strNum, sum[i]);
        }

        //даем возможность начать заново
        printf("Do you want to continue?(1 - yes/0 - no):");
        scanf("%d", &response);

        //проверка ответа
        if (response == 1) {
            fflush(stdin); //очистка потока ввода
            inputInfo = 0; // очистка переменной ввода
        }else {
            break;
        }
    }
}
