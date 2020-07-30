#ifndef ONI_H
#define ONI_H

#include "argumentsHandler.h"
#include "bigFactorObject.h"
#include "bigGearsFactorizer.h"
#include "bigHalfGearFactorizer.h"
#include "kdutils.h"
#include "maths_prime.h"
#include "primeTester.h"
#include "string"
#include <gmpxx.h>
#include <thread>

vector<unsigned int> mersenneExponents{
    2,        3,        5,        7,        13,       17,       19,
    31,       61,       89,       107,      127,      521,      607,
    1279,     2203,     2281,     3217,     4253,     4423,     9689,
    9941,     11213,    19937,    21701,    23209,    44497,    86243,
    110503,   132049,   216091,   756839,   859433,   1257787,  1398269,
    2976221,  3021377,  6972593,  13466917, 20996011, 24036583, 25964951,
    30402457, 32582657, 37156667, 42643801, 43112609, 57885161, 74207281,
    77232917, 82589933};

/* Return basic ONI operation. Adding odd numbers from a to b inclusive*/
mpz_class oni_sum(mpz_class a, mpz_class b);
void oni_primarity(mpz_class z);
void oni_test1(unsigned int a = 0, unsigned int b = 10);
// string findPower(mpz_class n, mpz_class &x, mpz_class &y);
string findPower(mpz_class n);
void findPower(mpz_class n, mpz_class &x, mpz_class &y);
void findPower(mpz_class n, int &x, int &y);

/*
void oni_wt(mpz_class x, mpz_class y, mpz_class aMin, mpz_class aMax,
            mpz_class bMin, mpz_class bMax, string &result, int id, int &flag);
void oni_n(int base, int exponent, mpz_class minB, mpz_class maxB);
*/

void oni_worker(int x, int y, mpz_class min, mpz_class max, int bMin, int id,
                string &result, int &threadSum);

void oni_finder(unsigned int x, unsigned int y, unsigned int bMin,
                int threadsQuantity = 4);

void oni_loop(unsigned int x, unsigned int bMin, int threadsQuantity);

void oni_worker_2(int x, int y, mpz_class min, mpz_class max, int id,
                  string &result, int &threadSum);

void oni_finder_2(unsigned int x, unsigned int y, int threadsQuantity = 4);

/*
Compiler:
clang++ -std=c++1z -stdlib=libc++ -lgmpxx -lgmp -pthread
-DBIG_HALF_GEAR_FACTORIZER_LIB kdutils.cpp argumentsHandler.cpp
bigFactorObject.cpp bigHalfGearFactorizer.cpp oni.cpp -o oni.out --debug
*/

#endif