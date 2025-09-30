#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../include/6.h"


// тесты
// .\6.exe 0.0000001
// .\6.exe 0.001
double a(double epsilon) {
    double result = 0.0;
    for (double x = epsilon / 2; x <= 1.0; x += epsilon) {
        if (x != 0.0) {
            if (1 - x < epsilon / 2) {
                result += log(1 + x) / x * (1 - x + epsilon / 2);
            } else {
                result += log(1 + x) / x * epsilon;
            }
        }
    }
    return result;
}

double b(double epsilon) {
    double result = 0.0;
    for (double x = epsilon / 2; x <= 1.0; x += epsilon) {
        if (1 - x < epsilon / 2) {
            result += exp(-x * x / 2) * (1 - x + epsilon / 2);
        } else {
            result += exp(-x * x / 2 ) * epsilon;
        }
    }
    return result;
}

double c(double epsilon) {
    double result = 0.0;
    for (double x = epsilon / 2; x <= 1.0; x += epsilon) {
        if (x != 1) { 
            if (1 - x < epsilon / 2) {
                result += log(1 / (1 - x)) * (1 - x + epsilon / 2);
            } else {
                result += log(1 / (1 - x)) * epsilon;
            }
        }
    }
    return result;
}

double d(double epsilon) {
    double result = 0.0;
    for (double x = epsilon / 2; x <= 1.0; x += epsilon) {
        if (1 - x < epsilon / 2) {
            result += pow(x, x) * (1 - x + epsilon / 2);
        } else {
            result += pow(x, x) * epsilon;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Too much aruments\n");
    }
    double epsilon = strtod(argv[1], NULL);
    printf("a) %.8f\n", a(epsilon));
    printf("b) %.8f\n", b(epsilon));
    printf("c) %.8f\n", c(epsilon));
    printf("d) %.8f\n", d(epsilon));
    return 0;
}