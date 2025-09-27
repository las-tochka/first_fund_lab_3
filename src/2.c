#include<stdio.h>
#include<stdlib.h>
#include "../include/2.h"

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
int* generingSingleNumbers(int* numbers, int nowKol, int needKol) {
    numbers = realloc(numbers, needKol * sizeof(int));
    if (!numbers) {
        printf("Memory error.\n");
        return numbers;
    }
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
    if (!numbers) return -1;
    int* results = malloc(T * sizeof(int));
    if (!results) return -1;

    numbers[0] = 2;
    numbers = generingSingleNumbers(numbers, 1, kol);
    if (!numbers) return -1;
    
    int n = 0; // порядковые значения для ввода
    for (int i = 0; i < T; i++) {
        scanf("%d", &n);
        if (!numbers) return -1;

        if (n > kol) {
            numbers = generingSingleNumbers(numbers, kol, n);
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
    free(results);
    free(numbers);
    return 0;
}