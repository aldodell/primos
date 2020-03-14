#ifndef MATHS_PRIME_H
#define MATHS_PRIME_H
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <gmpxx.h>
#include "kdutils.h"
using namespace std;

/* PROTOTYPES */
int jacobi(int a, int n);
void operatorTest();
bool isOdd(int n);
int64 factorial(int64 n);
mpz_class semiFactorial(mpz_class n);
#endif