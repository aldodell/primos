#ifndef MERSENNE_H
#include "argumentsHandler.h"
#include "kdutils.h"
#include <gmp.h>
#include <gmpxx.h>
#include <pthread.h>

string mersenne(int64 p);

// Encapsulate data for worker function
struct DataFinder {
  mpz_class fromK, toK, m, p;
  mpz_class *foundK;
  bool &keepAlive;
  bool &found;
};

// worker function sign
void *worker(void *args);

// Thread manager
void toFind(unsigned int exponent, int howManyThreads);

#define MERSENNE_H
#endif