#ifndef ERATOSTHENES_SEGMENTED_SIEVE_GMP_H
#define ERATOSTHENES_SEGMENTED_SIEVE_GMP_H
#include "argumentsHandler.h"
#include "kdutils.h"
#include <gmpxx.h>
#include <thread>

// void generateMain(mpz_class  min, mpz_class  max, bool save);

class essGmp {
public:
  static void generateMain(mpz_class min, mpz_class max, bool save);
  void generate(int exponent);
  int isPrime(vector<unsigned char> &buffer, mpz_class number, mpz_class min);
  inline int getFlag(int64 block, int offset);
  int trivialPrimerTable[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int filesize = 1000000;

private:
};

#endif
