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
void oni_test1(unsigned int a=0, unsigned int b=10);

#endif