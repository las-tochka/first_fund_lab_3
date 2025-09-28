#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../include/3.h"

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
double* findEqulationSolution(double epsilon, double a, double b, double c) {
    static double res[3];
    res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;
    // если уравнение - bx+c=0
    if (fabs(a) < epsilon) {
        if (fabs(b) < epsilon) {
            if (fabs(c) < epsilon) {
                res[0] = -1.0;
            } else {
                res[0] = 0.0;
            }
            return res;
        }
        res[0] = 1.0; res[1] = -c / b;
        return res;
    }
    double D = b * b - 4.0 * a * c;
    if (D < -epsilon) { // корней нет
        return res;
    }
    if (fabs(D) < epsilon) { // 1 корень
        res[0] = 1.0; res[1] = -b / (2.0 * a);
        return res;
    } // 2 корня
    double x1 = (-b + sqrt(D)) / (2.0 * a);
    double x2 = (-b - sqrt(D)) / (2.0 * a);
    if (fabs(x1 - x2) < epsilon) {
        res[0] = 1.0; res[1] = x1;
        return res;
    }
    res[0] = 2.0; res[1] = x1; res[2] = x2;
    return res;
}

void printSolution(double * solutions) {
    if (solutions[0] == -1.0) {
        printf("An infinite number of solutions\n");
        return;
    }
    if (solutions[0] == 0.0) {
        printf("No solutions\n");
        return;
    }
    if (solutions[0] == 1.0) {
        printf("One solution - %.6f\n", solutions[1]);
        return;
    }
    if (solutions[0] == 2.0) {
        printf("Two solutions - %.6f and %.6f\n", solutions[1], solutions[2]);
        return;
    }
    printf("Somehings goes wrong while finding solutions\n");
    return;
}

void q(int argc, int start, char ** numbers) {
    if (argc - start != 4) {
        printf("Wrong number of arguments\n");
        return;
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
            double sol [3] = {-1.0, 0.0, 0.0};
            printSolution(sol);
            return;
        }
        double* solutions = findEqulationSolution(epsilon, num[0], num[0], num[0]);
        printSolution(solutions);
        return;
    }
    if (k == 2) {
        int j[3] = {0, 0, 0};
        for (int i = 0; i < 3; i++) {
            j[i] = 1;
            double* solutions = findEqulationSolution(epsilon, num[j[0]], num[j[1]], num[j[2]]);
            printSolution(solutions);
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
                    double* solutions = findEqulationSolution(epsilon, num[j[0]], num[j[1]], num[j[2]]);
                    printSolution(solutions);
                    j[i2] = 0;
                }
            }
            j[i1] = 0;
        }
    }
}

// тесты
// .\3.exe -m 2.0 1
// .\3.exe -m 2 0
// .\3.exe -m 1 2
// .\3.exe -m 2.0 1.3
void m(int argc, int start, char ** numbers) {
    if (argc - start != 2) {
        printf("Wrong number of arguments\n");
        return;
    }
    double n1 = strtod(numbers[start], NULL);
    double n2 = strtod(numbers[start + 1], NULL);
    if (n1 == 0.0 || n2 == 0.0 || n1 != trunc(n1) || n2 != trunc(n2)) {
        printf("Numbers can't be 0 or double\n");
        return;
    }
    if (n1 / n2 != trunc(n1 / n2)) {
        printf("The first number is a multiple of the second\n");
        return;
    }
    printf("The first number is not a multiple of the second\n");
}

// тесты
// .\3.exe -t 0.001 3 4 5
// .\3.exe -t 0.001 3 4 5.1
// .\3.exe -t 0.01 3 4 5.001
void t(int argc, int start, char ** numbers) {
    if (argc - start != 4) {
        printf("Wrong number of arguments\n");
        return;
    }
    double epsilon = strtod(numbers[start], NULL);
    double num[3];
    for (int i = 1; i < 4; i++) {
        num[i - 1] = strtod(numbers[start + i], NULL);
    }

    if (num[0] > num[1] && num[0] > num[2]) {
        if (fabs(num[1] * num[1] + num[2] * num[2] - num[0] * num[0]) < epsilon) {
            printf("Such a right triangle exists");
        } else {
            printf("Such a right triangle doesn't exist");
        }
        return;
    }
    if (num[1] > num[0] && num[1] > num[2]) {
        if (fabs(num[0] * num[0] + num[2] * num[2] - num[1] * num[1]) < epsilon) {
            printf("Such a right triangle exists");
        } else {
            printf("Such a right triangle doesn't exist");
        }
        return;
    }
    if (fabs(num[0] * num[0] + num[1] * num[1] - num[2] * num[2]) < epsilon) {
            printf("Such a right triangle exists");
        } else {
            printf("Such a right triangle doesn't exist");
        }
}

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
    if (flag[1] == 'q') {
        q(argc, start, argv);
    } else if (flag[1] == 'm') {
        m(argc, start, argv);
    } else if (flag[1] == 't') {
        t(argc, start, argv);
    } else {
        printf("Incorrect flag");
        return 1;
    }
    return 0;
}