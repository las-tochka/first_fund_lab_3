#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// #include "../include/4.h"

void e(){
    // для предела
    int n = 1e9;
    double res1 = pow(1 + 1.0 / n, n);
    // для произведения
    double res2 = 0;
    double num = 1.0;
    for (int i = 0; i < 10000; i++) {
        if (i > 0) {
            num /= i;
        }
        res2 += num;
        if (num < 1e-16) {
            break;
        }
    }
    // для уравнения
    double res3 = exp(1.0);
    printf("E with limit - %.8f, with multiplite - %.8f, with equal - %.8f\n", res1, res2, res3);
}

void p(){
    // для предела
    int n = 1000;
    double res1 = 1.0;
    for (int i = 1; i <= 1000; i++) {
        res1 = res1 * 16 * i * i;
        res1 /= ((n + i) * (n + i));
    }
    res1 /= n;
    // для произведения
    double res2 = 0.0;
    for (int i = 1; i < 10000; i++) {
        res2 += pow(-1, i - 1) / (2 * i - 1);
    }
    res2 *= 4;
    // для уравнения
    double res3 = acos(-1.0);
    printf("Pi with limit - %.8f, with multiplite - %.8f, with equal - %.8f\n", res1, res2, res3);
}

void ln2() {
    // для предела
    int n = 10000;
    double res1 = n * (pow(2, 1.0 / n) - 1);
    // для произведения
    double res2 = 0.0;
    for (int i = 1; i < 10000; i++) {
        res2 += pow(-1, i - 1) / i;
    }
    // для уравнения
    double res3 = log(2);
    printf("Ln(2) with limit - %.8f, with multiplite - %.8f, with equal - %.8f\n", res1, res2, res3);
}

void sqrt2() {
    // для предела
    int n = 10000;
    double res1 = 0.5;
    for (int i = 1; i <= 1000; i++) {
        res1 = res1 - pow(res1, 2) / 2 + 1;
    }
    // для произведения
    double res2 = 1.0;
    // только при 10 дает изменение в точности
    for (int i = 2; i < 10000; i++) {
        res2 *= pow(2, pow(2, -i));
    }
    // для уравнения
    double res3 = sqrt(2);
    printf("Sqrt(2) with limit - %.8f, with multiplite - %.8f, with equal - %.8f\n", res1, res2, res3);
}

int findingC(int M, int K) {
    int res = 1;
    for (int i = 1; i <= M - K; i++) {
        res *= (K + i - 1) / i;
    }
    return res;
}

double countP(int t) {
    double res = 1.0;
    for (int i = 1; i <= t; i++) {
        res *= (double)(i - 1) / i;
    }
    return res;
}

double factLogK(int m, int k) {
    double res = 1.0;
    for (int i = 1; i <= m - k; i++) {
        res *= (double)(k + i) / i;
    }
    return res;
}

void addSingle(int numbers[], int maxN) {
    for (int i = 0; i <= maxN; i++) {
        numbers[i] = i;
    }
    numbers[1] = 0;
    for (int i = 2; i <= maxN; i++) {
        for (int j = i; j <= maxN; j += i) {
            if (j != i) {
                numbers[j] = 0;
            }
        }
    }
}

// 0,57721566490153286060651209008240243
void g() {
	// для предела
	int m = 15;
	double res1 = 0.0;
	double K = 1.0;
	for (int k = 1; k <= m; k++) {
		int c = findingC(m, k);
		K *= k;
		if (k % 2 == 1) {
			c *= -1;
		}
		res1 += c * log(K) / k;
	}

    // для произведения
    double res2 = 0.0;
    for (int i = 2; i < 10000; i++) {
        res2 += (1.0 / (sqrt(i) * sqrt(i))) - (1.0 / i);
    }
    res2 -= pow(acos(-1.0), 2) / 6;
    // для уравнения
    int t = 100;
    double res3 = -log(log(t));
    int single[101];
    addSingle(single, 100);
    int p = 1;
    for (int i = 0; i <= 100; i++) {
        if (single[i] != 0) p *=  (double) (single[i] - 1) / single[i];
    }
    printf("G with limit - %.8f, with multiplite - %.8f, with equal - %.8f\n", res1, res2, res3);

}

int main() {
    // e();
    // p();
    // ln2();
    // sqrt2();
    g();
    return 0;
}