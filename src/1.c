#include <stdio.h>
#include "../include/1.h"

// тесты
//.\1.exe 0 -h
//.\1.exe 10 -h
//.\1.exe 110 -h
void h(int x) {
    if (x == 0 || x > 100) {
        printf("Such numbers are not found\n");
        return;
    }
    for (int i = 1; i <= 100; i++) {
        if (i % x == 0) {
            printf("%d ", i);
        }
    }
}

//.\1.exe 1 -p
//.\1.exe 10 -p
//.\1.exe 101111111111111111111111111111111111111111111111111111111111111111111112222222222222222222222222222222 -p
void p(int x) {
    if (x == 1 || x == 0) {
        printf("Is not single or composit\n");
        return;
    }
    if (x == 2) {
        printf("Single\n");
    }
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            printf("Composit\n");
            return;
        }
    }
    printf("Single\n");
}

//.\1.exe 0 -s
//.\1.exe 10 -s
void s(int x) {
    char Numbers[] = "0123456789ABCDEF";
    char str[9] = "";
    int n = 0;
    
    if (x == 0) {
        printf("0\n");
        return;
    }
    
    while (x > 0) {
        int to_hex = x % 16;
        str[n++] = Numbers[to_hex];
        x = x / 16;
    }
    
    for (int i = n - 1; i >= 0; i--) {
        printf("%c ", str[i]);
    }
    printf("\n");
}

// .\1.exe 101 -e
// .\1.exe 4 -e
void e(int x) {
    if (x == 0 || x > 10) {
        printf("X must be lower than 10\n");
        return;
    }
    for (int i = 1; i <= x; i++) {
        printf("%d ", i * i);
    }
}

// .\1.exe 10 -a
void a(int x) {
    int number = 0;
    for (int i = 0; i <= x; i++) {
        number += i;
    }
    printf("%d", number);
}

// .\1.exe 0 -f
// .\1.exe 5 -f
void f(int x) {
    if (x == 0) {
        printf("Factorial 0 is not exsisting\n");
        return;
    }
    int number = 1;
    for (int i = 2; i <= x; i++) {
        number *= i;
    }
    printf("%d", number);
}

void command(char str[], int x) {
    if (str[0] != '-' || str[2] != '\0') {
        printf("Incorrect input\n");
        return;
    }
    if (str[1] == 'h') {
        h(x);
    } else if (str[1] == 'p') {
        p(x);
    } else if (str[1] == 's') {
        s(x);
    } else if (str[1] == 'e') {
        e(x);
    } else if (str[1] == 'a') {
        a(x);
    } else if (str[1] == 'f') {
        f(x);
    } else {
        printf("Incorrect input\n");
        return;
    }
}

// ч не может быть меньше 0, тк - начинает команду
int main(int argc, char *argv[]) {
    int number = -1;
    char *flag = NULL;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' || argv[i][0] == '/') {
            if (!flag) {
                flag = argv[i];
            } else {
                printf("Only one flag is allowed\n");
                return 1;
            }
        
        } else {
            if (number != -1){
                printf("Only one number is allowed\n");
                return 1;
            } else {
                number = 0;
            }
            int j = 0;
            while (argv[i][j] != '\0' && argv[i][j] != EOF) {
                if (argv[i][j] >= '0' && argv[i][j] <= '9') {
                    number = number * 10 + argv[i][j] - '0';
                } else {
                    printf("Incorreect input\n");
                    return 1;
                }
                ++j;
            }
        }
    }
    if (flag && number != -1) {
        command(flag, number);
    }else {
        printf("Not everything is given\n");
        return 1;
    }

    return 0;
}