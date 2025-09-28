#pragma once

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int checkIn(double *num, double epsilon);
double* findEqulationSolution(double epsilon, double a, double b, double c);
void printSolution(double * solutions);
void q(int argc, int start, char ** numbers);
void m(int argc, int start, char ** numbers);
void t(int argc, int start, char ** numbers);