#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int strLength( char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int inputNumber(char* message, int min, int max){
	int n = 0;
    int scanfRes = 0;

    while(scanfRes == 0){
        printf("%s", message);
        scanfRes = scanf("%d", &n);
        if(scanfRes == 0){
            printf("\033[1;31m\tInvalid Input!\033[0m\n");
        }
        else if(n < min || n > max) {
            printf("\033[1;31m\tNumber must be from %d to %d!\033[0m\n", min, max);
            scanfRes = 0;
            n = 0;
        }
		clearBuffer();
    }

	return n;
}

char *my_strncpy(char *dest, char *src, int n) {
    int i;
    
    for (i = 0; i < n && src[i] != '\0'; i++) {
        *(dest + i) = *(src + i);
    }

    // Заполнение оставшейся части dest нулями, если src короче n
    for (; i < n; i++) {
        *(dest + i) = '\0';
    }

    return dest;
}

char* inputString(char* msg, int length){
	char *str;
	str = (char*)calloc(length + 1, sizeof(char));
    printf("%s", msg);
	fgets(str, length + 1, stdin);
	return str;
}

void printString(char *message, char *str){
	printf("%s", message);
	puts(str);
}

void printArrayOfMatrix(char ****arr, int matrixNumber, int rows, int cols){
	for(int i = 0; i < matrixNumber; i++){
		printf("\t\033[32mMatrix with index [%d]\033[0m\n", i);
		for(int j = 0; j < rows; j++){
			printf("|");
			for(int k = 0; k < cols; k++){
				printf("%15s", *(*(*(arr + i)+ j) + k));
			}
			printf("|\n");
		}
	}
}

char**** createArrayOfMatrix(int matrixNumber, int rows, int cols){
	char ****arr = calloc(matrixNumber, sizeof(char***));
	for(int i = 0; i < matrixNumber; i++){
		printf("\t\033[32mCreating matrix with index [%d]\033[0m\n", matrixNumber);
		*(arr + i) = createMatrixAndFill(rows, cols);
	}
	return arr;
}

char*** createMatrixAndFill(int rows, int cols){
	char ***matrix = calloc(rows, sizeof(char**));

	for(int i = 0; i < rows; i++){
		*(matrix + i) = calloc(cols, sizeof(char*));
	}

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			printf("Enter length of the [%dx%d] element: ", i, j);
			int length = inputNumber("", 2, 100);
			*(*(matrix + i) + j) = inputString("Enter string: ", length);
			clearBuffer();
		}
	}
	return matrix;
}

int count_words(char *str) {
    int count = 0, in_word = 0;

    while (*str) {
        if (*str == ' ' || *str == '\t' || *str == '\n') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

char **findWords(char *str, int *wordsAmount) {
    int num_words = count_words(str);
	*wordsAmount = num_words;
    char **result = malloc((num_words + 1) * sizeof(char *));

    int word_index = 0;
    while (*str) {
        // Пропускаем пробельные символы
        while (*str == ' ' || *str == '\t' || *str == '\n') str++;

        if (*str) {
            // Определяем длину слова
            char *start = str;
            while (*str && *str != ' ' && *str != '\t' && *str != '\n') str++;

            int word_length = str - start;

            // Выделяем память под слово и копируем его
            result[word_index] = malloc((word_length + 1) * sizeof(char));
            for (int i = 0; i < word_length; i++) {
                result[word_index][i] = start[i];
            }
            result[word_index][word_length] = '\0';
            word_index++;
        }
    }

    return result;
}

int isPalindrome(char *word) {
    int len = strLength(word);
    for (int i = 0; i < len / 2; i++) {
        if (word[i] != word[len - 1 - i]) {
            return 0; 
        }
    }
    return 1; 
}

int getPalindromesInString(char **palindromes, int palindromesCounter, char* string) {
	int wordAmount = 0;
    char **words = findWords(string, &wordAmount);

	for (int i = 0; i < wordAmount; i++) {
		if(isPalindrome(*(words + i))){
			palindromesCounter++;
			*(palindromes + palindromesCounter - 1) = *(words + i); 
		}
		else{
			free(*(words + i));
		}
	}

	return palindromesCounter;
}

void findPalindromes(char ****arr, int matrixNumber, int rows, int cols){
	char **palindromes = calloc(20, sizeof(char*));
	int palindromesCounter = 0;

	for(int i = 0; i < matrixNumber; i++){
		for (int j = 0; j < rows; j++) {
			for(int k = 0; k < cols; k++){
				char* currentString = *(*(*(arr + i)+ j) + k);
				palindromesCounter = getPalindromesInString(palindromes, palindromesCounter, currentString);
			}
		}
	}

	printf("\nPalidromes at all: %d\n", palindromesCounter);
	printf("They are: ");
	for(int i = 0; i < palindromesCounter; i++){
		printf("%s, ", *(palindromes + i));
	}

	for(int i = 0; i < palindromesCounter; i++){
		free(*(palindromes + i));
	}
}


void freeArrayOfMatrix(char ****arr, int matrixNumber, int rows, int cols){
	for(int i = 0; i < matrixNumber; i++){
		for(int j = 0; j < rows; j++){
			for(int k = 0; k < cols; k++){
				free(*(*(*(arr + i)+ j) + k));
			}
		}
	}
}

// *(*(*(arr + i)+ j) + k) - обращение к элементу...