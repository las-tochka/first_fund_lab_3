#include<stdio.h>
#include<stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/2.h"

// Result is in include/2.h

// тест
// .\2.exe      
// 3
// 5
// -1
// 18
// ответ
// 11 0 61
// объяснение 5оу число - 11, -1 - такого быть не может -> 0, 18 теперь знаем из программы
//2 3 5 7 11 13...
int * generingSingleNumbers(int* numbers, int nowKol, int needKol, Result* result) {
    numbers = realloc(numbers, needKol * sizeof(int));
    if (!numbers) {
        result->error_code = -1;
        snprintf(result->error_message, sizeof(result->error_message), "Wrong memory allocation");
        return NULL;
    }
    result->error_code = 0;
    result->error_message[0] = '\0';
    int num = numbers[nowKol-1] + 1;
    while (nowKol < needKol) {
        int flag = 1; // проверка на простое число
        for (int i = 0; i < nowKol; i++) {
            if (num % numbers[i] == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            numbers[nowKol] = num;
            nowKol++;
        }
        num++;
    }
    return numbers;
}


// количество простых чисел примерно равно x/ln(x)
int main() {
    int T; // колличество вводимых чисел
    scanf("%d", &T);

    int kol = 100;
    int* numbers = malloc(10 * sizeof(int));
    if (!numbers) {
        return -1;
    }
    int* results = malloc(T * sizeof(int));
    if (!results) {
        free(numbers);
        return -1;
    }

    Result result = {0};
    numbers[0] = 2;
    numbers = generingSingleNumbers(numbers, 1, kol, &result);
    if (result.error_code == -1) {
        free(results);
        printf("%s", result.error_message);
        return -1;
    }
    
    int n = 0; // порядковые значения для ввода
    for (int i = 0; i < T; i++) {
        scanf("%d", &n);
        if (!numbers) {
            free(results);
            return -1;
        }

        if (n > kol) {
            numbers = generingSingleNumbers(numbers, kol, n, &result);
            if (result.error_code == -1) {
                free(results);
                printf("%s", result.error_message);
                return -1;
            }
            kol = n;
        }
        if (n < 1) {
            printf("Such number is not existing\n");
            results[i] = 0;
        } else {
            results[i] = numbers[n - 1];
        }
    }

    for (int i = 0; i < T; i++) {
        printf("%d ", results[i]);
    }
    return 0;
}