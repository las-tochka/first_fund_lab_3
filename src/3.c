#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// #include "../include/3.h"

// проверка сколько уникальных коэффициентов мы имеем
// в num[0] будет коэффициент с максимумом повторений
//  тесты
// .\3.exe -q 0.0000001 1 0 1
// .\3.exe -q 0.001 0 0 0
// .\3.exe -q 1e-10 1.0 -3.0 2.0 1
int checkIn(double *num, double epsilon){
    if (fabs(num[0] - num[1]) < epsilon) {
        if (fabs(num[1] - num[2]) < epsilon) {
            return 1;
        } else {
            num[1] = num[2];
            return 2;
        }
    }
    if (fabs(num[1] - num[2]) < epsilon) {
        num[1] = num[0];
        num[0] = num[2];
        return 2;
    }
    if (fabs(num[0] - num[2]) < epsilon) {
        return 2;
    }
    return 3;
}

// поиск решений уравнения
int findEqulationSolution(double epsilon, double a, double b, double c, double * solution) {
    // если уравнение - bx+c=0
    if (fabs(a) < epsilon) {
        if (fabs(b) < epsilon) {
            if (fabs(c) < epsilon) {
                return -1;
            }
            return 0;
        }
        solution[0] = -c / b;
        return 1;
    }
    double D = b * b - 4.0 * a * c;
    if (D < -epsilon) { // корней нет
        return 0;
    }
    if (fabs(D) < epsilon) { // 1 корень
        solution[0] = -b / (2.0 * a);
        return 1;
    } // 2 корня
    double x1 = (-b + sqrt(D)) / (2.0 * a);
    double x2 = (-b - sqrt(D)) / (2.0 * a);
    if (fabs(x1 - x2) < epsilon) {
        solution[0] = x1;
        return 1;
    }
    solution[0] = x1;
    solution[1] = x2;
    return 2;
}

int printSolution(int k, double * solutions) {
    if (k == -1) {
        printf("An infinite number of solutions\n");
        return 1;
    }
    if (k == 0) {
        printf("No solutions\n");
        return 1;
    }
    if (k == 1) {
        printf("One solution - %.6f\n", solutions[0]);
        return 1;
    }
    if (k == 2) {
        printf("Two solutions - %.6f and %.6f\n", solutions[0], solutions[1]);
        return 1;
    }
    return -1;
}

int q(int argc, int start, char ** numbers) {
    if (argc - start != 4) {
        return -1;
    }
    double epsilon = strtod(numbers[start], NULL);
    double num[3];
    for (int i = 1; i < 4; i++) {
        num[i - 1] = strtod(numbers[start + i], NULL);
    }
    // проверим количество уникальных коэффициентов
    int k = checkIn(num, epsilon);
    if (k == 1) {
        if (num[0] == 0) {
            int k = -1;
            double sol [2] = {0.0, 0.0};
            int res = printSolution(k, sol);
            if (!res) {
                return -2;
            }
            return 0;
        }
        double solutions[2] = {0.0 , 0.0};
        int k = findEqulationSolution(epsilon, num[0], num[0], num[0], solutions);
        printSolution(k, solutions);
        return 0;
    }
    if (k == 2) {
        int j[3] = {0, 0, 0};
        for (int i = 0; i < 3; i++) {
            j[i] = 1;
            double solutions[2] = {0.0, 0.0};
            int k = findEqulationSolution(epsilon, num[j[0]], num[j[1]], num[j[2]], solutions);
            printSolution(k, solutions);
            j[i] = 0;
        }
    }
    if (k == 3) {
        int j[3] = {0, 0, 0};
        for (int i1 = 0; i1 < 3; i1++) {
            j[i1] = 1;
            for (int i2 =0; i2 < 3; i2++) {
                if (i2 != i1) {
                    j[i2] = 2;
                    double solutions[2] = {0.0, 0.0};
                    int k = findEqulationSolution(epsilon, num[j[0]], num[j[1]], num[j[2]], solutions);
                    printSolution(k, solutions);
                    j[i2] = 0;
                }
            }
            j[i1] = 0;
        }
    }
    return 1;
}

// тесты
// .\3.exe -m 2.0 1
// .\3.exe -m 2 0
// .\3.exe -m 1 2
// .\3.exe -m 2.0 1.3
int m(int argc, int start, char ** numbers) {
    if (argc - start != 2) {
        return -1;
    }
    double n1 = strtod(numbers[start], NULL);
    double n2 = strtod(numbers[start + 1], NULL);
    if (n1 == 0.0 || n2 == 0.0 || n1 - (int) n1 != 0 || n2 - (int) n2 != 0) {
        return -3;
    }
    if ((int) n1 % (int) n2 == 0) {
        printf("The first number is a multiple of the second\n");
        return 0;
    }
    printf("The first number is not a multiple of the second\n");
    return 0;
}

// тесты
// .\3.exe -t 0.001 3 4 5
// .\3.exe -t 0.001 3 4 5.1
// .\3.exe -t 0.01 3 4 5.001
int t(int argc, int start, char ** numbers) {
    if (argc - start != 4) {
        return -1;
    }
    double epsilon = strtod(numbers[start], NULL);
    double num[3];
    for (int i = 1; i < 4; i++) {
        num[i - 1] = strtod(numbers[start + i], NULL);
    }

    if (num[0] > num[1] && num[0] > num[2]) {
        if (fabs(num[1] * num[1] + num[2] * num[2] - num[0] * num[0]) < epsilon) {
            return 1;
        } else {
            return 2;
        }
        return 0;
    }
    if (num[1] > num[0] && num[1] > num[2]) {
        if (fabs(num[0] * num[0] + num[2] * num[2] - num[1] * num[1]) < epsilon) {
            return 1;
        } else {
            return 2;
        }
        return 0;
    }
    if (fabs(num[0] * num[0] + num[1] * num[1] - num[2] * num[2]) < epsilon) {
            return 1;
        } else {
            return 2;
        }
    return 0;
}

// отрицательные для ошибок, положительные - для результатов
int main(int argc, char *argv[]) {
    int number = -1;
    char *flag = NULL;
    int start = 0;
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-' || argv[i][0] == '/') {
            flag = argv[1];
            start = i + 1;
            break;
        }
    }
    if (!flag) {
        printf("Flag is not given");
        return 1;
    }

    int res = 0;
    if (flag[1] == 'q') {
        res = q(argc, start, argv);
    } else if (flag[1] == 'm') {
        res = m(argc, start, argv);
    } else if (flag[1] == 't') {
        res = t(argc, start, argv);
        if (res == 1) {
            printf("Such a right triangle exists");
        } else if (res == 2) {
            printf("Such a right triangle doesn't exist");
        }
    } else {
        printf("Incorrect flag");
        return 1;
    }

    if (res == -1) {
        printf("Wrong number of arguments\n");
    } else if (res == -2) {
        printf("Finding solutions in q goes wrong\n");
    } else if (res == -3) {
        printf("Numbers in m can't be 0 or double\n");
    }
    return 0;
}