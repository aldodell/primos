#ifndef ALDO2_H
#define ALDO2_H

#include "argumentsHandler.h"
#include "bigFactorObject.h"
#include "bigGearsFactorizer.h"
#include "bigHalfGearFactorizer.h"
#include "kdutils.h"
#include "maths_prime.h"
#include "primeTester.h"
#include "primelib.h"
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

void processA(int exp, bool putHeader);

void processB(int exp, bool putHeader);
void processRange(int from, int to);
void lookFirstK(mpz_class p);
bool isMersenneKnowPrimeExponent(mpz_class p);
void analysis(unsigned int p, unsigned int limit = 0);
void analysis2(unsigned int to = 1000, unsigned int from = 0);
int primarityTest(unsigned int p, unsigned int presieving, int nThreads,
                  unsigned int phases = 1, int debug = 0);

/** Return if a number is a 4k+1 */
// bool is4kp1(mpz_class n);

class primeHolder {
public:
  primeHolder(unsigned int theMersenneExponent, unsigned int n);
  unsigned int mersenneExponent;
  unsigned int key;   // number with mod == 0
  unsigned int prime; // number to be evaluated.
  unsigned int prime1;
  void reset(mpz_class initial = 1);
  bool next();
  unsigned int index;
};

class primeSieve {
public:
  vector<primeHolder> holders;
  primeSieve(unsigned int theMersenneExponent, unsigned int upTo);
  unsigned int mersenneExponent;
  void reset(mpz_class initial = 1);
  bool next();
  float ratio();
  mpz_class primorial;
};

#endif
