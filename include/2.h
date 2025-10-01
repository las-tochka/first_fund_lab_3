#pragma once

#include<stdio.h>

typedef struct {
    int error_code;
    char error_message[100];
} Result;

int* generingSingleNumbers(int* numbers, int nowKol, int needKol, Result* result);